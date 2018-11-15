/* Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stddef.h>
#include <string.h>                     /* memset(), memcpy() */
#include <assert.h>
#include <limits.h>                     /* UINT_MAX */
#include <stdio.h>                      /* fprintf */
#include <stdlib.h>                     /* getenv */

#ifdef _WIN32
#define getpid GetCurrentProcessId
#else
#include <sys/time.h>                   /* gettimeofday() */
#include <sys/types.h>                  /* getpid() */
#include <unistd.h>                     /* getpid() */
#include <fcntl.h>                      /* O_RDONLY */
#include <errno.h>
#endif

#define XML_BUILDING_EXPAT 1

#ifdef _WIN32
#include "winconfig.h"
#elif defined(HAVE_EXPAT_CONFIG_H)
#include <expat_config.h>
#endif /* ndef _WIN32 */

#include "ascii.h"
#include "expat.h"
#include "siphash.h"

#if defined(HAVE_GETRANDOM) || defined(HAVE_SYSCALL_GETRANDOM)
# if defined(HAVE_GETRANDOM)
#  include <sys/random.h>    /* getrandom */
# else
#  include <unistd.h>        /* syscall */
#  include <sys/syscall.h>   /* SYS_getrandom */
# endif
# if ! defined(GRND_NONBLOCK)
#  define GRND_NONBLOCK  0x0001
# endif  /* defined(GRND_NONBLOCK) */
#endif  /* defined(HAVE_GETRANDOM) || defined(HAVE_SYSCALL_GETRANDOM) */

#if defined(HAVE_LIBBSD) \
    && (defined(HAVE_ARC4RANDOM_BUF) || defined(HAVE_ARC4RANDOM))
# include <bsd/stdlib.h>
#endif

#if defined(_WIN32) && !defined(LOAD_LIBRARY_SEARCH_SYSTEM32)
# define LOAD_LIBRARY_SEARCH_SYSTEM32  0x00000800
#endif

#ifdef XML_UNICODE
#define XML_ENCODE_MAX XML_UTF16_ENCODE_MAX
#define XmlConvert XmlUtf16Convert
#define XmlGetInternalEncoding XmlGetUtf16InternalEncoding
#define XmlGetInternalEncodingNS XmlGetUtf16InternalEncodingNS
#define XmlEncode XmlUtf16Encode
/* Using pointer subtraction to convert to integer type. */
#define MUST_CONVERT(enc, s) (!(enc)->isUtf16 || (((char *)(s) - (char *)NULL) & 1))
typedef unsigned short ICHAR;
#else
#define XML_ENCODE_MAX XML_UTF8_ENCODE_MAX
#define XmlConvert XmlUtf8Convert
#define XmlGetInternalEncoding XmlGetUtf8InternalEncoding
#define XmlGetInternalEncodingNS XmlGetUtf8InternalEncodingNS
#define XmlEncode XmlUtf8Encode
#define MUST_CONVERT(enc, s) (!(enc)->isUtf8)
typedef char ICHAR;
#endif


#ifndef XML_NS

#define XmlInitEncodingNS XmlInitEncoding
#define XmlInitUnknownEncodingNS XmlInitUnknownEncoding
#undef XmlGetInternalEncodingNS
#define XmlGetInternalEncodingNS XmlGetInternalEncoding
#define XmlParseXmlDeclNS XmlParseXmlDecl

#endif

#ifdef XML_UNICODE

#ifdef XML_UNICODE_WCHAR_T
#define XML_T(x) (const wchar_t)x
#define XML_L(x) L ## x
#else
#define XML_T(x) (const unsigned short)x
#define XML_L(x) x
#endif

#else

#define XML_T(x) x
#define XML_L(x) x

#endif

/* Round up n to be a multiple of sz, where sz is a power of 2. */
#define ROUND_UP(n, sz) (((n) + ((sz) - 1)) & ~((sz) - 1))

/* Do safe (NULL-aware) pointer arithmetic */
#define EXPAT_SAFE_PTR_DIFF(p, q) (((p) && (q)) ? ((p) - (q)) : 0)

#include "internal.h"
#include "xmltok.h"
#include "xmlrole.h"

typedef const XML_Char *KEY;

typedef struct {
  KEY name;
} NAMED;

typedef struct {
  NAMED **v;
  unsigned char power;
  size_t size;
  size_t used;
  const XML_Memory_Handling_Suite *mem;
} HASH_TABLE;

static size_t
keylen(KEY s);

static void
copy_salt_to_sipkey(XML_Parser parser, struct sipkey * key);

/* For probing (after a collision) we need a step size relative prime
   to the hash table size, which is a power of 2. We use double-hashing,
   since we can calculate a second hash value cheaply by taking those bits
   of the first hash value that were discarded (masked out) when the table
   index was calculated: index = hash & mask, where mask = table->size - 1.
   We limit the maximum step size to table->size / 4 (mask >> 2) and make
   it odd, since odd numbers are always relative prime to a power of 2.
*/
#define SECOND_HASH(hash, mask, power) \
  ((((hash) & ~(mask)) >> ((power) - 1)) & ((mask) >> 2))
#define PROBE_STEP(hash, mask, power) \
  ((unsigned char)((SECOND_HASH(hash, mask, power)) | 1))

typedef struct {
  NAMED **p;
  NAMED **end;
} HASH_TABLE_ITER;

#define INIT_TAG_BUF_SIZE 32  /* must be a multiple of sizeof(XML_Char) */
#define INIT_DATA_BUF_SIZE 1024
#define INIT_ATTS_SIZE 16
#define INIT_ATTS_VERSION 0xFFFFFFFF
#define INIT_BLOCK_SIZE 1024
#define INIT_BUFFER_SIZE 1024

#define EXPAND_SPARE 24

typedef struct binding {
  struct prefix *prefix;
  struct binding *nextTagBinding;
  struct binding *prevPrefixBinding;
  const struct attribute_id *attId;
  XML_Char *uri;
  int uriLen;
  int uriAlloc;
} BINDING;

typedef struct prefix {
  const XML_Char *name;
  BINDING *binding;
} PREFIX;

typedef struct {
  const XML_Char *str;
  const XML_Char *localPart;
  const XML_Char *prefix;
  int strLen;
  int uriLen;
  int prefixLen;
} TAG_NAME;

/* TAG represents an open element.
   The name of the element is stored in both the document and API
   encodings.  The memory buffer 'buf' is a separately-allocated
   memory area which stores the name.  During the XML_Parse()/
   XMLParseBuffer() when the element is open, the memory for the 'raw'
   version of the name (in the document encoding) is shared with the
   document buffer.  If the element is open across calls to
   XML_Parse()/XML_ParseBuffer(), the buffer is re-allocated to
   contain the 'raw' name as well.

   A parser re-uses these structures, maintaining a list of allocated
   TAG objects in a free list.
*/
typedef struct tag {
  struct tag *parent;           /* parent of this element */
  const char *rawName;          /* tagName in the original encoding */
  int rawNameLength;
  TAG_NAME name;                /* tagName in the API encoding */
  char *buf;                    /* buffer for name components */
  char *bufEnd;                 /* end of the buffer */
  BINDING *bindings;
} TAG;

typedef struct {
  const XML_Char *name;
  const XML_Char *textPtr;
  int textLen;                  /* length in XML_Chars */
  int processed;                /* # of processed bytes - when suspended */
  const XML_Char *systemId;
  const XML_Char *base;
  const XML_Char *publicId;
  const XML_Char *notation;
  XML_Bool open;
  XML_Bool is_param;
  XML_Bool is_internal; /* true if declared in internal subset outside PE */
} ENTITY;

typedef struct {
  enum XML_Content_Type         type;
  enum XML_Content_Quant        quant;
  const XML_Char *              name;
  int                           firstchild;
  int                           lastchild;
  int                           childcnt;
  int                           nextsib;
} CONTENT_SCAFFOLD;

#define INIT_SCAFFOLD_ELEMENTS 32

typedef struct block {
  struct block *next;
  int size;
  XML_Char s[1];
} BLOCK;

typedef struct {
  BLOCK *blocks;
  BLOCK *freeBlocks;
  const XML_Char *end;
  XML_Char *ptr;
  XML_Char *start;
  const XML_Memory_Handling_Suite *mem;
} STRING_POOL;

/* The XML_Char before the name is used to determine whether
   an attribute has been specified. */
typedef struct attribute_id {
  XML_Char *name;
  PREFIX *prefix;
  XML_Bool maybeTokenized;
  XML_Bool xmlns;
} ATTRIBUTE_ID;

typedef struct {
  const ATTRIBUTE_ID *id;
  XML_Bool isCdata;
  const XML_Char *value;
} DEFAULT_ATTRIBUTE;

typedef struct {
  unsigned long version;
  unsigned long hash;
  const XML_Char *uriName;
} NS_ATT;

typedef struct {
  const XML_Char *name;
  PREFIX *prefix;
  const ATTRIBUTE_ID *idAtt;
  int nDefaultAtts;
  int allocDefaultAtts;
  DEFAULT_ATTRIBUTE *defaultAtts;
} ELEMENT_TYPE;

typedef struct {
  HASH_TABLE generalEntities;
  HASH_TABLE elementTypes;
  HASH_TABLE attributeIds;
  HASH_TABLE prefixes;
  STRING_POOL pool;
  STRING_POOL entityValuePool;
  /* false once a parameter entity reference has been skipped */
  XML_Bool keepProcessing;
  /* true once an internal or external PE reference has been encountered;
     this includes the reference to an external subset */
  XML_Bool hasParamEntityRefs;
  XML_Bool standalone;
#ifdef XML_DTD
  /* indicates if external PE has been read */
  XML_Bool paramEntityRead;
  HASH_TABLE paramEntities;
#endif /* XML_DTD */
  PREFIX defaultPrefix;
  /* === scaffolding for building content model === */
  XML_Bool in_eldecl;
  CONTENT_SCAFFOLD *scaffold;
  unsigned contentStringLen;
  unsigned scaffSize;
  unsigned scaffCount;
  int scaffLevel;
  int *scaffIndex;
} DTD;

typedef struct open_internal_entity {
  const char *internalEventPtr;
  const char *internalEventEndPtr;
  struct open_internal_entity *next;
  ENTITY *entity;
  int startTagLevel;
  XML_Bool betweenDecl; /* WFC: PE Between Declarations */
} OPEN_INTERNAL_ENTITY;

typedef enum XML_Error PTRCALL Processor(XML_Parser parser,
                                         const char *start,
                                         const char *end,
                                         const char **endPtr);

static Processor prologProcessor;
static Processor prologInitProcessor;
static Processor contentProcessor;
static Processor cdataSectionProcessor;
#ifdef XML_DTD
static Processor ignoreSectionProcessor;
static Processor externalParEntProcessor;
static Processor externalParEntInitProcessor;
static Processor entityValueProcessor;
static Processor entityValueInitProcessor;
#endif /* XML_DTD */
static Processor epilogProcessor;
static Processor errorProcessor;
static Processor externalEntityInitProcessor;
static Processor externalEntityInitProcessor2;
static Processor externalEntityInitProcessor3;
static Processor externalEntityContentProcessor;
static Processor internalEntityProcessor;

static enum XML_Error
handleUnknownEncoding(XML_Parser parser, const XML_Char *encodingName);
static enum XML_Error
processXmlDecl(XML_Parser parser, int isGeneralTextEntity,
               const char *s, const char *next);
static enum XML_Error
initializeEncoding(XML_Parser parser);
static enum XML_Error
doProlog(XML_Parser parser, const ENCODING *enc, const char *s,
         const char *end, int tok, const char *next, const char **nextPtr,
         XML_Bool haveMore);
static enum XML_Error
processInternalEntity(XML_Parser parser, ENTITY *entity,
                      XML_Bool betweenDecl);
static enum XML_Error
doContent(XML_Parser parser, int startTagLevel, const ENCODING *enc,
          const char *start, const char *end, const char **endPtr,
          XML_Bool haveMore);
static enum XML_Error
doCdataSection(XML_Parser parser, const ENCODING *, const char **startPtr,
               const char *end, const char **nextPtr, XML_Bool haveMore);
#ifdef XML_DTD
static enum XML_Error
doIgnoreSection(XML_Parser parser, const ENCODING *, const char **startPtr,
                const char *end, const char **nextPtr, XML_Bool haveMore);
#endif /* XML_DTD */

static void
freeBindings(XML_Parser parser, BINDING *bindings);
static enum XML_Error
storeAtts(XML_Parser parser, const ENCODING *, const char *s,
          TAG_NAME *tagNamePtr, BINDING **bindingsPtr);
static enum XML_Error
addBinding(XML_Parser parser, PREFIX *prefix, const ATTRIBUTE_ID *attId,
           const XML_Char *uri, BINDING **bindingsPtr);
static int
defineAttribute(ELEMENT_TYPE *type, ATTRIBUTE_ID *, XML_Bool isCdata,
                XML_Bool isId, const XML_Char *dfltValue, XML_Parser parser);
static enum XML_Error
storeAttributeValue(XML_Parser parser, const ENCODING *, XML_Bool isCdata,
                    const char *, const char *, STRING_POOL *);
static enum XML_Error
appendAttributeValue(XML_Parser parser, const ENCODING *, XML_Bool isCdata,
                     const char *, const char *, STRING_POOL *);
static ATTRIBUTE_ID *
getAttributeId(XML_Parser parser, const ENCODING *enc, const char *start,
               const char *end);
static int
setElementTypePrefix(XML_Parser parser, ELEMENT_TYPE *);
static enum XML_Error
storeEntityValue(XML_Parser parser, const ENCODING *enc, const char *start,
                 const char *end);
static int
reportProcessingInstruction(XML_Parser parser, const ENCODING *enc,
                            const char *start, const char *end);
static int
reportComment(XML_Parser parser, const ENCODING *enc, const char *start,
              const char *end);
static void
reportDefault(XML_Parser parser, const ENCODING *enc, const char *start,
              const char *end);

static const XML_Char * getContext(XML_Parser parser);
static XML_Bool
setContext(XML_Parser parser, const XML_Char *context);

static void FASTCALL normalizePublicId(XML_Char *s);

static DTD * dtdCreate(const XML_Memory_Handling_Suite *ms);
/* do not call if m_parentParser != NULL */
static void dtdReset(DTD *p, const XML_Memory_Handling_Suite *ms);
static void
dtdDestroy(DTD *p, XML_Bool isDocEntity, const XML_Memory_Handling_Suite *ms);
static int
dtdCopy(XML_Parser oldParser,
        DTD *newDtd, const DTD *oldDtd, const XML_Memory_Handling_Suite *ms);
static int
copyEntityTable(XML_Parser oldParser,
                HASH_TABLE *, STRING_POOL *, const HASH_TABLE *);
static NAMED *
lookup(XML_Parser parser, HASH_TABLE *table, KEY name, size_t createSize);
static void FASTCALL
hashTableInit(HASH_TABLE *, const XML_Memory_Handling_Suite *ms);
static void FASTCALL hashTableClear(HASH_TABLE *);
static void FASTCALL hashTableDestroy(HASH_TABLE *);
static void FASTCALL
hashTableIterInit(HASH_TABLE_ITER *, const HASH_TABLE *);
static NAMED * FASTCALL hashTableIterNext(HASH_TABLE_ITER *);

static void FASTCALL
poolInit(STRING_POOL *, const XML_Memory_Handling_Suite *ms);
static void FASTCALL poolClear(STRING_POOL *);
static void FASTCALL poolDestroy(STRING_POOL *);
static XML_Char *
poolAppend(STRING_POOL *pool, const ENCODING *enc,
           const char *ptr, const char *end);
static XML_Char *
poolStoreString(STRING_POOL *pool, const ENCODING *enc,
                const char *ptr, const char *end);
static XML_Bool FASTCALL poolGrow(STRING_POOL *pool);
static const XML_Char * FASTCALL
poolCopyString(STRING_POOL *pool, const XML_Char *s);
static const XML_Char *
poolCopyStringN(STRING_POOL *pool, const XML_Char *s, int n);
static const XML_Char * FASTCALL
poolAppendString(STRING_POOL *pool, const XML_Char *s);

static int FASTCALL nextScaffoldPart(XML_Parser parser);
static XML_Content * build_model(XML_Parser parser);
static ELEMENT_TYPE *
getElementType(XML_Parser parser, const ENCODING *enc,
               const char *ptr, const char *end);

static XML_Char *copyString(const XML_Char *s,
                            const XML_Memory_Handling_Suite *memsuite);

static unsigned long generate_hash_secret_salt(XML_Parser parser);
static XML_Bool startParsing(XML_Parser parser);

static XML_Parser
parserCreate(const XML_Char *encodingName,
             const XML_Memory_Handling_Suite *memsuite,
             const XML_Char *nameSep,
             DTD *dtd);

static void
parserInit(XML_Parser parser, const XML_Char *encodingName);

#define poolStart(pool) ((pool)->start)
#define poolEnd(pool) ((pool)->ptr)
#define poolLength(pool) ((pool)->ptr - (pool)->start)
#define poolChop(pool) ((void)--(pool->ptr))
#define poolLastChar(pool) (((pool)->ptr)[-1])
#define poolDiscard(pool) ((pool)->ptr = (pool)->start)
#define poolFinish(pool) ((pool)->start = (pool)->ptr)
#define poolAppendChar(pool, c) \
  (((pool)->ptr == (pool)->end && !poolGrow(pool)) \
   ? 0 \
   : ((*((pool)->ptr)++ = c), 1))

struct XML_ParserStruct {
  /* The first member must be m_userData so that the XML_GetUserData
     macro works. */
  void *m_userData;
  void *m_handlerArg;
  char *m_buffer;
  const XML_Memory_Handling_Suite m_mem;
  /* first character to be parsed */
  const char *m_bufferPtr;
  /* past last character to be parsed */
  char *m_bufferEnd;
  /* allocated end of m_buffer */
  const char *m_bufferLim;
  XML_Index m_parseEndByteIndex;
  const char *m_parseEndPtr;
  XML_Char *m_dataBuf;
  XML_Char *m_dataBufEnd;
  XML_StartElementHandler m_startElementHandler;
  XML_EndElementHandler m_endElementHandler;
  XML_CharacterDataHandler m_characterDataHandler;
  XML_ProcessingInstructionHandler m_processingInstructionHandler;
  XML_CommentHandler m_commentHandler;
  XML_StartCdataSectionHandler m_startCdataSectionHandler;
  XML_EndCdataSectionHandler m_endCdataSectionHandler;
  XML_DefaultHandler m_defaultHandler;
  XML_StartDoctypeDeclHandler m_startDoctypeDeclHandler;
  XML_EndDoctypeDeclHandler m_endDoctypeDeclHandler;
  XML_UnparsedEntityDeclHandler m_unparsedEntityDeclHandler;
  XML_NotationDeclHandler m_notationDeclHandler;
  XML_StartNamespaceDeclHandler m_startNamespaceDeclHandler;
  XML_EndNamespaceDeclHandler m_endNamespaceDeclHandler;
  XML_NotStandaloneHandler m_notStandaloneHandler;
  XML_ExternalEntityRefHandler m_externalEntityRefHandler;
  XML_Parser m_externalEntityRefHandlerArg;
  XML_SkippedEntityHandler m_skippedEntityHandler;
  XML_UnknownEncodingHandler m_unknownEncodingHandler;
  XML_ElementDeclHandler m_elementDeclHandler;
  XML_AttlistDeclHandler m_attlistDeclHandler;
  XML_EntityDeclHandler m_entityDeclHandler;
  XML_XmlDeclHandler m_xmlDeclHandler;
  const ENCODING *m_encoding;
  INIT_ENCODING m_initEncoding;
  const ENCODING *m_internalEncoding;
  const XML_Char *m_protocolEncodingName;
  XML_Bool m_ns;
  XML_Bool m_ns_triplets;
  void *m_unknownEncodingMem;
  void *m_unknownEncodingData;
  void *m_unknownEncodingHandlerData;
  void (XMLCALL *m_unknownEncodingRelease)(void *);
  PROLOG_STATE m_prologState;
  Processor *m_processor;
  enum XML_Error m_errorCode;
  const char *m_eventPtr;
  const char *m_eventEndPtr;
  const char *m_positionPtr;
  OPEN_INTERNAL_ENTITY *m_openInternalEntities;
  OPEN_INTERNAL_ENTITY *m_freeInternalEntities;
  XML_Bool m_defaultExpandInternalEntities;
  int m_tagLevel;
  ENTITY *m_declEntity;
  const XML_Char *m_doctypeName;
  const XML_Char *m_doctypeSysid;
  const XML_Char *m_doctypePubid;
  const XML_Char *m_declAttributeType;
  const XML_Char *m_declNotationName;
  const XML_Char *m_declNotationPublicId;
  ELEMENT_TYPE *m_declElementType;
  ATTRIBUTE_ID *m_declAttributeId;
  XML_Bool m_declAttributeIsCdata;
  XML_Bool m_declAttributeIsId;
  DTD *m_dtd;
  const XML_Char *m_curBase;
  TAG *m_tagStack;
  TAG *m_freeTagList;
  BINDING *m_inheritedBindings;
  BINDING *m_freeBindingList;
  int m_attsSize;
  int m_nSpecifiedAtts;
  int m_idAttIndex;
  ATTRIBUTE *m_atts;
  NS_ATT *m_nsAtts;
  unsigned long m_nsAttsVersion;
  unsigned char m_nsAttsPower;
#ifdef XML_ATTR_INFO
  XML_AttrInfo *m_attInfo;
#endif
  POSITION m_position;
  STRING_POOL m_tempPool;
  STRING_POOL m_temp2Pool;
  char *m_groupConnector;
  unsigned int m_groupSize;
  XML_Char m_namespaceSeparator;
  XML_Parser m_parentParser;
  XML_ParsingStatus m_parsingStatus;
#ifdef XML_DTD
  XML_Bool m_isParamEntity;
  XML_Bool m_useForeignDTD;
  enum XML_ParamEntityParsing m_paramEntityParsing;
#endif
  unsigned long m_hash_secret_salt;
};

#define MALLOC(parser, s)      (parser->m_mem.malloc_fcn((s)))
#define REALLOC(parser, p, s)  (parser->m_mem.realloc_fcn((p),(s)))
#define FREE(parser, p)        (parser->m_mem.free_fcn((p)))


XML_Parser XMLCALL
XML_ParserCreate(const XML_Char *encodingName)
{
  return XML_ParserCreate_MM(encodingName, NULL, NULL);
}

XML_Parser XMLCALL
XML_ParserCreateNS(const XML_Char *encodingName, XML_Char nsSep)
{
  XML_Char tmp[2];
  *tmp = nsSep;
  return XML_ParserCreate_MM(encodingName, NULL, tmp);
}

static const XML_Char implicitContext[] = {
  ASCII_x, ASCII_m, ASCII_l, ASCII_EQUALS, ASCII_h, ASCII_t, ASCII_t, ASCII_p,
  ASCII_COLON, ASCII_SLASH, ASCII_SLASH, ASCII_w, ASCII_w, ASCII_w,
  ASCII_PERIOD, ASCII_w, ASCII_3, ASCII_PERIOD, ASCII_o, ASCII_r, ASCII_g,
  ASCII_SLASH, ASCII_X, ASCII_M, ASCII_L, ASCII_SLASH, ASCII_1, ASCII_9,
  ASCII_9, ASCII_8, ASCII_SLASH, ASCII_n, ASCII_a, ASCII_m, ASCII_e,
  ASCII_s, ASCII_p, ASCII_a, ASCII_c, ASCII_e, '\0'
};


/* To avoid warnings about unused functions: */
#if ! defined(HAVE_ARC4RANDOM_BUF) && ! defined(HAVE_ARC4RANDOM)

#if defined(HAVE_GETRANDOM) || defined(HAVE_SYSCALL_GETRANDOM)

/* Obtain entropy on Linux 3.17+ */
static int
writeRandomBytes_getrandom_nonblock(void * target, size_t count) {
  int success = 0;  /* full count bytes written? */
  size_t bytesWrittenTotal = 0;
  const unsigned int getrandomFlags = GRND_NONBLOCK;

  do {
    void * const currentTarget = (void*)((char*)target + bytesWrittenTotal);
    const size_t bytesToWrite = count - bytesWrittenTotal;

    const int bytesWrittenMore =
#if defined(HAVE_GETRANDOM)
        getrandom(currentTarget, bytesToWrite, getrandomFlags);
#else
        syscall(SYS_getrandom, currentTarget, bytesToWrite, getrandomFlags);
#endif

    if (bytesWrittenMore > 0) {
      bytesWrittenTotal += bytesWrittenMore;
      if (bytesWrittenTotal >= count)
        success = 1;
    }
  } while (! success && (errno == EINTR));

  return success;
}

#endif  /* defined(HAVE_GETRANDOM) || defined(HAVE_SYSCALL_GETRANDOM) */


#if ! defined(_WIN32) && defined(XML_DEV_URANDOM)

/* Extract entropy from /dev/urandom */
static int
writeRandomBytes_dev_urandom(void * target, size_t count) {
  int success = 0;  /* full count bytes written? */
  size_t bytesWrittenTotal = 0;

  const int fd = open("/dev/urandom", O_RDONLY);
  if (fd < 0) {
    return 0;
  }

  do {
    void * const currentTarget = (void*)((char*)target + bytesWrittenTotal);
    const size_t bytesToWrite = count - bytesWrittenTotal;

    const ssize_t bytesWrittenMore = read(fd, currentTarget, bytesToWrite);

    if (bytesWrittenMore > 0) {
      bytesWrittenTotal += bytesWrittenMore;
      if (bytesWrittenTotal >= count)
        success = 1;
    }
  } while (! success && (errno == EINTR));

  close(fd);
  return success;
}

#endif  /* ! defined(_WIN32) && defined(XML_DEV_URANDOM) */

#endif  /* ! defined(HAVE_ARC4RANDOM_BUF) && ! defined(HAVE_ARC4RANDOM) */


#if defined(HAVE_ARC4RANDOM)

static void
writeRandomBytes_arc4random(void * target, size_t count) {
  size_t bytesWrittenTotal = 0;

  while (bytesWrittenTotal < count) {
    const uint32_t random32 = arc4random();
    size_t i = 0;

    for (; (i < sizeof(random32)) && (bytesWrittenTotal < count);
        i++, bytesWrittenTotal++) {
      const uint8_t random8 = (uint8_t)(random32 >> (i * 8));
      ((uint8_t *)target)[bytesWrittenTotal] = random8;
    }
  }
}

#endif  /* defined(HAVE_ARC4RANDOM) */


#ifdef _WIN32

typedef BOOLEAN (APIENTRY *RTLGENRANDOM_FUNC)(PVOID, ULONG);
HMODULE _Expat_LoadLibrary(LPCTSTR filename);  /* see loadlibrary.c */

/* Obtain entropy on Windows XP / Windows Server 2003 and later.
 * Hint on RtlGenRandom and the following article from libsodium.
 *
 * Michael Howard: Cryptographically Secure Random number on Windows without using CryptoAPI
 * https://blogs.msdn.microsoft.com/michael_howard/2005/01/14/cryptographically-secure-random-number-on-windows-without-using-cryptoapi/
 */
static int
writeRandomBytes_RtlGenRandom(void * target, size_t count) {
  int success = 0;  /* full count bytes written? */
  const HMODULE advapi32 = _Expat_LoadLibrary(TEXT("ADVAPI32.DLL"));

  if (advapi32) {
    const RTLGENRANDOM_FUNC RtlGenRandom
        = (RTLGENRANDOM_FUNC)GetProcAddress(advapi32, "SystemFunction036");
    if (RtlGenRandom) {
      if (RtlGenRandom((PVOID)target, (ULONG)count) == TRUE) {
        success = 1;
      }
    }
    FreeLibrary(advapi32);
  }

  return success;
}

#endif /* _WIN32 */


#if ! defined(HAVE_ARC4RANDOM_BUF) && ! defined(HAVE_ARC4RANDOM)

static unsigned long
gather_time_entropy(void)
{
#ifdef _WIN32
  FILETIME ft;
  GetSystemTimeAsFileTime(&ft); /* never fails */
  return ft.dwHighDateTime ^ ft.dwLowDateTime;
#else
  struct timeval tv;
  int gettimeofday_res;

  gettimeofday_res = gettimeofday(&tv, NULL);

#if defined(NDEBUG)
  (void)gettimeofday_res;
#else
  assert (gettimeofday_res == 0);
#endif  /* defined(NDEBUG) */

  /* Microseconds time is <20 bits entropy */
  return tv.tv_usec;
#endif
}

#endif  /* ! defined(HAVE_ARC4RANDOM_BUF) && ! defined(HAVE_ARC4RANDOM) */


static unsigned long
ENTROPY_DEBUG(const char * label, unsigned long entropy) {
  const char * const EXPAT_ENTROPY_DEBUG = getenv("EXPAT_ENTROPY_DEBUG");
  if (EXPAT_ENTROPY_DEBUG && ! strcmp(EXPAT_ENTROPY_DEBUG, "1")) {
    fprintf(stderr, "Entropy: %s --> 0x%0*lx (%lu bytes)\n",
        label,
        (int)sizeof(entropy) * 2, entropy,
        (unsigned long)sizeof(entropy));
  }
  return entropy;
}

static unsigned long
generate_hash_secret_salt(XML_Parser parser)
{
  unsigned long entropy;
  (void)parser;

  /* "Failproof" high quality providers: */
#if defined(HAVE_ARC4RANDOM_BUF)
  arc4random_buf(&entropy, sizeof(entropy));
  return ENTROPY_DEBUG("arc4random_buf", entropy);
#elif defined(HAVE_ARC4RANDOM)
  writeRandomBytes_arc4random((void *)&entropy, sizeof(entropy));
  return ENTROPY_DEBUG("arc4random", entropy);
#else
  /* Try high quality providers first .. */
#ifdef _WIN32
  if (writeRandomBytes_RtlGenRandom((void *)&entropy, sizeof(entropy))) {
    return ENTROPY_DEBUG("RtlGenRandom", entropy);
  }
#elif defined(HAVE_GETRANDOM) || defined(HAVE_SYSCALL_GETRANDOM)
  if (writeRandomBytes_getrandom_nonblock((void *)&entropy, sizeof(entropy))) {
    return ENTROPY_DEBUG("getrandom", entropy);
  }
#endif
#if ! defined(_WIN32) && defined(XML_DEV_URANDOM)
  if (writeRandomBytes_dev_urandom((void *)&entropy, sizeof(entropy))) {
    return ENTROPY_DEBUG("/dev/urandom", entropy);
  }
#endif  /* ! defined(_WIN32) && defined(XML_DEV_URANDOM) */
  /* .. and self-made low quality for backup: */

  /* Process ID is 0 bits entropy if attacker has local access */
  entropy = gather_time_entropy() ^ getpid();

  /* Factors are 2^31-1 and 2^61-1 (Mersenne primes M31 and M61) */
  if (sizeof(unsigned long) == 4) {
    return ENTROPY_DEBUG("fallback(4)", entropy * 2147483647);
  } else {
    return ENTROPY_DEBUG("fallback(8)",
        entropy * (unsigned long)2305843009213693951ULL);
  }
#endif
}

static unsigned long
get_hash_secret_salt(XML_Parser parser) {
  if (parser->m_parentParser != NULL)
    return get_hash_secret_salt(parser->m_parentParser);
  return parser->m_hash_secret_salt;
}

static XML_Bool  /* only valid for root parser */
startParsing(XML_Parser parser)
{
    /* hash functions must be initialized before setContext() is called */
    if (parser->m_hash_secret_salt == 0)
      parser->m_hash_secret_salt = generate_hash_secret_salt(parser);
    if (parser->m_ns) {
      /* implicit context only set for root parser, since child
         parsers (i.e. external entity parsers) will inherit it
      */
      return setContext(parser, implicitContext);
    }
    return XML_TRUE;
}

XML_Parser XMLCALL
XML_ParserCreate_MM(const XML_Char *encodingName,
                    const XML_Memory_Handling_Suite *memsuite,
                    const XML_Char *nameSep)
{
  return parserCreate(encodingName, memsuite, nameSep, NULL);
}

static XML_Parser
parserCreate(const XML_Char *encodingName,
             const XML_Memory_Handling_Suite *memsuite,
             const XML_Char *nameSep,
             DTD *dtd)
{
  XML_Parser parser;

  if (memsuite) {
    XML_Memory_Handling_Suite *mtemp;
    parser = (XML_Parser)
      memsuite->malloc_fcn(sizeof(struct XML_ParserStruct));
    if (parser != NULL) {
      mtemp = (XML_Memory_Handling_Suite *)&(parser->m_mem);
      mtemp->malloc_fcn = memsuite->malloc_fcn;
      mtemp->realloc_fcn = memsuite->realloc_fcn;
      mtemp->free_fcn = memsuite->free_fcn;
    }
  }
  else {
    XML_Memory_Handling_Suite *mtemp;
    parser = (XML_Parser)malloc(sizeof(struct XML_ParserStruct));
    if (parser != NULL) {
      mtemp = (XML_Memory_Handling_Suite *)&(parser->m_mem);
      mtemp->malloc_fcn = malloc;
      mtemp->realloc_fcn = realloc;
      mtemp->free_fcn = free;
    }
  }

  if (!parser)
    return parser;

  parser->m_buffer = NULL;
  parser->m_bufferLim = NULL;

  parser->m_attsSize = INIT_ATTS_SIZE;
  parser->m_atts = (ATTRIBUTE *)MALLOC(parser, parser->m_attsSize * sizeof(ATTRIBUTE));
  if (parser->m_atts == NULL) {
    FREE(parser, parser);
    return NULL;
  }
#ifdef XML_ATTR_INFO
  parser->m_attInfo = (XML_AttrInfo*)MALLOC(parser, parser->m_attsSize * sizeof(XML_AttrInfo));
  if (parser->m_attInfo == NULL) {
    FREE(parser, parser->m_atts);
    FREE(parser, parser);
    return NULL;
  }
#endif
  parser->m_dataBuf = (XML_Char *)MALLOC(parser, INIT_DATA_BUF_SIZE * sizeof(XML_Char));
  if (parser->m_dataBuf == NULL) {
    FREE(parser, parser->m_atts);
#ifdef XML_ATTR_INFO
    FREE(parser, parser->m_attInfo);
#endif
    FREE(parser, parser);
    return NULL;
  }
  parser->m_dataBufEnd = parser->m_dataBuf + INIT_DATA_BUF_SIZE;

  if (dtd)
    parser->m_dtd = dtd;
  else {
    parser->m_dtd = dtdCreate(&parser->m_mem);
    if (parser->m_dtd == NULL) {
      FREE(parser, parser->m_dataBuf);
      FREE(parser, parser->m_atts);
#ifdef XML_ATTR_INFO
      FREE(parser, parser->m_attInfo);
#endif
      FREE(parser, parser);
      return NULL;
    }
  }

  parser->m_freeBindingList = NULL;
  parser->m_freeTagList = NULL;
  parser->m_freeInternalEntities = NULL;

  parser->m_groupSize = 0;
  parser->m_groupConnector = NULL;

  parser->m_unknownEncodingHandler = NULL;
  parser->m_unknownEncodingHandlerData = NULL;

  parser->m_namespaceSeparator = ASCII_EXCL;
  parser->m_ns = XML_FALSE;
  parser->m_ns_triplets = XML_FALSE;

  parser->m_nsAtts = NULL;
  parser->m_nsAttsVersion = 0;
  parser->m_nsAttsPower = 0;

  parser->m_protocolEncodingName = NULL;

  poolInit(&parser->m_tempPool, &(parser->m_mem));
  poolInit(&parser->m_temp2Pool, &(parser->m_mem));
  parserInit(parser, encodingName);

  if (encodingName && !parser->m_protocolEncodingName) {
    XML_ParserFree(parser);
    return NULL;
  }

  if (nameSep) {
    parser->m_ns = XML_TRUE;
    parser->m_internalEncoding = XmlGetInternalEncodingNS();
    parser->m_namespaceSeparator = *nameSep;
  }
  else {
    parser->m_internalEncoding = XmlGetInternalEncoding();
  }

  return parser;
}

static void
parserInit(XML_Parser parser, const XML_Char *encodingName)
{
  parser->m_processor = prologInitProcessor;
  XmlPrologStateInit(&parser->m_prologState);
  if (encodingName != NULL) {
    parser->m_protocolEncodingName = copyString(encodingName, &(parser->m_mem));
  }
  parser->m_curBase = NULL;
  XmlInitEncoding(&parser->m_initEncoding, &parser->m_encoding, 0);
  parser->m_userData = NULL;
  parser->m_handlerArg = NULL;
  parser->m_startElementHandler = NULL;
  parser->m_endElementHandler = NULL;
  parser->m_characterDataHandler = NULL;
  parser->m_processingInstructionHandler = NULL;
  parser->m_commentHandler = NULL;
  parser->m_startCdataSectionHandler = NULL;
  parser->m_endCdataSectionHandler = NULL;
  parser->m_defaultHandler = NULL;
  parser->m_startDoctypeDeclHandler = NULL;
  parser->m_endDoctypeDeclHandler = NULL;
  parser->m_unparsedEntityDeclHandler = NULL;
  parser->m_notationDeclHandler = NULL;
  parser->m_startNamespaceDeclHandler = NULL;
  parser->m_endNamespaceDeclHandler = NULL;
  parser->m_notStandaloneHandler = NULL;
  parser->m_externalEntityRefHandler = NULL;
  parser->m_externalEntityRefHandlerArg = parser;
  parser->m_skippedEntityHandler = NULL;
  parser->m_elementDeclHandler = NULL;
  parser->m_attlistDeclHandler = NULL;
  parser->m_entityDeclHandler = NULL;
  parser->m_xmlDeclHandler = NULL;
  parser->m_bufferPtr = parser->m_buffer;
  parser->m_bufferEnd = parser->m_buffer;
  parser->m_parseEndByteIndex = 0;
  parser->m_parseEndPtr = NULL;
  parser->m_declElementType = NULL;
  parser->m_declAttributeId = NULL;
  parser->m_declEntity = NULL;
  parser->m_doctypeName = NULL;
  parser->m_doctypeSysid = NULL;
  parser->m_doctypePubid = NULL;
  parser->m_declAttributeType = NULL;
  parser->m_declNotationName = NULL;
  parser->m_declNotationPublicId = NULL;
  parser->m_declAttributeIsCdata = XML_FALSE;
  parser->m_declAttributeIsId = XML_FALSE;
  memset(&parser->m_position, 0, sizeof(POSITION));
  parser->m_errorCode = XML_ERROR_NONE;
  parser->m_eventPtr = NULL;
  parser->m_eventEndPtr = NULL;
  parser->m_positionPtr = NULL;
  parser->m_openInternalEntities = NULL;
  parser->m_defaultExpandInternalEntities = XML_TRUE;
  parser->m_tagLevel = 0;
  parser->m_tagStack = NULL;
  parser->m_inheritedBindings = NULL;
  parser->m_nSpecifiedAtts = 0;
  parser->m_unknownEncodingMem = NULL;
  parser->m_unknownEncodingRelease = NULL;
  parser->m_unknownEncodingData = NULL;
  parser->m_parentParser = NULL;
  parser->m_parsingStatus.parsing = XML_INITIALIZED;
#ifdef XML_DTD
  parser->m_isParamEntity = XML_FALSE;
  parser->m_useForeignDTD = XML_FALSE;
  parser->m_paramEntityParsing = XML_PARAM_ENTITY_PARSING_NEVER;
#endif
  parser->m_hash_secret_salt = 0;
}

/* moves list of bindings to m_freeBindingList */
static void FASTCALL
moveToFreeBindingList(XML_Parser parser, BINDING *bindings)
{
  while (bindings) {
    BINDING *b = bindings;
    bindings = bindings->nextTagBinding;
    b->nextTagBinding = parser->m_freeBindingList;
    parser->m_freeBindingList = b;
  }
}

XML_Bool XMLCALL
XML_ParserReset(XML_Parser parser, const XML_Char *encodingName)
{
  TAG *tStk;
  OPEN_INTERNAL_ENTITY *openEntityList;

  if (parser == NULL)
      return XML_FALSE;

  if (parser->m_parentParser)
    return XML_FALSE;
  /* move m_tagStack to m_freeTagList */
  tStk = parser->m_tagStack;
  while (tStk) {
    TAG *tag = tStk;
    tStk = tStk->parent;
    tag->parent = parser->m_freeTagList;
    moveToFreeBindingList(parser, tag->bindings);
    tag->bindings = NULL;
    parser->m_freeTagList = tag;
  }
  /* move m_openInternalEntities to m_freeInternalEntities */
  openEntityList = parser->m_openInternalEntities;
  while (openEntityList) {
    OPEN_INTERNAL_ENTITY *openEntity = openEntityList;
    openEntityList = openEntity->next;
    openEntity->next = parser->m_freeInternalEntities;
    parser->m_freeInternalEntities = openEntity;
  }
  moveToFreeBindingList(parser, parser->m_inheritedBindings);
  FREE(parser, parser->m_unknownEncodingMem);
  if (parser->m_unknownEncodingRelease)
    parser->m_unknownEncodingRelease(parser->m_unknownEncodingData);
  poolClear(&parser->m_tempPool);
  poolClear(&parser->m_temp2Pool);
  FREE(parser, (void *)parser->m_protocolEncodingName);
  parser->m_protocolEncodingName = NULL;
  parserInit(parser, encodingName);
  dtdReset(parser->m_dtd, &parser->m_mem);
  return XML_TRUE;
}

enum XML_Status XMLCALL
XML_SetEncoding(XML_Parser parser, const XML_Char *encodingName)
{
  if (parser == NULL)
      return XML_STATUS_ERROR;
  /* Block after XML_Parse()/XML_ParseBuffer() has been called.
     XXX There's no way for the caller to determine which of the
     XXX possible error cases caused the XML_STATUS_ERROR return.
  */
  if (parser->m_parsingStatus.parsing == XML_PARSING || parser->m_parsingStatus.parsing == XML_SUSPENDED)
    return XML_STATUS_ERROR;

  /* Get rid of any previous encoding name */
  FREE(parser, (void *)parser->m_protocolEncodingName);

  if (encodingName == NULL)
    /* No new encoding name */
    parser->m_protocolEncodingName = NULL;
  else {
    /* Copy the new encoding name into allocated memory */
    parser->m_protocolEncodingName = copyString(encodingName, &(parser->m_mem));
    if (!parser->m_protocolEncodingName)
      return XML_STATUS_ERROR;
  }
  return XML_STATUS_OK;
}

XML_Parser XMLCALL
XML_ExternalEntityParserCreate(XML_Parser oldParser,
                               const XML_Char *context,
                               const XML_Char *encodingName)
{
  XML_Parser parser = oldParser;
  DTD *newDtd = NULL;
  DTD *oldDtd;
  XML_StartElementHandler oldStartElementHandler;
  XML_EndElementHandler oldEndElementHandler;
  XML_CharacterDataHandler oldCharacterDataHandler;
  XML_ProcessingInstructionHandler oldProcessingInstructionHandler;
  XML_CommentHandler oldCommentHandler;
  XML_StartCdataSectionHandler oldStartCdataSectionHandler;
  XML_EndCdataSectionHandler oldEndCdataSectionHandler;
  XML_DefaultHandler oldDefaultHandler;
  XML_UnparsedEntityDeclHandler oldUnparsedEntityDeclHandler;
  XML_NotationDeclHandler oldNotationDeclHandler;
  XML_StartNamespaceDeclHandler oldStartNamespaceDeclHandler;
  XML_EndNamespaceDeclHandler oldEndNamespaceDeclHandler;
  XML_NotStandaloneHandler oldNotStandaloneHandler;
  XML_ExternalEntityRefHandler oldExternalEntityRefHandler;
  XML_SkippedEntityHandler oldSkippedEntityHandler;
  XML_UnknownEncodingHandler oldUnknownEncodingHandler;
  XML_ElementDeclHandler oldElementDeclHandler;
  XML_AttlistDeclHandler oldAttlistDeclHandler;
  XML_EntityDeclHandler oldEntityDeclHandler;
  XML_XmlDeclHandler oldXmlDeclHandler;
  ELEMENT_TYPE * oldDeclElementType;

  void *oldUserData;
  void *oldHandlerArg;
  XML_Bool oldDefaultExpandInternalEntities;
  XML_Parser oldExternalEntityRefHandlerArg;
#ifdef XML_DTD
  enum XML_ParamEntityParsing oldParamEntityParsing;
  int oldInEntityValue;
#endif
  XML_Bool oldns_triplets;
  /* Note that the new parser shares the same hash secret as the old
     parser, so that dtdCopy and copyEntityTable can lookup values
     from hash tables associated with either parser without us having
     to worry which hash secrets each table has.
  */
  unsigned long oldhash_secret_salt;

  /* Validate the oldParser parameter before we pull everything out of it */
  if (oldParser == NULL)
    return NULL;

  /* Stash the original parser contents on the stack */
  oldDtd = parser->m_dtd;
  oldStartElementHandler = parser->m_startElementHandler;
  oldEndElementHandler = parser->m_endElementHandler;
  oldCharacterDataHandler = parser->m_characterDataHandler;
  oldProcessingInstructionHandler = parser->m_processingInstructionHandler;
  oldCommentHandler = parser->m_commentHandler;
  oldStartCdataSectionHandler = parser->m_startCdataSectionHandler;
  oldEndCdataSectionHandler = parser->m_endCdataSectionHandler;
  oldDefaultHandler = parser->m_defaultHandler;
  oldUnparsedEntityDeclHandler = parser->m_unparsedEntityDeclHandler;
  oldNotationDeclHandler = parser->m_notationDeclHandler;
  oldStartNamespaceDeclHandler = parser->m_startNamespaceDeclHandler;
  oldEndNamespaceDeclHandler = parser->m_endNamespaceDeclHandler;
  oldNotStandaloneHandler = parser->m_notStandaloneHandler;
  oldExternalEntityRefHandler = parser->m_externalEntityRefHandler;
  oldSkippedEntityHandler = parser->m_skippedEntityHandler;
  oldUnknownEncodingHandler = parser->m_unknownEncodingHandler;
  oldElementDeclHandler = parser->m_elementDeclHandler;
  oldAttlistDeclHandler = parser->m_attlistDeclHandler;
  oldEntityDeclHandler = parser->m_entityDeclHandler;
  oldXmlDeclHandler = parser->m_xmlDeclHandler;
  oldDeclElementType = parser->m_declElementType;

  oldUserData = parser->m_userData;
  oldHandlerArg = parser->m_handlerArg;
  oldDefaultExpandInternalEntities = parser->m_defaultExpandInternalEntities;
  oldExternalEntityRefHandlerArg = parser->m_externalEntityRefHandlerArg;
#ifdef XML_DTD
  oldParamEntityParsing = parser->m_paramEntityParsing;
  oldInEntityValue = parser->m_prologState.inEntityValue;
#endif
  oldns_triplets = parser->m_ns_triplets;
  /* Note that the new parser shares the same hash secret as the old
     parser, so that dtdCopy and copyEntityTable can lookup values
     from hash tables associated with either parser without us having
     to worry which hash secrets each table has.
  */
  oldhash_secret_salt = parser->m_hash_secret_salt;

#ifdef XML_DTD
  if (!context)
    newDtd = oldDtd;
#endif /* XML_DTD */

  /* Note that the magical uses of the pre-processor to make field
     access look more like C++ require that `parser' be overwritten
     here.  This makes this function more painful to follow than it
     would be otherwise.
  */
  if (parser->m_ns) {
    XML_Char tmp[2];
    *tmp = parser->m_namespaceSeparator;
    parser = parserCreate(encodingName, &parser->m_mem, tmp, newDtd);
  }
  else {
    parser = parserCreate(encodingName, &parser->m_mem, NULL, newDtd);
  }

  if (!parser)
    return NULL;

  parser->m_startElementHandler = oldStartElementHandler;
  parser->m_endElementHandler = oldEndElementHandler;
  parser->m_characterDataHandler = oldCharacterDataHandler;
  parser->m_processingInstructionHandler = oldProcessingInstructionHandler;
  parser->m_commentHandler = oldCommentHandler;
  parser->m_startCdataSectionHandler = oldStartCdataSectionHandler;
  parser->m_endCdataSectionHandler = oldEndCdataSectionHandler;
  parser->m_defaultHandler = oldDefaultHandler;
  parser->m_unparsedEntityDeclHandler = oldUnparsedEntityDeclHandler;
  parser->m_notationDeclHandler = oldNotationDeclHandler;
  parser->m_startNamespaceDeclHandler = oldStartNamespaceDeclHandler;
  parser->m_endNamespaceDeclHandler = oldEndNamespaceDeclHandler;
  parser->m_notStandaloneHandler = oldNotStandaloneHandler;
  parser->m_externalEntityRefHandler = oldExternalEntityRefHandler;
  parser->m_skippedEntityHandler = oldSkippedEntityHandler;
  parser->m_unknownEncodingHandler = oldUnknownEncodingHandler;
  parser->m_elementDeclHandler = oldElementDeclHandler;
  parser->m_attlistDeclHandler = oldAttlistDeclHandler;
  parser->m_entityDeclHandler = oldEntityDeclHandler;
  parser->m_xmlDeclHandler = oldXmlDeclHandler;
  parser->m_declElementType = oldDeclElementType;
  parser->m_userData = oldUserData;
  if (oldUserData == oldHandlerArg)
    parser->m_handlerArg = parser->m_userData;
  else
    parser->m_handlerArg = parser;
  if (oldExternalEntityRefHandlerArg != oldParser)
    parser->m_externalEntityRefHandlerArg = oldExternalEntityRefHandlerArg;
  parser->m_defaultExpandInternalEntities = oldDefaultExpandInternalEntities;
  parser->m_ns_triplets = oldns_triplets;
  parser->m_hash_secret_salt = oldhash_secret_salt;
  parser->m_parentParser = oldParser;
#ifdef XML_DTD
  parser->m_paramEntityParsing = oldParamEntityParsing;
  parser->m_prologState.inEntityValue = oldInEntityValue;
  if (context) {
#endif /* XML_DTD */
    if (!dtdCopy(oldParser, parser->m_dtd, oldDtd, &parser->m_mem)
      || !setContext(parser, context)) {
      XML_ParserFree(parser);
      return NULL;
    }
    parser->m_processor = externalEntityInitProcessor;
#ifdef XML_DTD
  }
  else {
    /* The DTD instance referenced by parser->m_dtd is shared between the document's
       root parser and external PE parsers, therefore one does not need to
       call setContext. In addition, one also *must* not call setContext,
       because this would overwrite existing prefix->binding pointers in
       parser->m_dtd with ones that get destroyed with the external PE parser.
       This would leave those prefixes with dangling pointers.
    */
    parser->m_isParamEntity = XML_TRUE;
    XmlPrologStateInitExternalEntity(&parser->m_prologState);
    parser->m_processor = externalParEntInitProcessor;
  }
#endif /* XML_DTD */
  return parser;
}

static void FASTCALL
destroyBindings(BINDING *bindings, XML_Parser parser)
{
  for (;;) {
    BINDING *b = bindings;
    if (!b)
      break;
    bindings = b->nextTagBinding;
    FREE(parser, b->uri);
    FREE(parser, b);
  }
}

void XMLCALL
XML_ParserFree(XML_Parser parser)
{
  TAG *tagList;
  OPEN_INTERNAL_ENTITY *entityList;
  if (parser == NULL)
    return;
  /* free m_tagStack and m_freeTagList */
  tagList = parser->m_tagStack;
  for (;;) {
    TAG *p;
    if (tagList == NULL) {
      if (parser->m_freeTagList == NULL)
        break;
      tagList = parser->m_freeTagList;
      parser->m_freeTagList = NULL;
    }
    p = tagList;
    tagList = tagList->parent;
    FREE(parser, p->buf);
    destroyBindings(p->bindings, parser);
    FREE(parser, p);
  }
  /* free m_openInternalEntities and m_freeInternalEntities */
  entityList = parser->m_openInternalEntities;
  for (;;) {
    OPEN_INTERNAL_ENTITY *openEntity;
    if (entityList == NULL) {
      if (parser->m_freeInternalEntities == NULL)
        break;
      entityList = parser->m_freeInternalEntities;
      parser->m_freeInternalEntities = NULL;
    }
    openEntity = entityList;
    entityList = entityList->next;
    FREE(parser, openEntity);
  }

  destroyBindings(parser->m_freeBindingList, parser);
  destroyBindings(parser->m_inheritedBindings, parser);
  poolDestroy(&parser->m_tempPool);
  poolDestroy(&parser->m_temp2Pool);
  FREE(parser, (void *)parser->m_protocolEncodingName);
#ifdef XML_DTD
  /* external parameter entity parsers share the DTD structure
     parser->m_dtd with the root parser, so we must not destroy it
  */
  if (!parser->m_isParamEntity && parser->m_dtd)
#else
  if (parser->m_dtd)
#endif /* XML_DTD */
    dtdDestroy(parser->m_dtd, (XML_Bool)!parser->m_parentParser, &parser->m_mem);
  FREE(parser, (void *)parser->m_atts);
#ifdef XML_ATTR_INFO
  FREE(parser, (void *)parser->m_attInfo);
#endif
  FREE(parser, parser->m_groupConnector);
  FREE(parser, parser->m_buffer);
  FREE(parser, parser->m_dataBuf);
  FREE(parser, parser->m_nsAtts);
  FREE(parser, parser->m_unknownEncodingMem);
  if (parser->m_unknownEncodingRelease)
    parser->m_unknownEncodingRelease(parser->m_unknownEncodingData);
  FREE(parser, parser);
}

void XMLCALL
XML_UseParserAsHandlerArg(XML_Parser parser)
{
  if (parser != NULL)
    parser->m_handlerArg = parser;
}

enum XML_Error XMLCALL
XML_UseForeignDTD(XML_Parser parser, XML_Bool useDTD)
{
  if (parser == NULL)
    return XML_ERROR_INVALID_ARGUMENT;
#ifdef XML_DTD
  /* block after XML_Parse()/XML_ParseBuffer() has been called */
  if (parser->m_parsingStatus.parsing == XML_PARSING || parser->m_parsingStatus.parsing == XML_SUSPENDED)
    return XML_ERROR_CANT_CHANGE_FEATURE_ONCE_PARSING;
  parser->m_useForeignDTD = useDTD;
  return XML_ERROR_NONE;
#else
  return XML_ERROR_FEATURE_REQUIRES_XML_DTD;
#endif
}

void XMLCALL
XML_SetReturnNSTriplet(XML_Parser parser, int do_nst)
{
  if (parser == NULL)
    return;
  /* block after XML_Parse()/XML_ParseBuffer() has been called */
  if (parser->m_parsingStatus.parsing == XML_PARSING || parser->m_parsingStatus.parsing == XML_SUSPENDED)
    return;
  parser->m_ns_triplets = do_nst ? XML_TRUE : XML_FALSE;
}

void XMLCALL
XML_SetUserData(XML_Parser parser, void *p)
{
  if (parser == NULL)
    return;
  if (parser->m_handlerArg == parser->m_userData)
    parser->m_handlerArg = parser->m_userData = p;
  else
    parser->m_userData = p;
}

enum XML_Status XMLCALL
XML_SetBase(XML_Parser parser, const XML_Char *p)
{
  if (parser == NULL)
    return XML_STATUS_ERROR;
  if (p) {
    p = poolCopyString(&parser->m_dtd->pool, p);
    if (!p)
      return XML_STATUS_ERROR;
    parser->m_curBase = p;
  }
  else
    parser->m_curBase = NULL;
  return XML_STATUS_OK;
}

const XML_Char * XMLCALL
XML_GetBase(XML_Parser parser)
{
  if (parser == NULL)
    return NULL;
  return parser->m_curBase;
}

int XMLCALL
XML_GetSpecifiedAttributeCount(XML_Parser parser)
{
  if (parser == NULL)
    return -1;
  return parser->m_nSpecifiedAtts;
}

int XMLCALL
XML_GetIdAttributeIndex(XML_Parser parser)
{
  if (parser == NULL)
    return -1;
  return parser->m_idAttIndex;
}

#ifdef XML_ATTR_INFO
const XML_AttrInfo * XMLCALL
XML_GetAttributeInfo(XML_Parser parser)
{
  if (parser == NULL)
    return NULL;
  return parser->m_attInfo;
}
#endif

void XMLCALL
XML_SetElementHandler(XML_Parser parser,
                      XML_StartElementHandler start,
                      XML_EndElementHandler end)
{
  if (parser == NULL)
    return;
  parser->m_startElementHandler = start;
  parser->m_endElementHandler = end;
}

void XMLCALL
XML_SetStartElementHandler(XML_Parser parser,
                           XML_StartElementHandler start) {
  if (parser != NULL)
    parser->m_startElementHandler = start;
}

void XMLCALL
XML_SetEndElementHandler(XML_Parser parser,
                         XML_EndElementHandler end) {
  if (parser != NULL)
    parser->m_endElementHandler = end;
}

void XMLCALL
XML_SetCharacterDataHandler(XML_Parser parser,
                            XML_CharacterDataHandler handler)
{
  if (parser != NULL)
    parser->m_characterDataHandler = handler;
}

void XMLCALL
XML_SetProcessingInstructionHandler(XML_Parser parser,
                                    XML_ProcessingInstructionHandler handler)
{
  if (parser != NULL)
    parser->m_processingInstructionHandler = handler;
}

void XMLCALL
XML_SetCommentHandler(XML_Parser parser,
                      XML_CommentHandler handler)
{
  if (parser != NULL)
    parser->m_commentHandler = handler;
}

void XMLCALL
XML_SetCdataSectionHandler(XML_Parser parser,
                           XML_StartCdataSectionHandler start,
                           XML_EndCdataSectionHandler end)
{
  if (parser == NULL)
    return;
  parser->m_startCdataSectionHandler = start;
  parser->m_endCdataSectionHandler = end;
}

void XMLCALL
XML_SetStartCdataSectionHandler(XML_Parser parser,
                                XML_StartCdataSectionHandler start) {
  if (parser != NULL)
    parser->m_startCdataSectionHandler = start;
}

void XMLCALL
XML_SetEndCdataSectionHandler(XML_Parser parser,
                              XML_EndCdataSectionHandler end) {
  if (parser != NULL)
    parser->m_endCdataSectionHandler = end;
}

void XMLCALL
XML_SetDefaultHandler(XML_Parser parser,
                      XML_DefaultHandler handler)
{
  if (parser == NULL)
    return;
  parser->m_defaultHandler = handler;
  parser->m_defaultExpandInternalEntities = XML_FALSE;
}

void XMLCALL
XML_SetDefaultHandlerExpand(XML_Parser parser,
                            XML_DefaultHandler handler)
{
  if (parser == NULL)
    return;
  parser->m_defaultHandler = handler;
  parser->m_defaultExpandInternalEntities = XML_TRUE;
}

void XMLCALL
XML_SetDoctypeDeclHandler(XML_Parser parser,
                          XML_StartDoctypeDeclHandler start,
                          XML_EndDoctypeDeclHandler end)
{
  if (parser == NULL)
    return;
  parser->m_startDoctypeDeclHandler = start;
  parser->m_endDoctypeDeclHandler = end;
}

void XMLCALL
XML_SetStartDoctypeDeclHandler(XML_Parser parser,
                               XML_StartDoctypeDeclHandler start) {
  if (parser != NULL)
    parser->m_startDoctypeDeclHandler = start;
}

void XMLCALL
XML_SetEndDoctypeDeclHandler(XML_Parser parser,
                             XML_EndDoctypeDeclHandler end) {
  if (parser != NULL)
    parser->m_endDoctypeDeclHandler = end;
}

void XMLCALL
XML_SetUnparsedEntityDeclHandler(XML_Parser parser,
                                 XML_UnparsedEntityDeclHandler handler)
{
  if (parser != NULL)
    parser->m_unparsedEntityDeclHandler = handler;
}

void XMLCALL
XML_SetNotationDeclHandler(XML_Parser parser,
                           XML_NotationDeclHandler handler)
{
  if (parser != NULL)
    parser->m_notationDeclHandler = handler;
}

void XMLCALL
XML_SetNamespaceDeclHandler(XML_Parser parser,
                            XML_StartNamespaceDeclHandler start,
                            XML_EndNamespaceDeclHandler end)
{
  if (parser == NULL)
    return;
  parser->m_startNamespaceDeclHandler = start;
  parser->m_endNamespaceDeclHandler = end;
}

void XMLCALL
XML_SetStartNamespaceDeclHandler(XML_Parser parser,
                                 XML_StartNamespaceDeclHandler start) {
  if (parser != NULL)
    parser->m_startNamespaceDeclHandler = start;
}

void XMLCALL
XML_SetEndNamespaceDeclHandler(XML_Parser parser,
                               XML_EndNamespaceDeclHandler end) {
  if (parser != NULL)
    parser->m_endNamespaceDeclHandler = end;
}

void XMLCALL
XML_SetNotStandaloneHandler(XML_Parser parser,
                            XML_NotStandaloneHandler handler)
{
  if (parser != NULL)
    parser->m_notStandaloneHandler = handler;
}

void XMLCALL
XML_SetExternalEntityRefHandler(XML_Parser parser,
                                XML_ExternalEntityRefHandler handler)
{
  if (parser != NULL)
    parser->m_externalEntityRefHandler = handler;
}

void XMLCALL
XML_SetExternalEntityRefHandlerArg(XML_Parser parser, void *arg)
{
  if (parser == NULL)
    return;
  if (arg)
    parser->m_externalEntityRefHandlerArg = (XML_Parser)arg;
  else
    parser->m_externalEntityRefHandlerArg = parser;
}

void XMLCALL
XML_SetSkippedEntityHandler(XML_Parser parser,
                            XML_SkippedEntityHandler handler)
{
  if (parser != NULL)
    parser->m_skippedEntityHandler = handler;
}

void XMLCALL
XML_SetUnknownEncodingHandler(XML_Parser parser,
                              XML_UnknownEncodingHandler handler,
                              void *data)
{
  if (parser == NULL)
    return;
  parser->m_unknownEncodingHandler = handler;
  parser->m_unknownEncodingHandlerData = data;
}

void XMLCALL
XML_SetElementDeclHandler(XML_Parser parser,
                          XML_ElementDeclHandler eldecl)
{
  if (parser != NULL)
    parser->m_elementDeclHandler = eldecl;
}

void XMLCALL
XML_SetAttlistDeclHandler(XML_Parser parser,
                          XML_AttlistDeclHandler attdecl)
{
  if (parser != NULL)
    parser->m_attlistDeclHandler = attdecl;
}

void XMLCALL
XML_SetEntityDeclHandler(XML_Parser parser,
                         XML_EntityDeclHandler handler)
{
  if (parser != NULL)
    parser->m_entityDeclHandler = handler;
}

void XMLCALL
XML_SetXmlDeclHandler(XML_Parser parser,
                      XML_XmlDeclHandler handler) {
  if (parser != NULL)
    parser->m_xmlDeclHandler = handler;
}

int XMLCALL
XML_SetParamEntityParsing(XML_Parser parser,
                          enum XML_ParamEntityParsing peParsing)
{
  if (parser == NULL)
    return 0;
  /* block after XML_Parse()/XML_ParseBuffer() has been called */
  if (parser->m_parsingStatus.parsing == XML_PARSING || parser->m_parsingStatus.parsing == XML_SUSPENDED)
    return 0;
#ifdef XML_DTD
  parser->m_paramEntityParsing = peParsing;
  return 1;
#else
  return peParsing == XML_PARAM_ENTITY_PARSING_NEVER;
#endif
}

int XMLCALL
XML_SetHashSalt(XML_Parser parser,
                unsigned long hash_salt)
{
  if (parser == NULL)
    return 0;
  if (parser->m_parentParser)
    return XML_SetHashSalt(parser->m_parentParser, hash_salt);
  /* block after XML_Parse()/XML_ParseBuffer() has been called */
  if (parser->m_parsingStatus.parsing == XML_PARSING || parser->m_parsingStatus.parsing == XML_SUSPENDED)
    return 0;
  parser->m_hash_secret_salt = hash_salt;
  return 1;
}

enum XML_Status XMLCALL
XML_Parse(XML_Parser parser, const char *s, int len, int isFinal)
{
  if ((parser == NULL) || (len < 0) || ((s == NULL) && (len != 0))) {
    if (parser != NULL)
      parser->m_errorCode = XML_ERROR_INVALID_ARGUMENT;
    return XML_STATUS_ERROR;
  }
  switch (parser->m_parsingStatus.parsing) {
  case XML_SUSPENDED:
    parser->m_errorCode = XML_ERROR_SUSPENDED;
    return XML_STATUS_ERROR;
  case XML_FINISHED:
    parser->m_errorCode = XML_ERROR_FINISHED;
    return XML_STATUS_ERROR;
  case XML_INITIALIZED:
    if (parser->m_parentParser == NULL && !startParsing(parser)) {
      parser->m_errorCode = XML_ERROR_NO_MEMORY;
      return XML_STATUS_ERROR;
    }
    /* fall through */
  default:
    parser->m_parsingStatus.parsing = XML_PARSING;
  }

  if (len == 0) {
    parser->m_parsingStatus.finalBuffer = (XML_Bool)isFinal;
    if (!isFinal)
      return XML_STATUS_OK;
    parser->m_positionPtr = parser->m_bufferPtr;
    parser->m_parseEndPtr = parser->m_bufferEnd;

    /* If data are left over from last buffer, and we now know that these
       data are the final chunk of input, then we have to check them again
       to detect errors based on that fact.
    */
    parser->m_errorCode = parser->m_processor(parser, parser->m_bufferPtr, parser->m_parseEndPtr, &parser->m_bufferPtr);

    if (parser->m_errorCode == XML_ERROR_NONE) {
      switch (parser->m_parsingStatus.parsing) {
      case XML_SUSPENDED:
        /* It is hard to be certain, but it seems that this case
         * cannot occur.  This code is cleaning up a previous parse
         * with no new data (since len == 0).  Changing the parsing
         * state requires getting to execute a handler function, and
         * there doesn't seem to be an opportunity for that while in
         * this circumstance.
         *
         * Given the uncertainty, we retain the code but exclude it
         * from coverage tests.
         *
         * LCOV_EXCL_START
         */
        XmlUpdatePosition(parser->m_encoding, parser->m_positionPtr, parser->m_bufferPtr, &parser->m_position);
        parser->m_positionPtr = parser->m_bufferPtr;
        return XML_STATUS_SUSPENDED;
        /* LCOV_EXCL_STOP */
      case XML_INITIALIZED:
      case XML_PARSING:
        parser->m_parsingStatus.parsing = XML_FINISHED;
        /* fall through */
      default:
        return XML_STATUS_OK;
      }
    }
    parser->m_eventEndPtr = parser->m_eventPtr;
    parser->m_processor = errorProcessor;
    return XML_STATUS_ERROR;
  }
#ifndef XML_CONTEXT_BYTES
  else if (parser->m_bufferPtr == parser->m_bufferEnd) {
    const char *end;
    int nLeftOver;
    enum XML_Status result;
    /* Detect overflow (a+b > MAX <==> b > MAX-a) */
    if (len > ((XML_Size)-1) / 2 - parser->m_parseEndByteIndex) {
       parser->m_errorCode = XML_ERROR_NO_MEMORY;
       parser->m_eventPtr = parser->m_eventEndPtr = NULL;
       parser->m_processor = errorProcessor;
       return XML_STATUS_ERROR;
    }
    parser->m_parseEndByteIndex += len;
    parser->m_positionPtr = s;
    parser->m_parsingStatus.finalBuffer = (XML_Bool)isFinal;

    parser->m_errorCode = parser->m_processor(parser, s, parser->m_parseEndPtr = s + len, &end);

    if (parser->m_errorCode != XML_ERROR_NONE) {
      parser->m_eventEndPtr = parser->m_eventPtr;
      parser->m_processor = errorProcessor;
      return XML_STATUS_ERROR;
    }
    else {
      switch (parser->m_parsingStatus.parsing) {
      case XML_SUSPENDED:
        result = XML_STATUS_SUSPENDED;
        break;
      case XML_INITIALIZED:
      case XML_PARSING:
        if (isFinal) {
          parser->m_parsingStatus.parsing = XML_FINISHED;
          return XML_STATUS_OK;
        }
      /* fall through */
      default:
        result = XML_STATUS_OK;
      }
    }

    XmlUpdatePosition(parser->m_encoding, parser->m_positionPtr, end, &parser->m_position);
    nLeftOver = s + len - end;
    if (nLeftOver) {
      if (parser->m_buffer == NULL || nLeftOver > parser->m_bufferLim - parser->m_buffer) {
        /* avoid _signed_ integer overflow */
        char *temp = NULL;
        const int bytesToAllocate = (int)((unsigned)len * 2U);
        if (bytesToAllocate > 0) {
          temp = (char *)REALLOC(parser, parser->m_buffer, bytesToAllocate);
        }
        if (temp == NULL) {
          parser->m_errorCode = XML_ERROR_NO_MEMORY;
          parser->m_eventPtr = parser->m_eventEndPtr = NULL;
          parser->m_processor = errorProcessor;
          return XML_STATUS_ERROR;
        }
        parser->m_buffer = temp;
        parser->m_bufferLim = parser->m_buffer + bytesToAllocate;
      }
      memcpy(parser->m_buffer, end, nLeftOver);
    }
    parser->m_bufferPtr = parser->m_buffer;
    parser->m_bufferEnd = parser->m_buffer + nLeftOver;
    parser->m_positionPtr = parser->m_bufferPtr;
    parser->m_parseEndPtr = parser->m_bufferEnd;
    parser->m_eventPtr = parser->m_bufferPtr;
    parser->m_eventEndPtr = parser->m_bufferPtr;
    return result;
  }
#endif  /* not defined XML_CONTEXT_BYTES */
  else {
    void *buff = XML_GetBuffer(parser, len);
    if (buff == NULL)
      return XML_STATUS_ERROR;
    else {
      memcpy(buff, s, len);
      return XML_ParseBuffer(parser, len, isFinal);
    }
  }
}

enum XML_Status XMLCALL
XML_ParseBuffer(XML_Parser parser, int len, int isFinal)
{
  const char *start;
  enum XML_Status result = XML_STATUS_OK;

  if (parser == NULL)
    return XML_STATUS_ERROR;
  switch (parser->m_parsingStatus.parsing) {
  case XML_SUSPENDED:
    parser->m_errorCode = XML_ERROR_SUSPENDED;
    return XML_STATUS_ERROR;
  case XML_FINISHED:
    parser->m_errorCode = XML_ERROR_FINISHED;
    return XML_STATUS_ERROR;
  case XML_INITIALIZED:
    if (parser->m_parentParser == NULL && !startParsing(parser)) {
      parser->m_errorCode = XML_ERROR_NO_MEMORY;
      return XML_STATUS_ERROR;
    }
    /* fall through */
  default:
    parser->m_parsingStatus.parsing = XML_PARSING;
  }

  start = parser->m_bufferPtr;
  parser->m_positionPtr = start;
  parser->m_bufferEnd += len;
  parser->m_parseEndPtr = parser->m_bufferEnd;
  parser->m_parseEndByteIndex += len;
  parser->m_parsingStatus.finalBuffer = (XML_Bool)isFinal;

  parser->m_errorCode = parser->m_processor(parser, start, parser->m_parseEndPtr, &parser->m_bufferPtr);

  if (parser->m_errorCode != XML_ERROR_NONE) {
    parser->m_eventEndPtr = parser->m_eventPtr;
    parser->m_processor = errorProcessor;
    return XML_STATUS_ERROR;
  }
  else {
    switch (parser->m_parsingStatus.parsing) {
    case XML_SUSPENDED:
      result = XML_STATUS_SUSPENDED;
      break;
    case XML_INITIALIZED:
    case XML_PARSING:
      if (isFinal) {
        parser->m_parsingStatus.parsing = XML_FINISHED;
        return result;
      }
    default: ;  /* should not happen */
    }
  }

  XmlUpdatePosition(parser->m_encoding, parser->m_positionPtr, parser->m_bufferPtr, &parser->m_position);
  parser->m_positionPtr = parser->m_bufferPtr;
  return result;
}

void * XMLCALL
XML_GetBuffer(XML_Parser parser, int len)
{
  if (parser == NULL)
    return NULL;
  if (len < 0) {
    parser->m_errorCode = XML_ERROR_NO_MEMORY;
    return NULL;
  }
  switch (parser->m_parsingStatus.parsing) {
  case XML_SUSPENDED:
    parser->m_errorCode = XML_ERROR_SUSPENDED;
    return NULL;
  case XML_FINISHED:
    parser->m_errorCode = XML_ERROR_FINISHED;
    return NULL;
  default: ;
  }

  if (len > EXPAT_SAFE_PTR_DIFF(parser->m_bufferLim, parser->m_bufferEnd)) {
#ifdef XML_CONTEXT_BYTES
    int keep;
#endif  /* defined XML_CONTEXT_BYTES */
    /* Do not invoke signed arithmetic overflow: */
    int neededSize = (int) ((unsigned)len +
                            (unsigned)EXPAT_SAFE_PTR_DIFF(parser->m_bufferEnd,
                                                          parser->m_bufferPtr));
    if (neededSize < 0) {
      parser->m_errorCode = XML_ERROR_NO_MEMORY;
      return NULL;
    }
#ifdef XML_CONTEXT_BYTES
    keep = (int)EXPAT_SAFE_PTR_DIFF(parser->m_bufferPtr, parser->m_buffer);
    if (keep > XML_CONTEXT_BYTES)
      keep = XML_CONTEXT_BYTES;
    neededSize += keep;
#endif  /* defined XML_CONTEXT_BYTES */
    if (neededSize <= EXPAT_SAFE_PTR_DIFF(parser->m_bufferLim, parser->m_buffer)) {
#ifdef XML_CONTEXT_BYTES
      if (keep < EXPAT_SAFE_PTR_DIFF(parser->m_bufferPtr, parser->m_buffer)) {
          int offset = (int)EXPAT_SAFE_PTR_DIFF(parser->m_bufferPtr, parser->m_buffer) - keep;
        /* The buffer pointers cannot be NULL here; we have at least some bytes in the buffer */
        memmove(parser->m_buffer, &parser->m_buffer[offset], parser->m_bufferEnd - parser->m_bufferPtr + keep);
        parser->m_bufferEnd -= offset;
        parser->m_bufferPtr -= offset;
      }
#else
      if (parser->m_buffer && parser->m_bufferPtr) {
        memmove(parser->m_buffer, parser->m_bufferPtr,
                EXPAT_SAFE_PTR_DIFF(parser->m_bufferEnd, parser->m_bufferPtr));
        parser->m_bufferEnd = parser->m_buffer +
            EXPAT_SAFE_PTR_DIFF(parser->m_bufferEnd, parser->m_bufferPtr);
        parser->m_bufferPtr = parser->m_buffer;
      }
#endif  /* not defined XML_CONTEXT_BYTES */
    }
    else {
      char *newBuf;
      int bufferSize = (int)EXPAT_SAFE_PTR_DIFF(parser->m_bufferLim, parser->m_bufferPtr);
      if (bufferSize == 0)
        bufferSize = INIT_BUFFER_SIZE;
      do {
        /* Do not invoke signed arithmetic overflow: */
        bufferSize = (int) (2U * (unsigned) bufferSize);
      } while (bufferSize < neededSize && bufferSize > 0);
      if (bufferSize <= 0) {
        parser->m_errorCode = XML_ERROR_NO_MEMORY;
        return NULL;
      }
      newBuf = (char *)MALLOC(parser, bufferSize);
      if (newBuf == 0) {
        parser->m_errorCode = XML_ERROR_NO_MEMORY;
        return NULL;
      }
      parser->m_bufferLim = newBuf + bufferSize;
#ifdef XML_CONTEXT_BYTES
      if (parser->m_bufferPtr) {
        int keep = (int)EXPAT_SAFE_PTR_DIFF(parser->m_bufferPtr, parser->m_buffer);
        if (keep > XML_CONTEXT_BYTES)
          keep = XML_CONTEXT_BYTES;
        memcpy(newBuf, &parser->m_bufferPtr[-keep],
               EXPAT_SAFE_PTR_DIFF(parser->m_bufferEnd, parser->m_bufferPtr) + keep);
        FREE(parser, parser->m_buffer);
        parser->m_buffer = newBuf;
        parser->m_bufferEnd = parser->m_buffer +
            EXPAT_SAFE_PTR_DIFF(parser->m_bufferEnd, parser->m_bufferPtr) + keep;
        parser->m_bufferPtr = parser->m_buffer + keep;
      }
      else {
        /* This must be a brand new buffer with no data in it yet */
        parser->m_bufferEnd = newBuf;
        parser->m_bufferPtr = parser->m_buffer = newBuf;
      }
#else
      if (parser->m_bufferPtr) {
        memcpy(newBuf, parser->m_bufferPtr,
               EXPAT_SAFE_PTR_DIFF(parser->m_bufferEnd, parser->m_bufferPtr));
        FREE(parser, parser->m_buffer);
        parser->m_bufferEnd = newBuf +
            EXPAT_SAFE_PTR_DIFF(parser->m_bufferEnd, parser->m_bufferPtr);
      }
      else {
        /* This must be a brand new buffer with no data in it yet */
        parser->m_bufferEnd = newBuf;
      }
      parser->m_bufferPtr = parser->m_buffer = newBuf;
#endif  /* not defined XML_CONTEXT_BYTES */
    }
    parser->m_eventPtr = parser->m_eventEndPtr = NULL;
    parser->m_positionPtr = NULL;
  }
  return parser->m_bufferEnd;
}

enum XML_Status XMLCALL
XML_StopParser(XML_Parser parser, XML_Bool resumable)
{
  if (parser == NULL)
    return XML_STATUS_ERROR;
  switch (parser->m_parsingStatus.parsing) {
  case XML_SUSPENDED:
    if (resumable) {
      parser->m_errorCode = XML_ERROR_SUSPENDED;
      return XML_STATUS_ERROR;
    }
    parser->m_parsingStatus.parsing = XML_FINISHED;
    break;
  case XML_FINISHED:
    parser->m_errorCode = XML_ERROR_FINISHED;
    return XML_STATUS_ERROR;
  default:
    if (resumable) {
#ifdef XML_DTD
      if (parser->m_isParamEntity) {
        parser->m_errorCode = XML_ERROR_SUSPEND_PE;
        return XML_STATUS_ERROR;
      }
#endif
      parser->m_parsingStatus.parsing = XML_SUSPENDED;
    }
    else
      parser->m_parsingStatus.parsing = XML_FINISHED;
  }
  return XML_STATUS_OK;
}

enum XML_Status XMLCALL
XML_ResumeParser(XML_Parser parser)
{
  enum XML_Status result = XML_STATUS_OK;

  if (parser == NULL)
    return XML_STATUS_ERROR;
  if (parser->m_parsingStatus.parsing != XML_SUSPENDED) {
    parser->m_errorCode = XML_ERROR_NOT_SUSPENDED;
    return XML_STATUS_ERROR;
  }
  parser->m_parsingStatus.parsing = XML_PARSING;

  parser->m_errorCode = parser->m_processor(parser, parser->m_bufferPtr, parser->m_parseEndPtr, &parser->m_bufferPtr);

  if (parser->m_errorCode != XML_ERROR_NONE) {
    parser->m_eventEndPtr = parser->m_eventPtr;
    parser->m_processor = errorProcessor;
    return XML_STATUS_ERROR;
  }
  else {
    switch (parser->m_parsingStatus.parsing) {
    case XML_SUSPENDED:
      result = XML_STATUS_SUSPENDED;
      break;
    case XML_INITIALIZED:
    case XML_PARSING:
      if (parser->m_parsingStatus.finalBuffer) {
        parser->m_parsingStatus.parsing = XML_FINISHED;
        return result;
      }
    default: ;
    }
  }

  XmlUpdatePosition(parser->m_encoding, parser->m_positionPtr, parser->m_bufferPtr, &parser->m_position);
  parser->m_positionPtr = parser->m_bufferPtr;
  return result;
}

void XMLCALL
XML_GetParsingStatus(XML_Parser parser, XML_ParsingStatus *status)
{
  if (parser == NULL)
    return;
  assert(status != NULL);
  *status = parser->m_parsingStatus;
}

enum XML_Error XMLCALL
XML_GetErrorCode(XML_Parser parser)
{
  if (parser == NULL)
    return XML_ERROR_INVALID_ARGUMENT;
  return parser->m_errorCode;
}

XML_Index XMLCALL
XML_GetCurrentByteIndex(XML_Parser parser)
{
  if (parser == NULL)
    return -1;
  if (parser->m_eventPtr)
    return (XML_Index)(parser->m_parseEndByteIndex - (parser->m_parseEndPtr - parser->m_eventPtr));
  return -1;
}

int XMLCALL
XML_GetCurrentByteCount(XML_Parser parser)
{
  if (parser == NULL)
    return 0;
  if (parser->m_eventEndPtr && parser->m_eventPtr)
    return (int)(parser->m_eventEndPtr - parser->m_eventPtr);
  return 0;
}

const char * XMLCALL
XML_GetInputContext(XML_Parser parser, int *offset, int *size)
{
#ifdef XML_CONTEXT_BYTES
  if (parser == NULL)
    return NULL;
  if (parser->m_eventPtr && parser->m_buffer) {
    if (offset != NULL)
      *offset = (int)(parser->m_eventPtr - parser->m_buffer);
    if (size != NULL)
      *size   = (int)(parser->m_bufferEnd - parser->m_buffer);
    return parser->m_buffer;
  }
#else
  (void)parser;
  (void)offset;
  (void)size;
#endif /* defined XML_CONTEXT_BYTES */
  return (char *) 0;
}

XML_Size XMLCALL
XML_GetCurrentLineNumber(XML_Parser parser)
{
  if (parser == NULL)
    return 0;
  if (parser->m_eventPtr && parser->m_eventPtr >= parser->m_positionPtr) {
    XmlUpdatePosition(parser->m_encoding, parser->m_positionPtr, parser->m_eventPtr, &parser->m_position);
    parser->m_positionPtr = parser->m_eventPtr;
  }
  return parser->m_position.lineNumber + 1;
}

XML_Size XMLCALL
XML_GetCurrentColumnNumber(XML_Parser parser)
{
  if (parser == NULL)
    return 0;
  if (parser->m_eventPtr && parser->m_eventPtr >= parser->m_positionPtr) {
    XmlUpdatePosition(parser->m_encoding, parser->m_positionPtr, parser->m_eventPtr, &parser->m_position);
    parser->m_positionPtr = parser->m_eventPtr;
  }
  return parser->m_position.columnNumber;
}

void XMLCALL
XML_FreeContentModel(XML_Parser parser, XML_Content *model)
{
  if (parser != NULL)
    FREE(parser, model);
}

void * XMLCALL
XML_MemMalloc(XML_Parser parser, size_t size)
{
  if (parser == NULL)
    return NULL;
  return MALLOC(parser, size);
}

void * XMLCALL
XML_MemRealloc(XML_Parser parser, void *ptr, size_t size)
{
  if (parser == NULL)
    return NULL;
  return REALLOC(parser, ptr, size);
}

void XMLCALL
XML_MemFree(XML_Parser parser, void *ptr)
{
  if (parser != NULL)
    FREE(parser, ptr);
}

void XMLCALL
XML_DefaultCurrent(XML_Parser parser)
{
  if (parser == NULL)
    return;
  if (parser->m_defaultHandler) {
    if (parser->m_openInternalEntities)
      reportDefault(parser,
                    parser->m_internalEncoding,
                    parser->m_openInternalEntities->internalEventPtr,
                    parser->m_openInternalEntities->internalEventEndPtr);
    else
      reportDefault(parser, parser->m_encoding, parser->m_eventPtr, parser->m_eventEndPtr);
  }
}

const XML_LChar * XMLCALL
XML_ErrorString(enum XML_Error code)
{
  switch (code) {
  case XML_ERROR_NONE:
    return NULL;
  case XML_ERROR_NO_MEMORY:
    return XML_L("out of memory");
  case XML_ERROR_SYNTAX:
    return XML_L("syntax error");
  case XML_ERROR_NO_ELEMENTS:
    return XML_L("no element found");
  case XML_ERROR_INVALID_TOKEN:
    return XML_L("not well-formed (invalid token)");
  case XML_ERROR_UNCLOSED_TOKEN:
    return XML_L("unclosed token");
  case XML_ERROR_PARTIAL_CHAR:
    return XML_L("partial character");
  case XML_ERROR_TAG_MISMATCH:
    return XML_L("mismatched tag");
  case XML_ERROR_DUPLICATE_ATTRIBUTE:
    return XML_L("duplicate attribute");
  case XML_ERROR_JUNK_AFTER_DOC_ELEMENT:
    return XML_L("junk after document element");
  case XML_ERROR_PARAM_ENTITY_REF:
    return XML_L("illegal parameter entity reference");
  case XML_ERROR_UNDEFINED_ENTITY:
    return XML_L("undefined entity");
  case XML_ERROR_RECURSIVE_ENTITY_REF:
    return XML_L("recursive entity reference");
  case XML_ERROR_ASYNC_ENTITY:
    return XML_L("asynchronous entity");
  case XML_ERROR_BAD_CHAR_REF:
    return XML_L("reference to invalid character number");
  case XML_ERROR_BINARY_ENTITY_REF:
    return XML_L("reference to binary entity");
  case XML_ERROR_ATTRIBUTE_EXTERNAL_ENTITY_REF:
    return XML_L("reference to external entity in attribute");
  case XML_ERROR_MISPLACED_XML_PI:
    return XML_L("XML or text declaration not at start of entity");
  case XML_ERROR_UNKNOWN_ENCODING:
    return XML_L("unknown encoding");
  case XML_ERROR_INCORRECT_ENCODING:
    return XML_L("encoding specified in XML declaration is incorrect");
  case XML_ERROR_UNCLOSED_CDATA_SECTION:
    return XML_L("unclosed CDATA section");
  case XML_ERROR_EXTERNAL_ENTITY_HANDLING:
    return XML_L("error in processing external entity reference");
  case XML_ERROR_NOT_STANDALONE:
    return XML_L("document is not standalone");
  case XML_ERROR_UNEXPECTED_STATE:
    return XML_L("unexpected parser state - please send a bug report");
  case XML_ERROR_ENTITY_DECLARED_IN_PE:
    return XML_L("entity declared in parameter entity");
  case XML_ERROR_FEATURE_REQUIRES_XML_DTD:
    return XML_L("requested feature requires XML_DTD support in Expat");
  case XML_ERROR_CANT_CHANGE_FEATURE_ONCE_PARSING:
    return XML_L("cannot change setting once parsing has begun");
  /* Added in 1.95.7. */
  case XML_ERROR_UNBOUND_PREFIX:
    return XML_L("unbound prefix");
  /* Added in 1.95.8. */
  case XML_ERROR_UNDECLARING_PREFIX:
    return XML_L("must not undeclare prefix");
  case XML_ERROR_INCOMPLETE_PE:
    return XML_L("incomplete markup in parameter entity");
  case XML_ERROR_XML_DECL:
    return XML_L("XML declaration not well-formed");
  case XML_ERROR_TEXT_DECL:
    return XML_L("text declaration not well-formed");
  case XML_ERROR_PUBLICID:
    return XML_L("illegal character(s) in public id");
  case XML_ERROR_SUSPENDED:
    return XML_L("parser suspended");
  case XML_ERROR_NOT_SUSPENDED:
    return XML_L("parser not suspended");
  case XML_ERROR_ABORTED:
    return XML_L("parsing aborted");
  case XML_ERROR_FINISHED:
    return XML_L("parsing finished");
  case XML_ERROR_SUSPEND_PE:
    return XML_L("cannot suspend in external parameter entity");
  /* Added in 2.0.0. */
  case XML_ERROR_RESERVED_PREFIX_XML:
    return XML_L("reserved prefix (xml) must not be undeclared or bound to another namespace name");
  case XML_ERROR_RESERVED_PREFIX_XMLNS:
    return XML_L("reserved prefix (xmlns) must not be declared or undeclared");
  case XML_ERROR_RESERVED_NAMESPACE_URI:
    return XML_L("prefix must not be bound to one of the reserved namespace names");
  /* Added in 2.2.5. */
  case XML_ERROR_INVALID_ARGUMENT:  /* Constant added in 2.2.1, already */
    return XML_L("invalid argument");
  }
  return NULL;
}

const XML_LChar * XMLCALL
XML_ExpatVersion(void) {

  /* V1 is used to string-ize the version number. However, it would
     string-ize the actual version macro *names* unless we get them
     substituted before being passed to V1. CPP is defined to expand
     a macro, then rescan for more expansions. Thus, we use V2 to expand
     the version macros, then CPP will expand the resulting V1() macro
     with the correct numerals. */
  /* ### I'm assuming cpp is portable in this respect... */

#define V1(a,b,c) XML_L(#a)XML_L(".")XML_L(#b)XML_L(".")XML_L(#c)
#define V2(a,b,c) XML_L("expat_")V1(a,b,c)

  return V2(XML_MAJOR_VERSION, XML_MINOR_VERSION, XML_MICRO_VERSION);

#undef V1
#undef V2
}

XML_Expat_Version XMLCALL
XML_ExpatVersionInfo(void)
{
  XML_Expat_Version version;

  version.major = XML_MAJOR_VERSION;
  version.minor = XML_MINOR_VERSION;
  version.micro = XML_MICRO_VERSION;

  return version;
}

const XML_Feature * XMLCALL
XML_GetFeatureList(void)
{
  static const XML_Feature features[] = {
    {XML_FEATURE_SIZEOF_XML_CHAR,  XML_L("sizeof(XML_Char)"),
     sizeof(XML_Char)},
    {XML_FEATURE_SIZEOF_XML_LCHAR, XML_L("sizeof(XML_LChar)"),
     sizeof(XML_LChar)},
#ifdef XML_UNICODE
    {XML_FEATURE_UNICODE,          XML_L("XML_UNICODE"), 0},
#endif
#ifdef XML_UNICODE_WCHAR_T
    {XML_FEATURE_UNICODE_WCHAR_T,  XML_L("XML_UNICODE_WCHAR_T"), 0},
#endif
#ifdef XML_DTD
    {XML_FEATURE_DTD,              XML_L("XML_DTD"), 0},
#endif
#ifdef XML_CONTEXT_BYTES
    {XML_FEATURE_CONTEXT_BYTES,    XML_L("XML_CONTEXT_BYTES"),
     XML_CONTEXT_BYTES},
#endif
#ifdef XML_MIN_SIZE
    {XML_FEATURE_MIN_SIZE,         XML_L("XML_MIN_SIZE"), 0},
#endif
#ifdef XML_NS
    {XML_FEATURE_NS,               XML_L("XML_NS"), 0},
#endif
#ifdef XML_LARGE_SIZE
    {XML_FEATURE_LARGE_SIZE,       XML_L("XML_LARGE_SIZE"), 0},
#endif
#ifdef XML_ATTR_INFO
    {XML_FEATURE_ATTR_INFO,        XML_L("XML_ATTR_INFO"), 0},
#endif
    {XML_FEATURE_END,              NULL, 0}
  };

  return features;
}

/* Initially tag->rawName always points into the parse buffer;
   for those TAG instances opened while the current parse buffer was
   processed, and not yet closed, we need to store tag->rawName in a more
   permanent location, since the parse buffer is about to be discarded.
*/
static XML_Bool
storeRawNames(XML_Parser parser)
{
  TAG *tag = parser->m_tagStack;
  while (tag) {
    int bufSize;
    int nameLen = sizeof(XML_Char) * (tag->name.strLen + 1);
    char *rawNameBuf = tag->buf + nameLen;
    /* Stop if already stored.  Since m_tagStack is a stack, we can stop
       at the first entry that has already been copied; everything
       below it in the stack is already been accounted for in a
       previous call to this function.
    */
    if (tag->rawName == rawNameBuf)
      break;
    /* For re-use purposes we need to ensure that the
       size of tag->buf is a multiple of sizeof(XML_Char).
    */
    bufSize = nameLen + ROUND_UP(tag->rawNameLength, sizeof(XML_Char));
    if (bufSize > tag->bufEnd - tag->buf) {
      char *temp = (char *)REALLOC(parser, tag->buf, bufSize);
      if (temp == NULL)
        return XML_FALSE;
      /* if tag->name.str points to tag->buf (only when namespace
         processing is off) then we have to update it
      */
      if (tag->name.str == (XML_Char *)tag->buf)
        tag->name.str = (XML_Char *)temp;
      /* if tag->name.localPart is set (when namespace processing is on)
         then update it as well, since it will always point into tag->buf
      */
      if (tag->name.localPart)
        tag->name.localPart = (XML_Char *)temp + (tag->name.localPart -
                                                  (XML_Char *)tag->buf);
      tag->buf = temp;
      tag->bufEnd = temp + bufSize;
      rawNameBuf = temp + nameLen;
    }
    memcpy(rawNameBuf, tag->rawName, tag->rawNameLength);
    tag->rawName = rawNameBuf;
    tag = tag->parent;
  }
  return XML_TRUE;
}

static enum XML_Error PTRCALL
contentProcessor(XML_Parser parser,
                 const char *start,
                 const char *end,
                 const char **endPtr)
{
  enum XML_Error result = doContent(parser, 0, parser->m_encoding, start, end,
                                    endPtr, (XML_Bool)!parser->m_parsingStatus.finalBuffer);
  if (result == XML_ERROR_NONE) {
    if (!storeRawNames(parser))
      return XML_ERROR_NO_MEMORY;
  }
  return result;
}

static enum XML_Error PTRCALL
externalEntityInitProcessor(XML_Parser parser,
                            const char *start,
                            const char *end,
                            const char **endPtr)
{
  enum XML_Error result = initializeEncoding(parser);
  if (result != XML_ERROR_NONE)
    return result;
  parser->m_processor = externalEntityInitProcessor2;
  return externalEntityInitProcessor2(parser, start, end, endPtr);
}

static enum XML_Error PTRCALL
externalEntityInitProcessor2(XML_Parser parser,
                             const char *start,
                             const char *end,
                             const char **endPtr)
{
  const char *next = start; /* XmlContentTok doesn't always set the last arg */
  int tok = XmlContentTok(parser->m_encoding, start, end, &next);
  switch (tok) {
  case XML_TOK_BOM:
    /* If we are at the end of the buffer, this would cause the next stage,
       i.e. externalEntityInitProcessor3, to pass control directly to
       doContent (by detecting XML_TOK_NONE) without processing any xml text
       declaration - causing the error XML_ERROR_MISPLACED_XML_PI in doContent.
    */
    if (next == end && !parser->m_parsingStatus.finalBuffer) {
      *endPtr = next;
      return XML_ERROR_NONE;
    }
    start = next;
    break;
  case XML_TOK_PARTIAL:
    if (!parser->m_parsingStatus.finalBuffer) {
      *endPtr = start;
      return XML_ERROR_NONE;
    }
    parser->m_eventPtr = start;
    return XML_ERROR_UNCLOSED_TOKEN;
  case XML_TOK_PARTIAL_CHAR:
    if (!parser->m_parsingStatus.finalBuffer) {
      *endPtr = start;
      return XML_ERROR_NONE;
    }
    parser->m_eventPtr = start;
    return XML_ERROR_PARTIAL_CHAR;
  }
  parser->m_processor = externalEntityInitProcessor3;
  return externalEntityInitProcessor3(parser, start, end, endPtr);
}

static enum XML_Error PTRCALL
externalEntityInitProcessor3(XML_Parser parser,
                             const char *start,
                             const char *end,
                             const char **endPtr)
{
  int tok;
  const char *next = start; /* XmlContentTok doesn't always set the last arg */
  parser->m_eventPtr = start;
  tok = XmlContentTok(parser->m_encoding, start, end, &next);
  parser->m_eventEndPtr = next;

  switch (tok) {
  case XML_TOK_XML_DECL:
    {
      enum XML_Error result;
      result = processXmlDecl(parser, 1, start, next);
      if (result != XML_ERROR_NONE)
        return result;
      switch (parser->m_parsingStatus.parsing) {
      case XML_SUSPENDED:
        *endPtr = next;
        return XML_ERROR_NONE;
      case XML_FINISHED:
        return XML_ERROR_ABORTED;
      default:
        start = next;
      }
    }
    break;
  case XML_TOK_PARTIAL:
    if (!parser->m_parsingStatus.finalBuffer) {
      *endPtr = start;
      return XML_ERROR_NONE;
    }
    return XML_ERROR_UNCLOSED_TOKEN;
  case XML_TOK_PARTIAL_CHAR:
    if (!parser->m_parsingStatus.finalBuffer) {
      *endPtr = start;
      return XML_ERROR_NONE;
    }
    return XML_ERROR_PARTIAL_CHAR;
  }
  parser->m_processor = externalEntityContentProcessor;
  parser->m_tagLevel = 1;
  return externalEntityContentProcessor(parser, start, end, endPtr);
}

static enum XML_Error PTRCALL
externalEntityContentProcessor(XML_Parser parser,
                               const char *start,
                               const char *end,
                               const char **endPtr)
{
  enum XML_Error result = doContent(parser, 1, parser->m_encoding, start, end,
                                    endPtr, (XML_Bool)!parser->m_parsingStatus.finalBuffer);
  if (result == XML_ERROR_NONE) {
    if (!storeRawNames(parser))
      return XML_ERROR_NO_MEMORY;
  }
  return result;
}

static enum XML_Error
doContent(XML_Parser parser,
          int startTagLevel,
          const ENCODING *enc,
          const char *s,
          const char *end,
          const char **nextPtr,
          XML_Bool haveMore)
{
  /* save one level of indirection */
  DTD * const dtd = parser->m_dtd;

  const char **eventPP;
  const char **eventEndPP;
  if (enc == parser->m_encoding) {
    eventPP = &parser->m_eventPtr;
    eventEndPP = &parser->m_eventEndPtr;
  }
  else {
    eventPP = &(parser->m_openInternalEntities->internalEventPtr);
    eventEndPP = &(parser->m_openInternalEntities->internalEventEndPtr);
  }
  *eventPP = s;

  for (;;) {
    const char *next = s; /* XmlContentTok doesn't always set the last arg */
    int tok = XmlContentTok(enc, s, end, &next);
    *eventEndPP = next;
    switch (tok) {
    case XML_TOK_TRAILING_CR:
      if (haveMore) {
        *nextPtr = s;
        return XML_ERROR_NONE;
      }
      *eventEndPP = end;
      if (parser->m_characterDataHandler) {
        XML_Char c = 0xA;
        parser->m_characterDataHandler(parser->m_handlerArg, &c, 1);
      }
      else if (parser->m_defaultHandler)
        reportDefault(parser, enc, s, end);
      /* We are at the end of the final buffer, should we check for
         XML_SUSPENDED, XML_FINISHED?
      */
      if (startTagLevel == 0)
        return XML_ERROR_NO_ELEMENTS;
      if (parser->m_tagLevel != startTagLevel)
        return XML_ERROR_ASYNC_ENTITY;
      *nextPtr = end;
      return XML_ERROR_NONE;
    case XML_TOK_NONE:
      if (haveMore) {
        *nextPtr = s;
        return XML_ERROR_NONE;
      }
      if (startTagLevel > 0) {
        if (parser->m_tagLevel != startTagLevel)
          return XML_ERROR_ASYNC_ENTITY;
        *nextPtr = s;
        return XML_ERROR_NONE;
      }
      return XML_ERROR_NO_ELEMENTS;
    case XML_TOK_INVALID:
      *eventPP = next;
      return XML_ERROR_INVALID_TOKEN;
    case XML_TOK_PARTIAL:
      if (haveMore) {
        *nextPtr = s;
        return XML_ERROR_NONE;
      }
      return XML_ERROR_UNCLOSED_TOKEN;
    case XML_TOK_PARTIAL_CHAR:
      if (haveMore) {
        *nextPtr = s;
        return XML_ERROR_NONE;
      }
      return XML_ERROR_PARTIAL_CHAR;
    case XML_TOK_ENTITY_REF:
      {
        const XML_Char *name;
        ENTITY *entity;
        XML_Char ch = (XML_Char) XmlPredefinedEntityName(enc,
                                              s + enc->minBytesPerChar,
                                              next - enc->minBytesPerChar);
        if (ch) {
          if (parser->m_characterDataHandler)
            parser->m_characterDataHandler(parser->m_handlerArg, &ch, 1);
          else if (parser->m_defaultHandler)
            reportDefault(parser, enc, s, next);
          break;
        }
        name = poolStoreString(&dtd->pool, enc,
                                s + enc->minBytesPerChar,
                                next - enc->minBytesPerChar);
        if (!name)
          return XML_ERROR_NO_MEMORY;
        entity = (ENTITY *)lookup(parser, &dtd->generalEntities, name, 0);
        poolDiscard(&dtd->pool);
        /* First, determine if a check for an existing declaration is needed;
           if yes, check that the entity exists, and that it is internal,
           otherwise call the skipped entity or default handler.
        */
        if (!dtd->hasParamEntityRefs || dtd->standalone) {
          if (!entity)
            return XML_ERROR_UNDEFINED_ENTITY;
          else if (!entity->is_internal)
            return XML_ERROR_ENTITY_DECLARED_IN_PE;
        }
        else if (!entity) {
          if (parser->m_skippedEntityHandler)
            parser->m_skippedEntityHandler(parser->m_handlerArg, name, 0);
          else if (parser->m_defaultHandler)
            reportDefault(parser, enc, s, next);
          break;
        }
        if (entity->open)
          return XML_ERROR_RECURSIVE_ENTITY_REF;
        if (entity->notation)
          return XML_ERROR_BINARY_ENTITY_REF;
        if (entity->textPtr) {
          enum XML_Error result;
          if (!parser->m_defaultExpandInternalEntities) {
            if (parser->m_skippedEntityHandler)
              parser->m_skippedEntityHandler(parser->m_handlerArg, entity->name, 0);
            else if (parser->m_defaultHandler)
              reportDefault(parser, enc, s, next);
            break;
          }
          result = processInternalEntity(parser, entity, XML_FALSE);
          if (result != XML_ERROR_NONE)
            return result;
        }
        else if (parser->m_externalEntityRefHandler) {
          const XML_Char *context;
          entity->open = XML_TRUE;
          context = getContext(parser);
          entity->open = XML_FALSE;
          if (!context)
            return XML_ERROR_NO_MEMORY;
          if (!parser->m_externalEntityRefHandler(parser->m_externalEntityRefHandlerArg,
                                        context,
                                        entity->base,
                                        entity->systemId,
                                        entity->publicId))
            return XML_ERROR_EXTERNAL_ENTITY_HANDLING;
          poolDiscard(&parser->m_tempPool);
        }
        else if (parser->m_defaultHandler)
          reportDefault(parser, enc, s, next);
        break;
      }
    case XML_TOK_START_TAG_NO_ATTS:
      /* fall through */
    case XML_TOK_START_TAG_WITH_ATTS:
      {
        TAG *tag;
        enum XML_Error result;
        XML_Char *toPtr;
        if (parser->m_freeTagList) {
          tag = parser->m_freeTagList;
          parser->m_freeTagList = parser->m_freeTagList->parent;
        }
        else {
          tag = (TAG *)MALLOC(parser, sizeof(TAG));
          if (!tag)
            return XML_ERROR_NO_MEMORY;
          tag->buf = (char *)MALLOC(parser, INIT_TAG_BUF_SIZE);
          if (!tag->buf) {
            FREE(parser, tag);
            return XML_ERROR_NO_MEMORY;
          }
          tag->bufEnd = tag->buf + INIT_TAG_BUF_SIZE;
        }
        tag->bindings = NULL;
        tag->parent = parser->m_tagStack;
        parser->m_tagStack = tag;
        tag->name.localPart = NULL;
        tag->name.prefix = NULL;
        tag->rawName = s + enc->minBytesPerChar;
        tag->rawNameLength = XmlNameLength(enc, tag->rawName);
        ++parser->m_tagLevel;
        {
          const char *rawNameEnd = tag->rawName + tag->rawNameLength;
          const char *fromPtr = tag->rawName;
          toPtr = (XML_Char *)tag->buf;
          for (;;) {
            int bufSize;
            int convLen;
            const enum XML_Convert_Result convert_res = XmlConvert(enc,
                       &fromPtr, rawNameEnd,
                       (ICHAR **)&toPtr, (ICHAR *)tag->bufEnd - 1);
            convLen = (int)(toPtr - (XML_Char *)tag->buf);
            if ((fromPtr >= rawNameEnd) || (convert_res == XML_CONVERT_INPUT_INCOMPLETE)) {
              tag->name.strLen = convLen;
              break;
            }
            bufSize = (int)(tag->bufEnd - tag->buf) << 1;
            {
              char *temp = (char *)REALLOC(parser, tag->buf, bufSize);
              if (temp == NULL)
                return XML_ERROR_NO_MEMORY;
              tag->buf = temp;
              tag->bufEnd = temp + bufSize;
              toPtr = (XML_Char *)temp + convLen;
            }
          }
        }
        tag->name.str = (XML_Char *)tag->buf;
        *toPtr = XML_T('\0');
        result = storeAtts(parser, enc, s, &(tag->name), &(tag->bindings));
        if (result)
          return result;
        if (parser->m_startElementHandler)
          parser->m_startElementHandler(parser->m_handlerArg, tag->name.str,
                              (const XML_Char **)parser->m_atts);
        else if (parser->m_defaultHandler)
          reportDefault(parser, enc, s, next);
        poolClear(&parser->m_tempPool);
        break;
      }
    case XML_TOK_EMPTY_ELEMENT_NO_ATTS:
      /* fall through */
    case XML_TOK_EMPTY_ELEMENT_WITH_ATTS:
      {
        const char *rawName = s + enc->minBytesPerChar;
        enum XML_Error result;
        BINDING *bindings = NULL;
        XML_Bool noElmHandlers = XML_TRUE;
        TAG_NAME name;
        name.str = poolStoreString(&parser->m_tempPool, enc, rawName,
                                   rawName + XmlNameLength(enc, rawName));
        if (!name.str)
          return XML_ERROR_NO_MEMORY;
        poolFinish(&parser->m_tempPool);
        result = storeAtts(parser, enc, s, &name, &bindings);
        if (result != XML_ERROR_NONE) {
          freeBindings(parser, bindings);
          return result;
        }
        poolFinish(&parser->m_tempPool);
        if (parser->m_startElementHandler) {
          parser->m_startElementHandler(parser->m_handlerArg, name.str, (const XML_Char **)parser->m_atts);
          noElmHandlers = XML_FALSE;
        }
        if (parser->m_endElementHandler) {
          if (parser->m_startElementHandler)
            *eventPP = *eventEndPP;
          parser->m_endElementHandler(parser->m_handlerArg, name.str);
          noElmHandlers = XML_FALSE;
        }
        if (noElmHandlers && parser->m_defaultHandler)
          reportDefault(parser, enc, s, next);
        poolClear(&parser->m_tempPool);
        freeBindings(parser, bindings);
      }
      if ((parser->m_tagLevel == 0) && (parser->m_parsingStatus.parsing != XML_FINISHED)) {
        if (parser->m_parsingStatus.parsing == XML_SUSPENDED)
          parser->m_processor = epilogProcessor;
        else
          return epilogProcessor(parser, next, end, nextPtr);
      }
      break;
    case XML_TOK_END_TAG:
      if (parser->m_tagLevel == startTagLevel)
        return XML_ERROR_ASYNC_ENTITY;
      else {
        int len;
        const char *rawName;
        TAG *tag = parser->m_tagStack;
        parser->m_tagStack = tag->parent;
        tag->parent = parser->m_freeTagList;
        parser->m_freeTagList = tag;
        rawName = s + enc->minBytesPerChar*2;
        len = XmlNameLength(enc, rawName);
        if (len != tag->rawNameLength
            || memcmp(tag->rawName, rawName, len) != 0) {
          *eventPP = rawName;
          return XML_ERROR_TAG_MISMATCH;
        }
        --parser->m_tagLevel;
        if (parser->m_endElementHandler) {
          const XML_Char *localPart;
          const XML_Char *prefix;
          XML_Char *uri;
          localPart = tag->name.localPart;
          if (parser->m_ns && localPart) {
            /* localPart and prefix may have been overwritten in
               tag->name.str, since this points to the binding->uri
               buffer which gets re-used; so we have to add them again
            */
            uri = (XML_Char *)tag->name.str + tag->name.uriLen;
            /* don't need to check for space - already done in storeAtts() */
            while (*localPart) *uri++ = *localPart++;
            prefix = (XML_Char *)tag->name.prefix;
            if (parser->m_ns_triplets && prefix) {
              *uri++ = parser->m_namespaceSeparator;
              while (*prefix) *uri++ = *prefix++;
             }
            *uri = XML_T('\0');
          }
          parser->m_endElementHandler(parser->m_handlerArg, tag->name.str);
        }
        else if (parser->m_defaultHandler)
          reportDefault(parser, enc, s, next);
        while (tag->bindings) {
          BINDING *b = tag->bindings;
          if (parser->m_endNamespaceDeclHandler)
            parser->m_endNamespaceDeclHandler(parser->m_handlerArg, b->prefix->name);
          tag->bindings = tag->bindings->nextTagBinding;
          b->nextTagBinding = parser->m_freeBindingList;
          parser->m_freeBindingList = b;
          b->prefix->binding = b->prevPrefixBinding;
        }
        if (parser->m_tagLevel == 0)
          return epilogProcessor(parser, next, end, nextPtr);
      }
      break;
    case XML_TOK_CHAR_REF:
      {
        int n = XmlCharRefNumber(enc, s);
        if (n < 0)
          return XML_ERROR_BAD_CHAR_REF;
        if (parser->m_characterDataHandler) {
          XML_Char buf[XML_ENCODE_MAX];
          parser->m_characterDataHandler(parser->m_handlerArg, buf, XmlEncode(n, (ICHAR *)buf));
        }
        else if (parser->m_defaultHandler)
          reportDefault(parser, enc, s, next);
      }
      break;
    case XML_TOK_XML_DECL:
      return XML_ERROR_MISPLACED_XML_PI;
    case XML_TOK_DATA_NEWLINE:
      if (parser->m_characterDataHandler) {
        XML_Char c = 0xA;
        parser->m_characterDataHandler(parser->m_handlerArg, &c, 1);
      }
      else if (parser->m_defaultHandler)
        reportDefault(parser, enc, s, next);
      break;
    case XML_TOK_CDATA_SECT_OPEN:
      {
        enum XML_Error result;
        if (parser->m_startCdataSectionHandler)
          parser->m_startCdataSectionHandler(parser->m_handlerArg);
#if 0
        /* Suppose you doing a transformation on a document that involves
           changing only the character data.  You set up a defaultHandler
           and a characterDataHandler.  The defaultHandler simply copies
           characters through.  The characterDataHandler does the
           transformation and writes the characters out escaping them as
           necessary.  This case will fail to work if we leave out the
           following two lines (because & and < inside CDATA sections will
           be incorrectly escaped).

           However, now we have a start/endCdataSectionHandler, so it seems
           easier to let the user deal with this.
        */
        else if (parser->m_characterDataHandler)
          parser->m_characterDataHandler(parser->m_handlerArg, parser->m_dataBuf, 0);
#endif
        else if (parser->m_defaultHandler)
          reportDefault(parser, enc, s, next);
        result = doCdataSection(parser, enc, &next, end, nextPtr, haveMore);
        if (result != XML_ERROR_NONE)
          return result;
        else if (!next) {
          parser->m_processor = cdataSectionProcessor;
          return result;
        }
      }
      break;
    case XML_TOK_TRAILING_RSQB:
      if (haveMore) {
        *nextPtr = s;
        return XML_ERROR_NONE;
      }
      if (parser->m_characterDataHandler) {
        if (MUST_CONVERT(enc, s)) {
          ICHAR *dataPtr = (ICHAR *)parser->m_dataBuf;
          XmlConvert(enc, &s, end, &dataPtr, (ICHAR *)parser->m_dataBufEnd);
          parser->m_characterDataHandler(parser->m_handlerArg, parser->m_dataBuf,
                               (int)(dataPtr - (ICHAR *)parser->m_dataBuf));
        }
        else
          parser->m_characterDataHandler(parser->m_handlerArg,
                               (XML_Char *)s,
                               (int)((XML_Char *)end - (XML_Char *)s));
      }
      else if (parser->m_defaultHandler)
        reportDefault(parser, enc, s, end);
      /* We are at the end of the final buffer, should we check for
         XML_SUSPENDED, XML_FINISHED?
      */
      if (startTagLevel == 0) {
        *eventPP = end;
        return XML_ERROR_NO_ELEMENTS;
      }
      if (parser->m_tagLevel != startTagLevel) {
        *eventPP = end;
        return XML_ERROR_ASYNC_ENTITY;
      }
      *nextPtr = end;
      return XML_ERROR_NONE;
    case XML_TOK_DATA_CHARS:
      {
        XML_CharacterDataHandler charDataHandler = parser->m_characterDataHandler;
        if (charDataHandler) {
          if (MUST_CONVERT(enc, s)) {
            for (;;) {
              ICHAR *dataPtr = (ICHAR *)parser->m_dataBuf;
              const enum XML_Convert_Result convert_res = XmlConvert(enc, &s, next, &dataPtr, (ICHAR *)parser->m_dataBufEnd);
              *eventEndPP = s;
              charDataHandler(parser->m_handlerArg, parser->m_dataBuf,
                              (int)(dataPtr - (ICHAR *)parser->m_dataBuf));
              if ((convert_res == XML_CONVERT_COMPLETED) || (convert_res == XML_CONVERT_INPUT_INCOMPLETE))
                break;
              *eventPP = s;
            }
          }
          else
            charDataHandler(parser->m_handlerArg,
                            (XML_Char *)s,
                            (int)((XML_Char *)next - (XML_Char *)s));
        }
        else if (parser->m_defaultHandler)
          reportDefault(parser, enc, s, next);
      }
      break;
    case XML_TOK_PI:
      if (!reportProcessingInstruction(parser, enc, s, next))
        return XML_ERROR_NO_MEMORY;
      break;
    case XML_TOK_COMMENT:
      if (!reportComment(parser, enc, s, next))
        return XML_ERROR_NO_MEMORY;
      break;
    default:
      /* All of the tokens produced by XmlContentTok() have their own
       * explicit cases, so this default is not strictly necessary.
       * However it is a useful safety net, so we retain the code and
       * simply exclude it from the coverage tests.
       *
       * LCOV_EXCL_START
       */
      if (parser->m_defaultHandler)
        reportDefault(parser, enc, s, next);
      break;
      /* LCOV_EXCL_STOP */
    }
    *eventPP = s = next;
    switch (parser->m_parsingStatus.parsing) {
    case XML_SUSPENDED:
      *nextPtr = next;
      return XML_ERROR_NONE;
    case XML_FINISHED:
      return XML_ERROR_ABORTED;
    default: ;
    }
  }
  /* not reached */
}

/* This function does not call free() on the allocated memory, merely
 * moving it to the parser's m_freeBindingList where it can be freed or
 * reused as appropriate.
 */
static void
freeBindings(XML_Parser parser, BINDING *bindings)
{
  while (bindings) {
    BINDING *b = bindings;

    /* m_startNamespaceDeclHandler will have been called for this
     * binding in addBindings(), so call the end handler now.
     */
    if (parser->m_endNamespaceDeclHandler)
        parser->m_endNamespaceDeclHandler(parser->m_handlerArg, b->prefix->name);

    bindings = bindings->nextTagBinding;
    b->nextTagBinding = parser->m_freeBindingList;
    parser->m_freeBindingList = b;
    b->prefix->binding = b->prevPrefixBinding;
  }
}

/* Precondition: all arguments must be non-NULL;
   Purpose:
   - normalize attributes
   - check attributes for well-formedness
   - generate namespace aware attribute names (URI, prefix)
   - build list of attributes for startElementHandler
   - default attributes
   - process namespace declarations (check and report them)
   - generate namespace aware element name (URI, prefix)
*/
static enum XML_Error
storeAtts(XML_Parser parser, const ENCODING *enc,
          const char *attStr, TAG_NAME *tagNamePtr,
          BINDING **bindingsPtr)
{
  DTD * const dtd = parser->m_dtd;  /* save one level of indirection */
  ELEMENT_TYPE *elementType;
  int nDefaultAtts;
  const XML_Char **appAtts;   /* the attribute list for the application */
  int attIndex = 0;
  int prefixLen;
  int i;
  int n;
  XML_Char *uri;
  int nPrefixes = 0;
  BINDING *binding;
  const XML_Char *localPart;

  /* lookup the element type name */
  elementType = (ELEMENT_TYPE *)lookup(parser, &dtd->elementTypes, tagNamePtr->str,0);
  if (!elementType) {
    const XML_Char *name = poolCopyString(&dtd->pool, tagNamePtr->str);
    if (!name)
      return XML_ERROR_NO_MEMORY;
    elementType = (ELEMENT_TYPE *)lookup(parser, &dtd->elementTypes, name,
                                         sizeof(ELEMENT_TYPE));
    if (!elementType)
      return XML_ERROR_NO_MEMORY;
    if (parser->m_ns && !setElementTypePrefix(parser, elementType))
      return XML_ERROR_NO_MEMORY;
  }
  nDefaultAtts = elementType->nDefaultAtts;

  /* get the attributes from the tokenizer */
  n = XmlGetAttributes(enc, attStr, parser->m_attsSize, parser->m_atts);
  if (n + nDefaultAtts > parser->m_attsSize) {
    int oldAttsSize = parser->m_attsSize;
    ATTRIBUTE *temp;
#ifdef XML_ATTR_INFO
    XML_AttrInfo *temp2;
#endif
    parser->m_attsSize = n + nDefaultAtts + INIT_ATTS_SIZE;
    temp = (ATTRIBUTE *)REALLOC(parser, (void *)parser->m_atts, parser->m_attsSize * sizeof(ATTRIBUTE));
    if (temp == NULL) {
      parser->m_attsSize = oldAttsSize;
      return XML_ERROR_NO_MEMORY;
    }
    parser->m_atts = temp;
#ifdef XML_ATTR_INFO
    temp2 = (XML_AttrInfo *)REALLOC(parser, (void *)parser->m_attInfo, parser->m_attsSize * sizeof(XML_AttrInfo));
    if (temp2 == NULL) {
      parser->m_attsSize = oldAttsSize;
      return XML_ERROR_NO_MEMORY;
    }
    parser->m_attInfo = temp2;
#endif
    if (n > oldAttsSize)
      XmlGetAttributes(enc, attStr, n, parser->m_atts);
  }

  appAtts = (const XML_Char **)parser->m_atts;
  for (i = 0; i < n; i++) {
    ATTRIBUTE *currAtt = &parser->m_atts[i];
#ifdef XML_ATTR_INFO
    XML_AttrInfo *currAttInfo = &parser->m_attInfo[i];
#endif
    /* add the name and value to the attribute list */
    ATTRIBUTE_ID *attId = getAttributeId(parser, enc, currAtt->name,
                                         currAtt->name
                                         + XmlNameLength(enc, currAtt->name));
    if (!attId)
      return XML_ERROR_NO_MEMORY;
#ifdef XML_ATTR_INFO
    currAttInfo->nameStart = parser->m_parseEndByteIndex - (parser->m_parseEndPtr - currAtt->name);
    currAttInfo->nameEnd = currAttInfo->nameStart +
                           XmlNameLength(enc, currAtt->name);
    currAttInfo->valueStart = parser->m_parseEndByteIndex -
                            (parser->m_parseEndPtr - currAtt->valuePtr);
    currAttInfo->valueEnd = parser->m_parseEndByteIndex - (parser->m_parseEndPtr - currAtt->valueEnd);
#endif
    /* Detect duplicate attributes by their QNames. This does not work when
       namespace processing is turned on and different prefixes for the same
       namespace are used. For this case we have a check further down.
    */
    if ((attId->name)[-1]) {
      if (enc == parser->m_encoding)
        parser->m_eventPtr = parser->m_atts[i].name;
      return XML_ERROR_DUPLICATE_ATTRIBUTE;
    }
    (attId->name)[-1] = 1;
    appAtts[attIndex++] = attId->name;
    if (!parser->m_atts[i].normalized) {
      enum XML_Error result;
      XML_Bool isCdata = XML_TRUE;

      /* figure out whether declared as other than CDATA */
      if (attId->maybeTokenized) {
        int j;
        for (j = 0; j < nDefaultAtts; j++) {
          if (attId == elementType->defaultAtts[j].id) {
            isCdata = elementType->defaultAtts[j].isCdata;
            break;
          }
        }
      }

      /* normalize the attribute value */
      result = storeAttributeValue(parser, enc, isCdata,
                                   parser->m_atts[i].valuePtr, parser->m_atts[i].valueEnd,
                                   &parser->m_tempPool);
      if (result)
        return result;
      appAtts[attIndex] = poolStart(&parser->m_tempPool);
      poolFinish(&parser->m_tempPool);
    }
    else {
      /* the value did not need normalizing */
      appAtts[attIndex] = poolStoreString(&parser->m_tempPool, enc, parser->m_atts[i].valuePtr,
                                          parser->m_atts[i].valueEnd);
      if (appAtts[attIndex] == 0)
        return XML_ERROR_NO_MEMORY;
      poolFinish(&parser->m_tempPool);
    }
    /* handle prefixed attribute names */
    if (attId->prefix) {
      if (attId->xmlns) {
        /* deal with namespace declarations here */
        enum XML_Error result = addBinding(parser, attId->prefix, attId,
                                           appAtts[attIndex], bindingsPtr);
        if (result)
          return result;
        --attIndex;
      }
      else {
        /* deal with other prefixed names later */
        attIndex++;
        nPrefixes++;
        (attId->name)[-1] = 2;
      }
    }
    else
      attIndex++;
  }

  /* set-up for XML_GetSpecifiedAttributeCount and XML_GetIdAttributeIndex */
  parser->m_nSpecifiedAtts = attIndex;
  if (elementType->idAtt && (elementType->idAtt->name)[-1]) {
    for (i = 0; i < attIndex; i += 2)
      if (appAtts[i] == elementType->idAtt->name) {
        parser->m_idAttIndex = i;
        break;
      }
  }
  else
    parser->m_idAttIndex = -1;

  /* do attribute defaulting */
  for (i = 0; i < nDefaultAtts; i++) {
    const DEFAULT_ATTRIBUTE *da = elementType->defaultAtts + i;
    if (!(da->id->name)[-1] && da->value) {
      if (da->id->prefix) {
        if (da->id->xmlns) {
          enum XML_Error result = addBinding(parser, da->id->prefix, da->id,
                                             da->value, bindingsPtr);
          if (result)
            return result;
        }
        else {
          (da->id->name)[-1] = 2;
          nPrefixes++;
          appAtts[attIndex++] = da->id->name;
          appAtts[attIndex++] = da->value;
        }
      }
      else {
        (da->id->name)[-1] = 1;
        appAtts[attIndex++] = da->id->name;
        appAtts[attIndex++] = da->value;
      }
    }
  }
  appAtts[attIndex] = 0;

  /* expand prefixed attribute names, check for duplicates,
     and clear flags that say whether attributes were specified */
  i = 0;
  if (nPrefixes) {
    int j;  /* hash table index */
    unsigned long version = parser->m_nsAttsVersion;
    int nsAttsSize = (int)1 << parser->m_nsAttsPower;
    unsigned char oldNsAttsPower = parser->m_nsAttsPower;
    /* size of hash table must be at least 2 * (# of prefixed attributes) */
    if ((nPrefixes << 1) >> parser->m_nsAttsPower) {  /* true for m_nsAttsPower = 0 */
      NS_ATT *temp;
      /* hash table size must also be a power of 2 and >= 8 */
      while (nPrefixes >> parser->m_nsAttsPower++);
      if (parser->m_nsAttsPower < 3)
        parser->m_nsAttsPower = 3;
      nsAttsSize = (int)1 << parser->m_nsAttsPower;
      temp = (NS_ATT *)REALLOC(parser, parser->m_nsAtts, nsAttsSize * sizeof(NS_ATT));
      if (!temp) {
        /* Restore actual size of memory in m_nsAtts */
        parser->m_nsAttsPower = oldNsAttsPower;
        return XML_ERROR_NO_MEMORY;
      }
      parser->m_nsAtts = temp;
      version = 0;  /* force re-initialization of m_nsAtts hash table */
    }
    /* using a version flag saves us from initializing m_nsAtts every time */
    if (!version) {  /* initialize version flags when version wraps around */
      version = INIT_ATTS_VERSION;
      for (j = nsAttsSize; j != 0; )
        parser->m_nsAtts[--j].version = version;
    }
    parser->m_nsAttsVersion = --version;

    /* expand prefixed names and check for duplicates */
    for (; i < attIndex; i += 2) {
      const XML_Char *s = appAtts[i];
      if (s[-1] == 2) {  /* prefixed */
        ATTRIBUTE_ID *id;
        const BINDING *b;
        unsigned long uriHash;
        struct siphash sip_state;
        struct sipkey sip_key;

        copy_salt_to_sipkey(parser, &sip_key);
        sip24_init(&sip_state, &sip_key);

        ((XML_Char *)s)[-1] = 0;  /* clear flag */
        id = (ATTRIBUTE_ID *)lookup(parser, &dtd->attributeIds, s, 0);
        if (!id || !id->prefix) {
          /* This code is walking through the appAtts array, dealing
           * with (in this case) a prefixed attribute name.  To be in
           * the array, the attribute must have already been bound, so
           * has to have passed through the hash table lookup once
           * already.  That implies that an entry for it already
           * exists, so the lookup above will return a pointer to
           * already allocated memory.  There is no opportunaity for
           * the allocator to fail, so the condition above cannot be
           * fulfilled.
           *
           * Since it is difficult to be certain that the above
           * analysis is complete, we retain the test and merely
           * remove the code from coverage tests.
           */
          return XML_ERROR_NO_MEMORY; /* LCOV_EXCL_LINE */
        }
        b = id->prefix->binding;
        if (!b)
          return XML_ERROR_UNBOUND_PREFIX;

        for (j = 0; j < b->uriLen; j++) {
          const XML_Char c = b->uri[j];
          if (!poolAppendChar(&parser->m_tempPool, c))
            return XML_ERROR_NO_MEMORY;
        }

        sip24_update(&sip_state, b->uri, b->uriLen * sizeof(XML_Char));

        while (*s++ != XML_T(ASCII_COLON))
          ;

        sip24_update(&sip_state, s, keylen(s) * sizeof(XML_Char));

        do {  /* copies null terminator */
          if (!poolAppendChar(&parser->m_tempPool, *s))
            return XML_ERROR_NO_MEMORY;
        } while (*s++);

        uriHash = (unsigned long)sip24_final(&sip_state);

        { /* Check hash table for duplicate of expanded name (uriName).
             Derived from code in lookup(parser, HASH_TABLE *table, ...).
          */
          unsigned char step = 0;
          unsigned long mask = nsAttsSize - 1;
          j = uriHash & mask;  /* index into hash table */
          while (parser->m_nsAtts[j].version == version) {
            /* for speed we compare stored hash values first */
            if (uriHash == parser->m_nsAtts[j].hash) {
              const XML_Char *s1 = poolStart(&parser->m_tempPool);
              const XML_Char *s2 = parser->m_nsAtts[j].uriName;
              /* s1 is null terminated, but not s2 */
              for (; *s1 == *s2 && *s1 != 0; s1++, s2++);
              if (*s1 == 0)
                return XML_ERROR_DUPLICATE_ATTRIBUTE;
            }
            if (!step)
              step = PROBE_STEP(uriHash, mask, parser->m_nsAttsPower);
            j < step ? (j += nsAttsSize - step) : (j -= step);
          }
        }

        if (parser->m_ns_triplets) {  /* append namespace separator and prefix */
          parser->m_tempPool.ptr[-1] = parser->m_namespaceSeparator;
          s = b->prefix->name;
          do {
            if (!poolAppendChar(&parser->m_tempPool, *s))
              return XML_ERROR_NO_MEMORY;
          } while (*s++);
        }

        /* store expanded name in attribute list */
        s = poolStart(&parser->m_tempPool);
        poolFinish(&parser->m_tempPool);
        appAtts[i] = s;

        /* fill empty slot with new version, uriName and hash value */
        parser->m_nsAtts[j].version = version;
        parser->m_nsAtts[j].hash = uriHash;
        parser->m_nsAtts[j].uriName = s;

        if (!--nPrefixes) {
          i += 2;
          break;
        }
      }
      else  /* not prefixed */
        ((XML_Char *)s)[-1] = 0;  /* clear flag */
    }
  }
  /* clear flags for the remaining attributes */
  for (; i < attIndex; i += 2)
    ((XML_Char *)(appAtts[i]))[-1] = 0;
  for (binding = *bindingsPtr; binding; binding = binding->nextTagBinding)
    binding->attId->name[-1] = 0;

  if (!parser->m_ns)
    return XML_ERROR_NONE;

  /* expand the element type name */
  if (elementType->prefix) {
    binding = elementType->prefix->binding;
    if (!binding)
      return XML_ERROR_UNBOUND_PREFIX;
    localPart = tagNamePtr->str;
    while (*localPart++ != XML_T(ASCII_COLON))
      ;
  }
  else if (dtd->defaultPrefix.binding) {
    binding = dtd->defaultPrefix.binding;
    localPart = tagNamePtr->str;
  }
  else
    return XML_ERROR_NONE;
  prefixLen = 0;
  if (parser->m_ns_triplets && binding->prefix->name) {
    for (; binding->prefix->name[prefixLen++];)
      ;  /* prefixLen includes null terminator */
  }
  tagNamePtr->localPart = localPart;
  tagNamePtr->uriLen = binding->uriLen;
  tagNamePtr->prefix = binding->prefix->name;
  tagNamePtr->prefixLen = prefixLen;
  for (i = 0; localPart[i++];)
    ;  /* i includes null terminator */
  n = i + binding->uriLen + prefixLen;
  if (n > binding->uriAlloc) {
    TAG *p;
    uri = (XML_Char *)MALLOC(parser, (n + EXPAND_SPARE) * sizeof(XML_Char));
    if (!uri)
      return XML_ERROR_NO_MEMORY;
    binding->uriAlloc = n + EXPAND_SPARE;
    memcpy(uri, binding->uri, binding->uriLen * sizeof(XML_Char));
    for (p = parser->m_tagStack; p; p = p->parent)
      if (p->name.str == binding->uri)
        p->name.str = uri;
    FREE(parser, binding->uri);
    binding->uri = uri;
  }
  /* if m_namespaceSeparator != '\0' then uri includes it already */
  uri = binding->uri + binding->uriLen;
  memcpy(uri, localPart, i * sizeof(XML_Char));
  /* we always have a namespace separator between localPart and prefix */
  if (prefixLen) {
    uri += i - 1;
    *uri = parser->m_namespaceSeparator;  /* replace null terminator */
    memcpy(uri + 1, binding->prefix->name, prefixLen * sizeof(XML_Char));
  }
  tagNamePtr->str = binding->uri;
  return XML_ERROR_NONE;
}

/* addBinding() overwrites the value of prefix->binding without checking.
   Therefore one must keep track of the old value outside of addBinding().
*/
static enum XML_Error
addBinding(XML_Parser parser, PREFIX *prefix, const ATTRIBUTE_ID *attId,
           const XML_Char *uri, BINDING **bindingsPtr)
{
  static const XML_Char xmlNamespace[] = {
    ASCII_h, ASCII_t, ASCII_t, ASCII_p, ASCII_COLON, ASCII_SLASH, ASCII_SLASH,
    ASCII_w, ASCII_w, ASCII_w, ASCII_PERIOD, ASCII_w, ASCII_3, ASCII_PERIOD,
    ASCII_o, ASCII_r, ASCII_g, ASCII_SLASH, ASCII_X, ASCII_M, ASCII_L,
    ASCII_SLASH, ASCII_1, ASCII_9, ASCII_9, ASCII_8, ASCII_SLASH,
    ASCII_n, ASCII_a, ASCII_m, ASCII_e, ASCII_s, ASCII_p, ASCII_a, ASCII_c,
    ASCII_e, '\0'
  };
  static const int xmlLen =
    (int)sizeof(xmlNamespace)/sizeof(XML_Char) - 1;
  static const XML_Char xmlnsNamespace[] = {
    ASCII_h, ASCII_t, ASCII_t, ASCII_p, ASCII_COLON, ASCII_SLASH, ASCII_SLASH,
    ASCII_w, ASCII_w, ASCII_w, ASCII_PERIOD, ASCII_w, ASCII_3, ASCII_PERIOD,
    ASCII_o, ASCII_r, ASCII_g, ASCII_SLASH, ASCII_2, ASCII_0, ASCII_0,
    ASCII_0, ASCII_SLASH, ASCII_x, ASCII_m, ASCII_l, ASCII_n, ASCII_s,
    ASCII_SLASH, '\0'
  };
  static const int xmlnsLen =
    (int)sizeof(xmlnsNamespace)/sizeof(XML_Char) - 1;

  XML_Bool mustBeXML = XML_FALSE;
  XML_Bool isXML = XML_TRUE;
  XML_Bool isXMLNS = XML_TRUE;

  BINDING *b;
  int len;

  /* empty URI is only valid for default namespace per XML NS 1.0 (not 1.1) */
  if (*uri == XML_T('\0') && prefix->name)
    return XML_ERROR_UNDECLARING_PREFIX;

  if (prefix->name
      && prefix->name[0] == XML_T(ASCII_x)
      && prefix->name[1] == XML_T(ASCII_m)
      && prefix->name[2] == XML_T(ASCII_l)) {

    /* Not allowed to bind xmlns */
    if (prefix->name[3] == XML_T(ASCII_n)
        && prefix->name[4] == XML_T(ASCII_s)
        && prefix->name[5] == XML_T('\0'))
      return XML_ERROR_RESERVED_PREFIX_XMLNS;

    if (prefix->name[3] == XML_T('\0'))
      mustBeXML = XML_TRUE;
  }

  for (len = 0; uri[len]; len++) {
    if (isXML && (len > xmlLen || uri[len] != xmlNamespace[len]))
      isXML = XML_FALSE;

    if (!mustBeXML && isXMLNS
        && (len > xmlnsLen || uri[len] != xmlnsNamespace[len]))
      isXMLNS = XML_FALSE;
  }
  isXML = isXML && len == xmlLen;
  isXMLNS = isXMLNS && len == xmlnsLen;

  if (mustBeXML != isXML)
    return mustBeXML ? XML_ERROR_RESERVED_PREFIX_XML
                     : XML_ERROR_RESERVED_NAMESPACE_URI;

  if (isXMLNS)
    return XML_ERROR_RESERVED_NAMESPACE_URI;

  if (parser->m_namespaceSeparator)
    len++;
  if (parser->m_freeBindingList) {
    b = parser->m_freeBindingList;
    if (len > b->uriAlloc) {
      XML_Char *temp = (XML_Char *)REALLOC(parser, b->uri,
                          sizeof(XML_Char) * (len + EXPAND_SPARE));
      if (temp == NULL)
        return XML_ERROR_NO_MEMORY;
      b->uri = temp;
      b->uriAlloc = len + EXPAND_SPARE;
    }
    parser->m_freeBindingList = b->nextTagBinding;
  }
  else {
    b = (BINDING *)MALLOC(parser, sizeof(BINDING));
    if (!b)
      return XML_ERROR_NO_MEMORY;
    b->uri = (XML_Char *)MALLOC(parser, sizeof(XML_Char) * (len + EXPAND_SPARE));
    if (!b->uri) {
      FREE(parser, b);
      return XML_ERROR_NO_MEMORY;
    }
    b->uriAlloc = len + EXPAND_SPARE;
  }
  b->uriLen = len;
  memcpy(b->uri, uri, len * sizeof(XML_Char));
  if (parser->m_namespaceSeparator)
    b->uri[len - 1] = parser->m_namespaceSeparator;
  b->prefix = prefix;
  b->attId = attId;
  b->prevPrefixBinding = prefix->binding;
  /* NULL binding when default namespace undeclared */
  if (*uri == XML_T('\0') && prefix == &parser->m_dtd->defaultPrefix)
    prefix->binding = NULL;
  else
    prefix->binding = b;
  b->nextTagBinding = *bindingsPtr;
  *bindingsPtr = b;
  /* if attId == NULL then we are not starting a namespace scope */
  if (attId && parser->m_startNamespaceDeclHandler)
    parser->m_startNamespaceDeclHandler(parser->m_handlerArg, prefix->name,
                              prefix->binding ? uri : 0);
  return XML_ERROR_NONE;
}

/* The idea here is to avoid using stack for each CDATA section when
   the whole file is parsed with one call.
*/
static enum XML_Error PTRCALL
cdataSectionProcessor(XML_Parser parser,
                      const char *start,
                      const char *end,
                      const char **endPtr)
{
  enum XML_Error result = doCdataSection(parser, parser->m_encoding, &start, end,
                                         endPtr, (XML_Bool)!parser->m_parsingStatus.finalBuffer);
  if (result != XML_ERROR_NONE)
    return result;
  if (start) {
    if (parser->m_parentParser) {  /* we are parsing an external entity */
      parser->m_processor = externalEntityContentProcessor;
      return externalEntityContentProcessor(parser, start, end, endPtr);
    }
    else {
      parser->m_processor = contentProcessor;
      return contentProcessor(parser, start, end, endPtr);
    }
  }
  return result;
}

/* startPtr gets set to non-null if the section is closed, and to null if
   the section is not yet closed.
*/
static enum XML_Error
doCdataSection(XML_Parser parser,
               const ENCODING *enc,
               const char **startPtr,
               const char *end,
               const char **nextPtr,
               XML_Bool haveMore)
{
  const char *s = *startPtr;
  const char **eventPP;
  const char **eventEndPP;
  if (enc == parser->m_encoding) {
    eventPP = &parser->m_eventPtr;
    *eventPP = s;
    eventEndPP = &parser->m_eventEndPtr;
  }
  else {
    eventPP = &(parser->m_openInternalEntities->internalEventPtr);
    eventEndPP = &(parser->m_openInternalEntities->internalEventEndPtr);
  }
  *eventPP = s;
  *startPtr = NULL;

  for (;;) {
    const char *next;
    int tok = XmlCdataSectionTok(enc, s, end, &next);
    *eventEndPP = next;
    switch (tok) {
    case XML_TOK_CDATA_SECT_CLOSE:
      if (parser->m_endCdataSectionHandler)
        parser->m_endCdataSectionHandler(parser->m_handlerArg);
#if 0
      /* see comment under XML_TOK_CDATA_SECT_OPEN */
      else if (parser->m_characterDataHandler)
        parser->m_characterDataHandler(parser->m_handlerArg, parser->m_dataBuf, 0);
#endif
      else if (parser->m_defaultHandler)
        reportDefault(parser, enc, s, next);
      *startPtr = next;
      *nextPtr = next;
      if (parser->m_parsingStatus.parsing == XML_FINISHED)
        return XML_ERROR_ABORTED;
      else
        return XML_ERROR_NONE;
    case XML_TOK_DATA_NEWLINE:
      if (parser->m_characterDataHandler) {
        XML_Char c = 0xA;
        parser->m_characterDataHandler(parser->m_handlerArg, &c, 1);
      }
      else if (parser->m_defaultHandler)
        reportDefault(parser, enc, s, next);
      break;
    case XML_TOK_DATA_CHARS:
      {
        XML_CharacterDataHandler charDataHandler = parser->m_characterDataHandler;
        if (charDataHandler) {
          if (MUST_CONVERT(enc, s)) {
            for (;;) {
              ICHAR *dataPtr = (ICHAR *)parser->m_dataBuf;
              const enum XML_Convert_Result convert_res = XmlConvert(enc, &s, next, &dataPtr, (ICHAR *)parser->m_dataBufEnd);
              *eventEndPP = next;
              charDataHandler(parser->m_handlerArg, parser->m_dataBuf,
                              (int)(dataPtr - (ICHAR *)parser->m_dataBuf));
              if ((convert_res == XML_CONVERT_COMPLETED) || (convert_res == XML_CONVERT_INPUT_INCOMPLETE))
                break;
              *eventPP = s;
            }
          }
          else
            charDataHandler(parser->m_handlerArg,
                            (XML_Char *)s,
                            (int)((XML_Char *)next - (XML_Char *)s));
        }
        else if (parser->m_defaultHandler)
          reportDefault(parser, enc, s, next);
      }
      break;
    case XML_TOK_INVALID:
      *eventPP = next;
      return XML_ERROR_INVALID_TOKEN;
    case XML_TOK_PARTIAL_CHAR:
      if (haveMore) {
        *nextPtr = s;
        return XML_ERROR_NONE;
      }
      return XML_ERROR_PARTIAL_CHAR;
    case XML_TOK_PARTIAL:
    case XML_TOK_NONE:
      if (haveMore) {
        *nextPtr = s;
        return XML_ERROR_NONE;
      }
      return XML_ERROR_UNCLOSED_CDATA_SECTION;
    default:
      /* Every token returned by XmlCdataSectionTok() has its own
       * explicit case, so this default case will never be executed.
       * We retain it as a safety net and exclude it from the coverage
       * statistics.
       *
       * LCOV_EXCL_START
      */
      *eventPP = next;
      return XML_ERROR_UNEXPECTED_STATE;
      /* LCOV_EXCL_STOP */
    }

    *eventPP = s = next;
    switch (parser->m_parsingStatus.parsing) {
    case XML_SUSPENDED:
      *nextPtr = next;
      return XML_ERROR_NONE;
    case XML_FINISHED:
      return XML_ERROR_ABORTED;
    default: ;
    }
  }
  /* not reached */
}

#ifdef XML_DTD

/* The idea here is to avoid using stack for each IGNORE section when
   the whole file is parsed with one call.
*/
static enum XML_Error PTRCALL
ignoreSectionProcessor(XML_Parser parser,
                       const char *start,
                       const char *end,
                       const char **endPtr)
{
  enum XML_Error result = doIgnoreSection(parser, parser->m_encoding, &start, end,
                                          endPtr, (XML_Bool)!parser->m_parsingStatus.finalBuffer);
  if (result != XML_ERROR_NONE)
    return result;
  if (start) {
    parser->m_processor = prologProcessor;
    return prologProcessor(parser, start, end, endPtr);
  }
  return result;
}

/* startPtr gets set to non-null is the section is closed, and to null
   if the section is not yet closed.
*/
static enum XML_Error
doIgnoreSection(XML_Parser parser,
                const ENCODING *enc,
                const char **startPtr,
                const char *end,
                const char **nextPtr,
                XML_Bool haveMore)
{
  const char *next;
  int tok;
  const char *s = *startPtr;
  const char **eventPP;
  const char **eventEndPP;
  if (enc == parser->m_encoding) {
    eventPP = &parser->m_eventPtr;
    *eventPP = s;
    eventEndPP = &parser->m_eventEndPtr;
  }
  else {
    /* It's not entirely clear, but it seems the following two lines
     * of code cannot be executed.  The only occasions on which 'enc'
     * is not 'encoding' are when this function is called
     * from the internal entity processing, and IGNORE sections are an
     * error in internal entities.
     *
     * Since it really isn't clear that this is true, we keep the code
     * and just remove it from our coverage tests.
     *
     * LCOV_EXCL_START
     */
    eventPP = &(parser->m_openInternalEntities->internalEventPtr);
    eventEndPP = &(parser->m_openInternalEntities->internalEventEndPtr);
    /* LCOV_EXCL_STOP */
  }
  *eventPP = s;
  *startPtr = NULL;
  tok = XmlIgnoreSectionTok(enc, s, end, &next);
  *eventEndPP = next;
  switch (tok) {
  case XML_TOK_IGNORE_SECT:
    if (parser->m_defaultHandler)
      reportDefault(parser, enc, s, next);
    *startPtr = next;
    *nextPtr = next;
    if (parser->m_parsingStatus.parsing == XML_FINISHED)
      return XML_ERROR_ABORTED;
    else
      return XML_ERROR_NONE;
  case XML_TOK_INVALID:
    *eventPP = next;
    return XML_ERROR_INVALID_TOKEN;
  case XML_TOK_PARTIAL_CHAR:
    if (haveMore) {
      *nextPtr = s;
      return XML_ERROR_NONE;
    }
    return XML_ERROR_PARTIAL_CHAR;
  case XML_TOK_PARTIAL:
  case XML_TOK_NONE:
    if (haveMore) {
      *nextPtr = s;
      return XML_ERROR_NONE;
    }
    return XML_ERROR_SYNTAX; /* XML_ERROR_UNCLOSED_IGNORE_SECTION */
  default:
    /* All of the tokens that XmlIgnoreSectionTok() returns have
     * explicit cases to handle them, so this default case is never
     * executed.  We keep it as a safety net anyway, and remove it
     * from our test coverage statistics.
     *
     * LCOV_EXCL_START
     */
    *eventPP = next;
    return XML_ERROR_UNEXPECTED_STATE;
    /* LCOV_EXCL_STOP */
  }
  /* not reached */
}

#endif /* XML_DTD */

static enum XML_Error
initializeEncoding(XML_Parser parser)
{
  const char *s;
#ifdef XML_UNICODE
  char encodingBuf[128];
  /* See comments abount `protoclEncodingName` in parserInit() */
  if (!parser->m_protocolEncodingName)
    s = NULL;
  else {
    int i;
    for (i = 0; parser->m_protocolEncodingName[i]; i++) {
      if (i == sizeof(encodingBuf) - 1
          || (parser->m_protocolEncodingName[i] & ~0x7f) != 0) {
        encodingBuf[0] = '\0';
        break;
      }
      encodingBuf[i] = (char)parser->m_protocolEncodingName[i];
    }
    encodingBuf[i] = '\0';
    s = encodingBuf;
  }
#else
  s = parser->m_protocolEncodingName;
#endif
  if ((parser->m_ns ? XmlInitEncodingNS : XmlInitEncoding)(&parser->m_initEncoding, &parser->m_encoding, s))
    return XML_ERROR_NONE;
  return handleUnknownEncoding(parser, parser->m_protocolEncodingName);
}

static enum XML_Error
processXmlDecl(XML_Parser parser, int isGeneralTextEntity,
               const char *s, const char *next)
{
  const char *encodingName = NULL;
  const XML_Char *storedEncName = NULL;
  const ENCODING *newEncoding = NULL;
  const char *version = NULL;
  const char *versionend;
  const XML_Char *storedversion = NULL;
  int standalone = -1;
  if (!(parser->m_ns
        ? XmlParseXmlDeclNS
        : XmlParseXmlDecl)(isGeneralTextEntity,
                           parser->m_encoding,
                           s,
                           next,
                           &parser->m_eventPtr,
                           &version,
                           &versionend,
                           &encodingName,
                           &newEncoding,
                           &standalone)) {
    if (isGeneralTextEntity)
      return XML_ERROR_TEXT_DECL;
    else
      return XML_ERROR_XML_DECL;
  }
  if (!isGeneralTextEntity && standalone == 1) {
    parser->m_dtd->standalone = XML_TRUE;
#ifdef XML_DTD
    if (parser->m_paramEntityParsing == XML_PARAM_ENTITY_PARSING_UNLESS_STANDALONE)
      parser->m_paramEntityParsing = XML_PARAM_ENTITY_PARSING_NEVER;
#endif /* XML_DTD */
  }
  if (parser->m_xmlDeclHandler) {
    if (encodingName != NULL) {
      storedEncName = poolStoreString(&parser->m_temp2Pool,
                                      parser->m_encoding,
                                      encodingName,
                                      encodingName
                                      + XmlNameLength(parser->m_encoding, encodingName));
      if (!storedEncName)
              return XML_ERROR_NO_MEMORY;
      poolFinish(&parser->m_temp2Pool);
    }
    if (version) {
      storedversion = poolStoreString(&parser->m_temp2Pool,
                                      parser->m_encoding,
                                      version,
                                      versionend - parser->m_encoding->minBytesPerChar);
      if (!storedversion)
        return XML_ERROR_NO_MEMORY;
    }
    parser->m_xmlDeclHandler(parser->m_handlerArg, storedversion, storedEncName, standalone);
  }
  else if (parser->m_defaultHandler)
    reportDefault(parser, parser->m_encoding, s, next);
  if (parser->m_protocolEncodingName == NULL) {
    if (newEncoding) {
      /* Check that the specified encoding does not conflict with what
       * the parser has already deduced.  Do we have the same number
       * of bytes in the smallest representation of a character?  If
       * this is UTF-16, is it the same endianness?
       */
      if (newEncoding->minBytesPerChar != parser->m_encoding->minBytesPerChar
          || (newEncoding->minBytesPerChar == 2 &&
              newEncoding != parser->m_encoding)) {
        parser->m_eventPtr = encodingName;
        return XML_ERROR_INCORRECT_ENCODING;
      }
      parser->m_encoding = newEncoding;
    }
    else if (encodingName) {
      enum XML_Error result;
      if (!storedEncName) {
        storedEncName = poolStoreString(
          &parser->m_temp2Pool, parser->m_encoding, encodingName,
          encodingName + XmlNameLength(parser->m_encoding, encodingName));
        if (!storedEncName)
          return XML_ERROR_NO_MEMORY;
      }
      result = handleUnknownEncoding(parser, storedEncName);
      poolClear(&parser->m_temp2Pool);
      if (result == XML_ERROR_UNKNOWN_ENCODING)
        parser->m_eventPtr = encodingName;
      return result;
    }
  }

  if (storedEncName || storedversion)
    poolClear(&parser->m_temp2Pool);

  return XML_ERROR_NONE;
}

static enum XML_Error
handleUnknownEncoding(XML_Parser parser, const XML_Char *encodingName)
{
  if (parser->m_unknownEncodingHandler) {
    XML_Encoding info;
    int i;
    for (i = 0; i < 256; i++)
      info.map[i] = -1;
    info.convert = NULL;
    info.data = NULL;
    info.release = NULL;
    if (parser->m_unknownEncodingHandler(parser->m_unknownEncodingHandlerData, encodingName,
                               &info)) {
      ENCODING *enc;
      parser->m_unknownEncodingMem = MALLOC(parser, XmlSizeOfUnknownEncoding());
      if (!parser->m_unknownEncodingMem) {
        if (info.release)
          info.release(info.data);
        return XML_ERROR_NO_MEMORY;
      }
      enc = (parser->m_ns
             ? XmlInitUnknownEncodingNS
             : XmlInitUnknownEncoding)(parser->m_unknownEncodingMem,
                                       info.map,
                                       info.convert,
                                       info.data);
      if (enc) {
        parser->m_unknownEncodingData = info.data;
        parser->m_unknownEncodingRelease = info.release;
        parser->m_encoding = enc;
        return XML_ERROR_NONE;
      }
    }
    if (info.release != NULL)
      info.release(info.data);
  }
  return XML_ERROR_UNKNOWN_ENCODING;
}

static enum XML_Error PTRCALL
prologInitProcessor(XML_Parser parser,
                    const char *s,
                    const char *end,
                    const char **nextPtr)
{
  enum XML_Error result = initializeEncoding(parser);
  if (result != XML_ERROR_NONE)
    return result;
  parser->m_processor = prologProcessor;
  return prologProcessor(parser, s, end, nextPtr);
}

#ifdef XML_DTD

static enum XML_Error PTRCALL
externalParEntInitProcessor(XML_Parser parser,
                            const char *s,
                            const char *end,
                            const char **nextPtr)
{
  enum XML_Error result = initializeEncoding(parser);
  if (result != XML_ERROR_NONE)
    return result;

  /* we know now that XML_Parse(Buffer) has been called,
     so we consider the external parameter entity read */
  parser->m_dtd->paramEntityRead = XML_TRUE;

  if (parser->m_prologState.inEntityValue) {
    parser->m_processor = entityValueInitProcessor;
    return entityValueInitProcessor(parser, s, end, nextPtr);
  }
  else {
    parser->m_processor = externalParEntProcessor;
    return externalParEntProcessor(parser, s, end, nextPtr);
  }
}

static enum XML_Error PTRCALL
entityValueInitProcessor(XML_Parser parser,
                         const char *s,
                         const char *end,
                         const char **nextPtr)
{
  int tok;
  const char *start = s;
  const char *next = start;
  parser->m_eventPtr = start;

  for (;;) {
    tok = XmlPrologTok(parser->m_encoding, start, end, &next);
    parser->m_eventEndPtr = next;
    if (tok <= 0) {
      if (!parser->m_parsingStatus.finalBuffer && tok != XML_TOK_INVALID) {
        *nextPtr = s;
        return XML_ERROR_NONE;
      }
      switch (tok) {
      case XML_TOK_INVALID:
        return XML_ERROR_INVALID_TOKEN;
      case XML_TOK_PARTIAL:
        return XML_ERROR_UNCLOSED_TOKEN;
      case XML_TOK_PARTIAL_CHAR:
        return XML_ERROR_PARTIAL_CHAR;
      case XML_TOK_NONE:   /* start == end */
      default:
        break;
      }
      /* found end of entity value - can store it now */
      return storeEntityValue(parser, parser->m_encoding, s, end);
    }
    else if (tok == XML_TOK_XML_DECL) {
      enum XML_Error result;
      result = processXmlDecl(parser, 0, start, next);
      if (result != XML_ERROR_NONE)
        return result;
      /* At this point, m_parsingStatus.parsing cannot be XML_SUSPENDED.  For that
       * to happen, a parameter entity parsing handler must have
       * attempted to suspend the parser, which fails and raises an
       * error.  The parser can be aborted, but can't be suspended.
       */
      if (parser->m_parsingStatus.parsing == XML_FINISHED)
        return XML_ERROR_ABORTED;
      *nextPtr = next;
      /* stop scanning for text declaration - we found one */
      parser->m_processor = entityValueProcessor;
      return entityValueProcessor(parser, next, end, nextPtr);
    }
    /* If we are at the end of the buffer, this would cause XmlPrologTok to
       return XML_TOK_NONE on the next call, which would then cause the
       function to exit with *nextPtr set to s - that is what we want for other
       tokens, but not for the BOM - we would rather like to skip it;
       then, when this routine is entered the next time, XmlPrologTok will
       return XML_TOK_INVALID, since the BOM is still in the buffer
    */
    else if (tok == XML_TOK_BOM && next == end && !parser->m_parsingStatus.finalBuffer) {
      *nextPtr = next;
      return XML_ERROR_NONE;
    }
    /* If we get this token, we have the start of what might be a
       normal tag, but not a declaration (i.e. it doesn't begin with
       "<!").  In a DTD context, that isn't legal.
    */
    else if (tok == XML_TOK_INSTANCE_START) {
      *nextPtr = next;
      return XML_ERROR_SYNTAX;
    }
    start = next;
    parser->m_eventPtr = start;
  }
}

static enum XML_Error PTRCALL
externalParEntProcessor(XML_Parser parser,
                        const char *s,
                        const char *end,
                        const char **nextPtr)
{
  const char *next = s;
  int tok;

  tok = XmlPrologTok(parser->m_encoding, s, end, &next);
  if (tok <= 0) {
    if (!parser->m_parsingStatus.finalBuffer && tok != XML_TOK_INVALID) {
      *nextPtr = s;
      return XML_ERROR_NONE;
    }
    switch (tok) {
    case XML_TOK_INVALID:
      return XML_ERROR_INVALID_TOKEN;
    case XML_TOK_PARTIAL:
      return XML_ERROR_UNCLOSED_TOKEN;
    case XML_TOK_PARTIAL_CHAR:
      return XML_ERROR_PARTIAL_CHAR;
    case XML_TOK_NONE:   /* start == end */
    default:
      break;
    }
  }
  /* This would cause the next stage, i.e. doProlog to be passed XML_TOK_BOM.
     However, when parsing an external subset, doProlog will not accept a BOM
     as valid, and report a syntax error, so we have to skip the BOM
  */
  else if (tok == XML_TOK_BOM) {
    s = next;
    tok = XmlPrologTok(parser->m_encoding, s, end, &next);
  }

  parser->m_processor = prologProcessor;
  return doProlog(parser, parser->m_encoding, s, end, tok, next,
                  nextPtr, (XML_Bool)!parser->m_parsingStatus.finalBuffer);
}

static enum XML_Error PTRCALL
entityValueProcessor(XML_Parser parser,
                     const char *s,
                     const char *end,
                     const char **nextPtr)
{
  const char *start = s;
  const char *next = s;
  const ENCODING *enc = parser->m_encoding;
  int tok;

  for (;;) {
    tok = XmlPrologTok(enc, start, end, &next);
    if (tok <= 0) {
      if (!parser->m_parsingStatus.finalBuffer && tok != XML_TOK_INVALID) {
        *nextPtr = s;
        return XML_ERROR_NONE;
      }
      switch (tok) {
      case XML_TOK_INVALID:
        return XML_ERROR_INVALID_TOKEN;
      case XML_TOK_PARTIAL:
        return XML_ERROR_UNCLOSED_TOKEN;
      case XML_TOK_PARTIAL_CHAR:
        return XML_ERROR_PARTIAL_CHAR;
      case XML_TOK_NONE:   /* start == end */
      default:
        break;
      }
      /* found end of entity value - can store it now */
      return storeEntityValue(parser, enc, s, end);
    }
    start = next;
  }
}

#endif /* XML_DTD */

static enum XML_Error PTRCALL
prologProcessor(XML_Parser parser,
                const char *s,
                const char *end,
                const char **nextPtr)
{
  const char *next = s;
  int tok = XmlPrologTok(parser->m_encoding, s, end, &next);
  return doProlog(parser, parser->m_encoding, s, end, tok, next,
                  nextPtr, (XML_Bool)!parser->m_parsingStatus.finalBuffer);
}

static enum XML_Error
doProlog(XML_Parser parser,
         const ENCODING *enc,
         const char *s,
         const char *end,
         int tok,
         const char *next,
         const char **nextPtr,
         XML_Bool haveMore)
{
#ifdef XML_DTD
  static const XML_Char externalSubsetName[] = { ASCII_HASH , '\0' };
#endif /* XML_DTD */
  static const XML_Char atypeCDATA[] =
      { ASCII_C, ASCII_D, ASCII_A, ASCII_T, ASCII_A, '\0' };
  static const XML_Char atypeID[] = { ASCII_I, ASCII_D, '\0' };
  static const XML_Char atypeIDREF[] =
      { ASCII_I, ASCII_D, ASCII_R, ASCII_E, ASCII_F, '\0' };
  static const XML_Char atypeIDREFS[] =
      { ASCII_I, ASCII_D, ASCII_R, ASCII_E, ASCII_F, ASCII_S, '\0' };
  static const XML_Char atypeENTITY[] =
      { ASCII_E, ASCII_N, ASCII_T, ASCII_I, ASCII_T, ASCII_Y, '\0' };
  static const XML_Char atypeENTITIES[] = { ASCII_E, ASCII_N,
      ASCII_T, ASCII_I, ASCII_T, ASCII_I, ASCII_E, ASCII_S, '\0' };
  static const XML_Char atypeNMTOKEN[] = {
      ASCII_N, ASCII_M, ASCII_T, ASCII_O, ASCII_K, ASCII_E, ASCII_N, '\0' };
  static const XML_Char atypeNMTOKENS[] = { ASCII_N, ASCII_M, ASCII_T,
      ASCII_O, ASCII_K, ASCII_E, ASCII_N, ASCII_S, '\0' };
  static const XML_Char notationPrefix[] = { ASCII_N, ASCII_O, ASCII_T,
      ASCII_A, ASCII_T, ASCII_I, ASCII_O, ASCII_N, ASCII_LPAREN, '\0' };
  static const XML_Char enumValueSep[] = { ASCII_PIPE, '\0' };
  static const XML_Char enumValueStart[] = { ASCII_LPAREN, '\0' };

  /* save one level of indirection */
  DTD * const dtd = parser->m_dtd;

  const char **eventPP;
  const char **eventEndPP;
  enum XML_Content_Quant quant;

  if (enc == parser->m_encoding) {
    eventPP = &parser->m_eventPtr;
    eventEndPP = &parser->m_eventEndPtr;
  }
  else {
    eventPP = &(parser->m_openInternalEntities->internalEventPtr);
    eventEndPP = &(parser->m_openInternalEntities->internalEventEndPtr);
  }

  for (;;) {
    int role;
    XML_Bool handleDefault = XML_TRUE;
    *eventPP = s;
    *eventEndPP = next;
    if (tok <= 0) {
      if (haveMore && tok != XML_TOK_INVALID) {
        *nextPtr = s;
        return XML_ERROR_NONE;
      }
      switch (tok) {
      case XML_TOK_INVALID:
        *eventPP = next;
        return XML_ERROR_INVALID_TOKEN;
      case XML_TOK_PARTIAL:
        return XML_ERROR_UNCLOSED_TOKEN;
      case XML_TOK_PARTIAL_CHAR:
        return XML_ERROR_PARTIAL_CHAR;
      case -XML_TOK_PROLOG_S:
        tok = -tok;
        break;
      case XML_TOK_NONE:
#ifdef XML_DTD
        /* for internal PE NOT referenced between declarations */
        if (enc != parser->m_encoding && !parser->m_openInternalEntities->betweenDecl) {
          *nextPtr = s;
          return XML_ERROR_NONE;
        }
        /* WFC: PE Between Declarations - must check that PE contains
           complete markup, not only for external PEs, but also for
           internal PEs if the reference occurs between declarations.
        */
        if (parser->m_isParamEntity || enc != parser->m_encoding) {
          if (XmlTokenRole(&parser->m_prologState, XML_TOK_NONE, end, end, enc)
              == XML_ROLE_ERROR)
            return XML_ERROR_INCOMPLETE_PE;
          *nextPtr = s;
          return XML_ERROR_NONE;
        }
#endif /* XML_DTD */
        return XML_ERROR_NO_ELEMENTS;
      default:
        tok = -tok;
        next = end;
        break;
      }
    }
    role = XmlTokenRole(&parser->m_prologState, tok, s, next, enc);
    switch (role) {
    case XML_ROLE_XML_DECL:
      {
        enum XML_Error result = processXmlDecl(parser, 0, s, next);
        if (result != XML_ERROR_NONE)
          return result;
        enc = parser->m_encoding;
        handleDefault = XML_FALSE;
      }
      break;
    case XML_ROLE_DOCTYPE_NAME:
      if (parser->m_startDoctypeDeclHandler) {
        parser->m_doctypeName = poolStoreString(&parser->m_tempPool, enc, s, next);
        if (!parser->m_doctypeName)
          return XML_ERROR_NO_MEMORY;
        poolFinish(&parser->m_tempPool);
        parser->m_doctypePubid = NULL;
        handleDefault = XML_FALSE;
      }
      parser->m_doctypeSysid = NULL; /* always initialize to NULL */
      break;
    case XML_ROLE_DOCTYPE_INTERNAL_SUBSET:
      if (parser->m_startDoctypeDeclHandler) {
        parser->m_startDoctypeDeclHandler(parser->m_handlerArg, parser->m_doctypeName, parser->m_doctypeSysid,
                                parser->m_doctypePubid, 1);
        parser->m_doctypeName = NULL;
        poolClear(&parser->m_tempPool);
        handleDefault = XML_FALSE;
      }
      break;
#ifdef XML_DTD
    case XML_ROLE_TEXT_DECL:
      {
        enum XML_Error result = processXmlDecl(parser, 1, s, next);
        if (result != XML_ERROR_NONE)
          return result;
        enc = parser->m_encoding;
        handleDefault = XML_FALSE;
      }
      break;
#endif /* XML_DTD */
    case XML_ROLE_DOCTYPE_PUBLIC_ID:
#ifdef XML_DTD
      parser->m_useForeignDTD = XML_FALSE;
      parser->m_declEntity = (ENTITY *)lookup(parser,
                                    &dtd->paramEntities,
                                    externalSubsetName,
                                    sizeof(ENTITY));
      if (!parser->m_declEntity)
        return XML_ERROR_NO_MEMORY;
#endif /* XML_DTD */
      dtd->hasParamEntityRefs = XML_TRUE;
      if (parser->m_startDoctypeDeclHandler) {
        XML_Char *pubId;
        if (!XmlIsPublicId(enc, s, next, eventPP))
          return XML_ERROR_PUBLICID;
        pubId = poolStoreString(&parser->m_tempPool, enc,
                                s + enc->minBytesPerChar,
                                next - enc->minBytesPerChar);
        if (!pubId)
          return XML_ERROR_NO_MEMORY;
        normalizePublicId(pubId);
        poolFinish(&parser->m_tempPool);
        parser->m_doctypePubid = pubId;
        handleDefault = XML_FALSE;
        goto alreadyChecked;
      }
      /* fall through */
    case XML_ROLE_ENTITY_PUBLIC_ID:
      if (!XmlIsPublicId(enc, s, next, eventPP))
        return XML_ERROR_PUBLICID;
    alreadyChecked:
      if (dtd->keepProcessing && parser->m_declEntity) {
        XML_Char *tem = poolStoreString(&dtd->pool,
                                        enc,
                                        s + enc->minBytesPerChar,
                                        next - enc->minBytesPerChar);
        if (!tem)
          return XML_ERROR_NO_MEMORY;
        normalizePublicId(tem);
        parser->m_declEntity->publicId = tem;
        poolFinish(&dtd->pool);
        /* Don't suppress the default handler if we fell through from
         * the XML_ROLE_DOCTYPE_PUBLIC_ID case.
         */
        if (parser->m_entityDeclHandler && role == XML_ROLE_ENTITY_PUBLIC_ID)
          handleDefault = XML_FALSE;
      }
      break;
    case XML_ROLE_DOCTYPE_CLOSE:
      if (parser->m_doctypeName) {
        parser->m_startDoctypeDeclHandler(parser->m_handlerArg, parser->m_doctypeName,
                                parser->m_doctypeSysid, parser->m_doctypePubid, 0);
        poolClear(&parser->m_tempPool);
        handleDefault = XML_FALSE;
      }
      /* parser->m_doctypeSysid will be non-NULL in the case of a previous
         XML_ROLE_DOCTYPE_SYSTEM_ID, even if parser->m_startDoctypeDeclHandler
         was not set, indicating an external subset
      */
#ifdef XML_DTD
      if (parser->m_doctypeSysid || parser->m_useForeignDTD) {
        XML_Bool hadParamEntityRefs = dtd->hasParamEntityRefs;
        dtd->hasParamEntityRefs = XML_TRUE;
        if (parser->m_paramEntityParsing && parser->m_externalEntityRefHandler) {
          ENTITY *entity = (ENTITY *)lookup(parser,
                                            &dtd->paramEntities,
                                            externalSubsetName,
                                            sizeof(ENTITY));
          if (!entity) {
            /* The external subset name "#" will have already been
             * inserted into the hash table at the start of the
             * external entity parsing, so no allocation will happen
             * and lookup() cannot fail.
             */
            return XML_ERROR_NO_MEMORY; /* LCOV_EXCL_LINE */
          }
          if (parser->m_useForeignDTD)
            entity->base = parser->m_curBase;
          dtd->paramEntityRead = XML_FALSE;
          if (!parser->m_externalEntityRefHandler(parser->m_externalEntityRefHandlerArg,
                                        0,
                                        entity->base,
                                        entity->systemId,
                                        entity->publicId))
            return XML_ERROR_EXTERNAL_ENTITY_HANDLING;
          if (dtd->paramEntityRead) {
            if (!dtd->standalone &&
                parser->m_notStandaloneHandler &&
                !parser->m_notStandaloneHandler(parser->m_handlerArg))
              return XML_ERROR_NOT_STANDALONE;
          }
          /* if we didn't read the foreign DTD then this means that there
             is no external subset and we must reset dtd->hasParamEntityRefs
          */
          else if (!parser->m_doctypeSysid)
            dtd->hasParamEntityRefs = hadParamEntityRefs;
          /* end of DTD - no need to update dtd->keepProcessing */
        }
        parser->m_useForeignDTD = XML_FALSE;
      }
#endif /* XML_DTD */
      if (parser->m_endDoctypeDeclHandler) {
        parser->m_endDoctypeDeclHandler(parser->m_handlerArg);
        handleDefault = XML_FALSE;
      }
      break;
    case XML_ROLE_INSTANCE_START:
#ifdef XML_DTD
      /* if there is no DOCTYPE declaration then now is the
         last chance to read the foreign DTD
      */
      if (parser->m_useForeignDTD) {
        XML_Bool hadParamEntityRefs = dtd->hasParamEntityRefs;
        dtd->hasParamEntityRefs = XML_TRUE;
        if (parser->m_paramEntityParsing && parser->m_externalEntityRefHandler) {
          ENTITY *entity = (ENTITY *)lookup(parser, &dtd->paramEntities,
                                            externalSubsetName,
                                            sizeof(ENTITY));
          if (!entity)
            return XML_ERROR_NO_MEMORY;
          entity->base = parser->m_curBase;
          dtd->paramEntityRead = XML_FALSE;
          if (!parser->m_externalEntityRefHandler(parser->m_externalEntityRefHandlerArg,
                                        0,
                                        entity->base,
                                        entity->systemId,
                                        entity->publicId))
            return XML_ERROR_EXTERNAL_ENTITY_HANDLING;
          if (dtd->paramEntityRead) {
            if (!dtd->standalone &&
                parser->m_notStandaloneHandler &&
                !parser->m_notStandaloneHandler(parser->m_handlerArg))
              return XML_ERROR_NOT_STANDALONE;
          }
          /* if we didn't read the foreign DTD then this means that there
             is no external subset and we must reset dtd->hasParamEntityRefs
          */
          else
            dtd->hasParamEntityRefs = hadParamEntityRefs;
          /* end of DTD - no need to update dtd->keepProcessing */
        }
      }
#endif /* XML_DTD */
      parser->m_processor = contentProcessor;
      return contentProcessor(parser, s, end, nextPtr);
    case XML_ROLE_ATTLIST_ELEMENT_NAME:
      parser->m_declElementType = getElementType(parser, enc, s, next);
      if (!parser->m_declElementType)
        return XML_ERROR_NO_MEMORY;
      goto checkAttListDeclHandler;
    case XML_ROLE_ATTRIBUTE_NAME:
      parser->m_declAttributeId = getAttributeId(parser, enc, s, next);
      if (!parser->m_declAttributeId)
        return XML_ERROR_NO_MEMORY;
      parser->m_declAttributeIsCdata = XML_FALSE;
      parser->m_declAttributeType = NULL;
      parser->m_declAttributeIsId = XML_FALSE;
      goto checkAttListDeclHandler;
    case XML_ROLE_ATTRIBUTE_TYPE_CDATA:
      parser->m_declAttributeIsCdata = XML_TRUE;
      parser->m_declAttributeType = atypeCDATA;
      goto checkAttListDeclHandler;
    case XML_ROLE_ATTRIBUTE_TYPE_ID:
      parser->m_declAttributeIsId = XML_TRUE;
      parser->m_declAttributeType = atypeID;
      goto checkAttListDeclHandler;
    case XML_ROLE_ATTRIBUTE_TYPE_IDREF:
      parser->m_declAttributeType = atypeIDREF;
      goto checkAttListDeclHandler;
    case XML_ROLE_ATTRIBUTE_TYPE_IDREFS:
      parser->m_declAttributeType = atypeIDREFS;
      goto checkAttListDeclHandler;
    case XML_ROLE_ATTRIBUTE_TYPE_ENTITY:
      parser->m_declAttributeType = atypeENTITY;
      goto checkAttListDeclHandler;
    case XML_ROLE_ATTRIBUTE_TYPE_ENTITIES:
      parser->m_declAttributeType = atypeENTITIES;
      goto checkAttListDeclHandler;
    case XML_ROLE_ATTRIBUTE_TYPE_NMTOKEN:
      parser->m_declAttributeType = atypeNMTOKEN;
      goto checkAttListDeclHandler;
    case XML_ROLE_ATTRIBUTE_TYPE_NMTOKENS:
      parser->m_declAttributeType = atypeNMTOKENS;
    checkAttListDeclHandler:
      if (dtd->keepProcessing && parser->m_attlistDeclHandler)
        handleDefault = XML_FALSE;
      break;
    case XML_ROLE_ATTRIBUTE_ENUM_VALUE:
    case XML_ROLE_ATTRIBUTE_NOTATION_VALUE:
      if (dtd->keepProcessing && parser->m_attlistDeclHandler) {
        const XML_Char *prefix;
        if (parser->m_declAttributeType) {
          prefix = enumValueSep;
        }
        else {
          prefix = (role == XML_ROLE_ATTRIBUTE_NOTATION_VALUE
                    ? notationPrefix
                    : enumValueStart);
        }
        if (!poolAppendString(&parser->m_tempPool, prefix))
          return XML_ERROR_NO_MEMORY;
        if (!poolAppend(&parser->m_tempPool, enc, s, next))
          return XML_ERROR_NO_MEMORY;
        parser->m_declAttributeType = parser->m_tempPool.start;
        handleDefault = XML_FALSE;
      }
      break;
    case XML_ROLE_IMPLIED_ATTRIBUTE_VALUE:
    case XML_ROLE_REQUIRED_ATTRIBUTE_VALUE:
      if (dtd->keepProcessing) {
        if (!defineAttribute(parser->m_declElementType, parser->m_declAttributeId,
                             parser->m_declAttributeIsCdata, parser->m_declAttributeIsId,
                             0, parser))
          return XML_ERROR_NO_MEMORY;
        if (parser->m_attlistDeclHandler && parser->m_declAttributeType) {
          if (*parser->m_declAttributeType == XML_T(ASCII_LPAREN)
              || (*parser->m_declAttributeType == XML_T(ASCII_N)
                  && parser->m_declAttributeType[1] == XML_T(ASCII_O))) {
            /* Enumerated or Notation type */
            if (!poolAppendChar(&parser->m_tempPool, XML_T(ASCII_RPAREN))
                || !poolAppendChar(&parser->m_tempPool, XML_T('\0')))
              return XML_ERROR_NO_MEMORY;
            parser->m_declAttributeType = parser->m_tempPool.start;
            poolFinish(&parser->m_tempPool);
          }
          *eventEndPP = s;
          parser->m_attlistDeclHandler(parser->m_handlerArg, parser->m_declElementType->name,
                             parser->m_declAttributeId->name, parser->m_declAttributeType,
                             0, role == XML_ROLE_REQUIRED_ATTRIBUTE_VALUE);
          poolClear(&parser->m_tempPool);
          handleDefault = XML_FALSE;
        }
      }
      break;
    case XML_ROLE_DEFAULT_ATTRIBUTE_VALUE:
    case XML_ROLE_FIXED_ATTRIBUTE_VALUE:
      if (dtd->keepProcessing) {
        const XML_Char *attVal;
        enum XML_Error result =
          storeAttributeValue(parser, enc, parser->m_declAttributeIsCdata,
                              s + enc->minBytesPerChar,
                              next - enc->minBytesPerChar,
                              &dtd->pool);
        if (result)
          return result;
        attVal = poolStart(&dtd->pool);
        poolFinish(&dtd->pool);
        /* ID attributes aren't allowed to have a default */
        if (!defineAttribute(parser->m_declElementType, parser->m_declAttributeId,
                             parser->m_declAttributeIsCdata, XML_FALSE, attVal, parser))
          return XML_ERROR_NO_MEMORY;
        if (parser->m_attlistDeclHandler && parser->m_declAttributeType) {
          if (*parser->m_declAttributeType == XML_T(ASCII_LPAREN)
              || (*parser->m_declAttributeType == XML_T(ASCII_N)
                  && parser->m_declAttributeType[1] == XML_T(ASCII_O))) {
            /* Enumerated or Notation type */
            if (!poolAppendChar(&parser->m_tempPool, XML_T(ASCII_RPAREN))
                || !poolAppendChar(&parser->m_tempPool, XML_T('\0')))
              return XML_ERROR_NO_MEMORY;
            parser->m_declAttributeType = parser->m_tempPool.start;
            poolFinish(&parser->m_tempPool);
          }
          *eventEndPP = s;
          parser->m_attlistDeclHandler(parser->m_handlerArg, parser->m_declElementType->name,
                             parser->m_declAttributeId->name, parser->m_declAttributeType,
                             attVal,
                             role == XML_ROLE_FIXED_ATTRIBUTE_VALUE);
          poolClear(&parser->m_tempPool);
          handleDefault = XML_FALSE;
        }
      }
      break;
    case XML_ROLE_ENTITY_VALUE:
      if (dtd->keepProcessing) {
        enum XML_Error result = storeEntityValue(parser, enc,
                                            s + enc->minBytesPerChar,
                                            next - enc->minBytesPerChar);
        if (parser->m_declEntity) {
          parser->m_declEntity->textPtr = poolStart(&dtd->entityValuePool);
          parser->m_declEntity->textLen = (int)(poolLength(&dtd->entityValuePool));
          poolFinish(&dtd->entityValuePool);
          if (parser->m_entityDeclHandler) {
            *eventEndPP = s;
            parser->m_entityDeclHandler(parser->m_handlerArg,
                              parser->m_declEntity->name,
                              parser->m_declEntity->is_param,
                              parser->m_declEntity->textPtr,
                              parser->m_declEntity->textLen,
                              parser->m_curBase, 0, 0, 0);
            handleDefault = XML_FALSE;
          }
        }
        else
          poolDiscard(&dtd->entityValuePool);
        if (result != XML_ERROR_NONE)
          return result;
      }
      break;
    case XML_ROLE_DOCTYPE_SYSTEM_ID:
#ifdef XML_DTD
      parser->m_useForeignDTD = XML_FALSE;
#endif /* XML_DTD */
      dtd->hasParamEntityRefs = XML_TRUE;
      if (parser->m_startDoctypeDeclHandler) {
        parser->m_doctypeSysid = poolStoreString(&parser->m_tempPool, enc,
                                       s + enc->minBytesPerChar,
                                       next - enc->minBytesPerChar);
        if (parser->m_doctypeSysid == NULL)
          return XML_ERROR_NO_MEMORY;
        poolFinish(&parser->m_tempPool);
        handleDefault = XML_FALSE;
      }
#ifdef XML_DTD
      else
        /* use externalSubsetName to make parser->m_doctypeSysid non-NULL
           for the case where no parser->m_startDoctypeDeclHandler is set */
        parser->m_doctypeSysid = externalSubsetName;
#endif /* XML_DTD */
      if (!dtd->standalone
#ifdef XML_DTD
          && !parser->m_paramEntityParsing
#endif /* XML_DTD */
          && parser->m_notStandaloneHandler
          && !parser->m_notStandaloneHandler(parser->m_handlerArg))
        return XML_ERROR_NOT_STANDALONE;
#ifndef XML_DTD
      break;
#else /* XML_DTD */
      if (!parser->m_declEntity) {
        parser->m_declEntity = (ENTITY *)lookup(parser,
                                      &dtd->paramEntities,
                                      externalSubsetName,
                                      sizeof(ENTITY));
        if (!parser->m_declEntity)
          return XML_ERROR_NO_MEMORY;
        parser->m_declEntity->publicId = NULL;
      }
#endif /* XML_DTD */
      /* fall through */
    case XML_ROLE_ENTITY_SYSTEM_ID:
      if (dtd->keepProcessing && parser->m_declEntity) {
        parser->m_declEntity->systemId = poolStoreString(&dtd->pool, enc,
                                               s + enc->minBytesPerChar,
                                               next - enc->minBytesPerChar);
        if (!parser->m_declEntity->systemId)
          return XML_ERROR_NO_MEMORY;
        parser->m_declEntity->base = parser->m_curBase;
        poolFinish(&dtd->pool);
        /* Don't suppress the default handler if we fell through from
         * the XML_ROLE_DOCTYPE_SYSTEM_ID case.
         */
        if (parser->m_entityDeclHandler && role == XML_ROLE_ENTITY_SYSTEM_ID)
          handleDefault = XML_FALSE;
      }
      break;
    case XML_ROLE_ENTITY_COMPLETE:
      if (dtd->keepProcessing && parser->m_declEntity && parser->m_entityDeclHandler) {
        *eventEndPP = s;
        parser->m_entityDeclHandler(parser->m_handlerArg,
                          parser->m_declEntity->name,
                          parser->m_declEntity->is_param,
                          0,0,
                          parser->m_declEntity->base,
                          parser->m_declEntity->systemId,
                          parser->m_declEntity->publicId,
                          0);
        handleDefault = XML_FALSE;
      }
      break;
    case XML_ROLE_ENTITY_NOTATION_NAME:
      if (dtd->keepProcessing && parser->m_declEntity) {
        parser->m_declEntity->notation = poolStoreString(&dtd->pool, enc, s, next);
        if (!parser->m_declEntity->notation)
          return XML_ERROR_NO_MEMORY;
        poolFinish(&dtd->pool);
        if (parser->m_unparsedEntityDeclHandler) {
          *eventEndPP = s;
          parser->m_unparsedEntityDeclHandler(parser->m_handlerArg,
                                    parser->m_declEntity->name,
                                    parser->m_declEntity->base,
                                    parser->m_declEntity->systemId,
                                    parser->m_declEntity->publicId,
                                    parser->m_declEntity->notation);
          handleDefault = XML_FALSE;
        }
        else if (parser->m_entityDeclHandler) {
          *eventEndPP = s;
          parser->m_entityDeclHandler(parser->m_handlerArg,
                            parser->m_declEntity->name,
                            0,0,0,
                            parser->m_declEntity->base,
                            parser->m_declEntity->systemId,
                            parser->m_declEntity->publicId,
                            parser->m_declEntity->notation);
          handleDefault = XML_FALSE;
        }
      }
      break;
    case XML_ROLE_GENERAL_ENTITY_NAME:
      {
        if (XmlPredefinedEntityName(enc, s, next)) {
          parser->m_declEntity = NULL;
          break;
        }
        if (dtd->keepProcessing) {
          const XML_Char *name = poolStoreString(&dtd->pool, enc, s, next);
          if (!name)
            return XML_ERROR_NO_MEMORY;
          parser->m_declEntity = (ENTITY *)lookup(parser, &dtd->generalEntities, name,
                                        sizeof(ENTITY));
          if (!parser->m_declEntity)
            return XML_ERROR_NO_MEMORY;
          if (parser->m_declEntity->name != name) {
            poolDiscard(&dtd->pool);
            parser->m_declEntity = NULL;
          }
          else {
            poolFinish(&dtd->pool);
            parser->m_declEntity->publicId = NULL;
            parser->m_declEntity->is_param = XML_FALSE;
            /* if we have a parent parser or are reading an internal parameter
               entity, then the entity declaration is not considered "internal"
            */
            parser->m_declEntity->is_internal = !(parser->m_parentParser || parser->m_openInternalEntities);
            if (parser->m_entityDeclHandler)
              handleDefault = XML_FALSE;
          }
        }
        else {
          poolDiscard(&dtd->pool);
          parser->m_declEntity = NULL;
        }
      }
      break;
    case XML_ROLE_PARAM_ENTITY_NAME:
#ifdef XML_DTD
      if (dtd->keepProcessing) {
        const XML_Char *name = poolStoreString(&dtd->pool, enc, s, next);
        if (!name)
          return XML_ERROR_NO_MEMORY;
        parser->m_declEntity = (ENTITY *)lookup(parser, &dtd->paramEntities,
                                           name, sizeof(ENTITY));
        if (!parser->m_declEntity)
          return XML_ERROR_NO_MEMORY;
        if (parser->m_declEntity->name != name) {
          poolDiscard(&dtd->pool);
          parser->m_declEntity = NULL;
        }
        else {
          poolFinish(&dtd->pool);
          parser->m_declEntity->publicId = NULL;
          parser->m_declEntity->is_param = XML_TRUE;
          /* if we have a parent parser or are reading an internal parameter
             entity, then the entity declaration is not considered "internal"
          */
          parser->m_declEntity->is_internal = !(parser->m_parentParser || parser->m_openInternalEntities);
          if (parser->m_entityDeclHandler)
            handleDefault = XML_FALSE;
        }
      }
      else {
        poolDiscard(&dtd->pool);
        parser->m_declEntity = NULL;
      }
#else /* not XML_DTD */
      parser->m_declEntity = NULL;
#endif /* XML_DTD */
      break;
    case XML_ROLE_NOTATION_NAME:
      parser->m_declNotationPublicId = NULL;
      parser->m_declNotationName = NULL;
      if (parser->m_notationDeclHandler) {
        parser->m_declNotationName = poolStoreString(&parser->m_tempPool, enc, s, next);
        if (!parser->m_declNotationName)
          return XML_ERROR_NO_MEMORY;
        poolFinish(&parser->m_tempPool);
        handleDefault = XML_FALSE;
      }
      break;
    case XML_ROLE_NOTATION_PUBLIC_ID:
      if (!XmlIsPublicId(enc, s, next, eventPP))
        return XML_ERROR_PUBLICID;
      if (parser->m_declNotationName) {  /* means m_notationDeclHandler != NULL */
        XML_Char *tem = poolStoreString(&parser->m_tempPool,
                                        enc,
                                        s + enc->minBytesPerChar,
                                        next - enc->minBytesPerChar);
        if (!tem)
          return XML_ERROR_NO_MEMORY;
        normalizePublicId(tem);
        parser->m_declNotationPublicId = tem;
        poolFinish(&parser->m_tempPool);
        handleDefault = XML_FALSE;
      }
      break;
    case XML_ROLE_NOTATION_SYSTEM_ID:
      if (parser->m_declNotationName && parser->m_notationDeclHandler) {
        const XML_Char *systemId
          = poolStoreString(&parser->m_tempPool, enc,
                            s + enc->minBytesPerChar,
                            next - enc->minBytesPerChar);
        if (!systemId)
          return XML_ERROR_NO_MEMORY;
        *eventEndPP = s;
        parser->m_notationDeclHandler(parser->m_handlerArg,
                            parser->m_declNotationName,
                            parser->m_curBase,
                            systemId,
                            parser->m_declNotationPublicId);
        handleDefault = XML_FALSE;
      }
      poolClear(&parser->m_tempPool);
      break;
    case XML_ROLE_NOTATION_NO_SYSTEM_ID:
      if (parser->m_declNotationPublicId && parser->m_notationDeclHandler) {
        *eventEndPP = s;
        parser->m_notationDeclHandler(parser->m_handlerArg,
                            parser->m_declNotationName,
                            parser->m_curBase,
                            0,
                            parser->m_declNotationPublicId);
        handleDefault = XML_FALSE;
      }
      poolClear(&parser->m_tempPool);
      break;
    case XML_ROLE_ERROR:
      switch (tok) {
      case XML_TOK_PARAM_ENTITY_REF:
        /* PE references in internal subset are
           not allowed within declarations. */
        return XML_ERROR_PARAM_ENTITY_REF;
      case XML_TOK_XML_DECL:
        return XML_ERROR_MISPLACED_XML_PI;
      default:
        return XML_ERROR_SYNTAX;
      }
#ifdef XML_DTD
    case XML_ROLE_IGNORE_SECT:
      {
        enum XML_Error result;
        if (parser->m_defaultHandler)
          reportDefault(parser, enc, s, next);
        handleDefault = XML_FALSE;
        result = doIgnoreSection(parser, enc, &next, end, nextPtr, haveMore);
        if (result != XML_ERROR_NONE)
          return result;
        else if (!next) {
          parser->m_processor = ignoreSectionProcessor;
          return result;
        }
      }
      break;
#endif /* XML_DTD */
    case XML_ROLE_GROUP_OPEN:
      if (parser->m_prologState.level >= parser->m_groupSize) {
        if (parser->m_groupSize) {
          char *temp = (char *)REALLOC(parser, parser->m_groupConnector, parser->m_groupSize *= 2);
          if (temp == NULL) {
            parser->m_groupSize /= 2;
            return XML_ERROR_NO_MEMORY;
          }
          parser->m_groupConnector = temp;
          if (dtd->scaffIndex) {
            int *temp = (int *)REALLOC(parser, dtd->scaffIndex,
                          parser->m_groupSize * sizeof(int));
            if (temp == NULL)
              return XML_ERROR_NO_MEMORY;
            dtd->scaffIndex = temp;
          }
        }
        else {
          parser->m_groupConnector = (char *)MALLOC(parser, parser->m_groupSize = 32);
          if (!parser->m_groupConnector) {
            parser->m_groupSize = 0;
            return XML_ERROR_NO_MEMORY;
          }
        }
      }
      parser->m_groupConnector[parser->m_prologState.level] = 0;
      if (dtd->in_eldecl) {
        int myindex = nextScaffoldPart(parser);
        if (myindex < 0)
          return XML_ERROR_NO_MEMORY;
        dtd->scaffIndex[dtd->scaffLevel] = myindex;
        dtd->scaffLevel++;
        dtd->scaffold[myindex].type = XML_CTYPE_SEQ;
        if (parser->m_elementDeclHandler)
          handleDefault = XML_FALSE;
      }
      break;
    case XML_ROLE_GROUP_SEQUENCE:
      if (parser->m_groupConnector[parser->m_prologState.level] == ASCII_PIPE)
        return XML_ERROR_SYNTAX;
      parser->m_groupConnector[parser->m_prologState.level] = ASCII_COMMA;
      if (dtd->in_eldecl && parser->m_elementDeclHandler)
        handleDefault = XML_FALSE;
      break;
    case XML_ROLE_GROUP_CHOICE:
      if (parser->m_groupConnector[parser->m_prologState.level] == ASCII_COMMA)
        return XML_ERROR_SYNTAX;
      if (dtd->in_eldecl
          && !parser->m_groupConnector[parser->m_prologState.level]
          && (dtd->scaffold[dtd->scaffIndex[dtd->scaffLevel - 1]].type
              != XML_CTYPE_MIXED)
          ) {
        dtd->scaffold[dtd->scaffIndex[dtd->scaffLevel - 1]].type
            = XML_CTYPE_CHOICE;
        if (parser->m_elementDeclHandler)
          handleDefault = XML_FALSE;
      }
      parser->m_groupConnector[parser->m_prologState.level] = ASCII_PIPE;
      break;
    case XML_ROLE_PARAM_ENTITY_REF:
#ifdef XML_DTD
    case XML_ROLE_INNER_PARAM_ENTITY_REF:
      dtd->hasParamEntityRefs = XML_TRUE;
      if (!parser->m_paramEntityParsing)
        dtd->keepProcessing = dtd->standalone;
      else {
        const XML_Char *name;
        ENTITY *entity;
        name = poolStoreString(&dtd->pool, enc,
                                s + enc->minBytesPerChar,
                                next - enc->minBytesPerChar);
        if (!name)
          return XML_ERROR_NO_MEMORY;
        entity = (ENTITY *)lookup(parser, &dtd->paramEntities, name, 0);
        poolDiscard(&dtd->pool);
        /* first, determine if a check for an existing declaration is needed;
           if yes, check that the entity exists, and that it is internal,
           otherwise call the skipped entity handler
        */
        if (parser->m_prologState.documentEntity &&
            (dtd->standalone
             ? !parser->m_openInternalEntities
             : !dtd->hasParamEntityRefs)) {
          if (!entity)
            return XML_ERROR_UNDEFINED_ENTITY;
          else if (!entity->is_internal) {
            /* It's hard to exhaustively search the code to be sure,
             * but there doesn't seem to be a way of executing the
             * following line.  There are two cases:
             *
             * If 'standalone' is false, the DTD must have no
             * parameter entities or we wouldn't have passed the outer
             * 'if' statement.  That measn the only entity in the hash
             * table is the external subset name "#" which cannot be
             * given as a parameter entity name in XML syntax, so the
             * lookup must have returned NULL and we don't even reach
             * the test for an internal entity.
             *
             * If 'standalone' is true, it does not seem to be
             * possible to create entities taking this code path that
             * are not internal entities, so fail the test above.
             *
             * Because this analysis is very uncertain, the code is
             * being left in place and merely removed from the
             * coverage test statistics.
             */
            return XML_ERROR_ENTITY_DECLARED_IN_PE; /* LCOV_EXCL_LINE */
          }
        }
        else if (!entity) {
          dtd->keepProcessing = dtd->standalone;
          /* cannot report skipped entities in declarations */
          if ((role == XML_ROLE_PARAM_ENTITY_REF) && parser->m_skippedEntityHandler) {
            parser->m_skippedEntityHandler(parser->m_handlerArg, name, 1);
            handleDefault = XML_FALSE;
          }
          break;
        }
        if (entity->open)
          return XML_ERROR_RECURSIVE_ENTITY_REF;
        if (entity->textPtr) {
          enum XML_Error result;
          XML_Bool betweenDecl =
            (role == XML_ROLE_PARAM_ENTITY_REF ? XML_TRUE : XML_FALSE);
          result = processInternalEntity(parser, entity, betweenDecl);
          if (result != XML_ERROR_NONE)
            return result;
          handleDefault = XML_FALSE;
          break;
        }
        if (parser->m_externalEntityRefHandler) {
          dtd->paramEntityRead = XML_FALSE;
          entity->open = XML_TRUE;
          if (!parser->m_externalEntityRefHandler(parser->m_externalEntityRefHandlerArg,
                                        0,
                                        entity->base,
                                        entity->systemId,
                                        entity->publicId)) {
            entity->open = XML_FALSE;
            return XML_ERROR_EXTERNAL_ENTITY_HANDLING;
          }
          entity->open = XML_FALSE;
          handleDefault = XML_FALSE;
          if (!dtd->paramEntityRead) {
            dtd->keepProcessing = dtd->standalone;
            break;
          }
        }
        else {
          dtd->keepProcessing = dtd->standalone;
          break;
        }
      }
#endif /* XML_DTD */
      if (!dtd->standalone &&
          parser->m_notStandaloneHandler &&
          !parser->m_notStandaloneHandler(parser->m_handlerArg))
        return XML_ERROR_NOT_STANDALONE;
      break;

    /* Element declaration stuff */

    case XML_ROLE_ELEMENT_NAME:
      if (parser->m_elementDeclHandler) {
        parser->m_declElementType = getElementType(parser, enc, s, next);
        if (!parser->m_declElementType)
          return XML_ERROR_NO_MEMORY;
        dtd->scaffLevel = 0;
        dtd->scaffCount = 0;
        dtd->in_eldecl = XML_TRUE;
        handleDefault = XML_FALSE;
      }
      break;

    case XML_ROLE_CONTENT_ANY:
    case XML_ROLE_CONTENT_EMPTY:
      if (dtd->in_eldecl) {
        if (parser->m_elementDeclHandler) {
          XML_Content * content = (XML_Content *) MALLOC(parser, sizeof(XML_Content));
          if (!content)
            return XML_ERROR_NO_MEMORY;
          content->quant = XML_CQUANT_NONE;
          content->name = NULL;
          content->numchildren = 0;
          content->children = NULL;
          content->type = ((role == XML_ROLE_CONTENT_ANY) ?
                           XML_CTYPE_ANY :
                           XML_CTYPE_EMPTY);
          *eventEndPP = s;
          parser->m_elementDeclHandler(parser->m_handlerArg, parser->m_declElementType->name, content);
          handleDefault = XML_FALSE;
        }
        dtd->in_eldecl = XML_FALSE;
      }
      break;

    case XML_ROLE_CONTENT_PCDATA:
      if (dtd->in_eldecl) {
        dtd->scaffold[dtd->scaffIndex[dtd->scaffLevel - 1]].type
            = XML_CTYPE_MIXED;
        if (parser->m_elementDeclHandler)
          handleDefault = XML_FALSE;
      }
      break;

    case XML_ROLE_CONTENT_ELEMENT:
      quant = XML_CQUANT_NONE;
      goto elementContent;
    case XML_ROLE_CONTENT_ELEMENT_OPT:
      quant = XML_CQUANT_OPT;
      goto elementContent;
    case XML_ROLE_CONTENT_ELEMENT_REP:
      quant = XML_CQUANT_REP;
      goto elementContent;
    case XML_ROLE_CONTENT_ELEMENT_PLUS:
      quant = XML_CQUANT_PLUS;
    elementContent:
      if (dtd->in_eldecl) {
        ELEMENT_TYPE *el;
        const XML_Char *name;
        int nameLen;
        const char *nxt = (quant == XML_CQUANT_NONE
                           ? next
                           : next - enc->minBytesPerChar);
        int myindex = nextScaffoldPart(parser);
        if (myindex < 0)
          return XML_ERROR_NO_MEMORY;
        dtd->scaffold[myindex].type = XML_CTYPE_NAME;
        dtd->scaffold[myindex].quant = quant;
        el = getElementType(parser, enc, s, nxt);
        if (!el)
          return XML_ERROR_NO_MEMORY;
        name = el->name;
        dtd->scaffold[myindex].name = name;
        nameLen = 0;
        for (; name[nameLen++]; );
        dtd->contentStringLen +=  nameLen;
        if (parser->m_elementDeclHandler)
          handleDefault = XML_FALSE;
      }
      break;

    case XML_ROLE_GROUP_CLOSE:
      quant = XML_CQUANT_NONE;
      goto closeGroup;
    case XML_ROLE_GROUP_CLOSE_OPT:
      quant = XML_CQUANT_OPT;
      goto closeGroup;
    case XML_ROLE_GROUP_CLOSE_REP:
      quant = XML_CQUANT_REP;
      goto closeGroup;
    case XML_ROLE_GROUP_CLOSE_PLUS:
      quant = XML_CQUANT_PLUS;
    closeGroup:
      if (dtd->in_eldecl) {
        if (parser->m_elementDeclHandler)
          handleDefault = XML_FALSE;
        dtd->scaffLevel--;
        dtd->scaffold[dtd->scaffIndex[dtd->scaffLevel]].quant = quant;
        if (dtd->scaffLevel == 0) {
          if (!handleDefault) {
            XML_Content *model = build_model(parser);
            if (!model)
              return XML_ERROR_NO_MEMORY;
            *eventEndPP = s;
            parser->m_elementDeclHandler(parser->m_handlerArg, parser->m_declElementType->name, model);
          }
          dtd->in_eldecl = XML_FALSE;
          dtd->contentStringLen = 0;
        }
      }
      break;
      /* End element declaration stuff */

    case XML_ROLE_PI:
      if (!reportProcessingInstruction(parser, enc, s, next))
        return XML_ERROR_NO_MEMORY;
      handleDefault = XML_FALSE;
      break;
    case XML_ROLE_COMMENT:
      if (!reportComment(parser, enc, s, next))
        return XML_ERROR_NO_MEMORY;
      handleDefault = XML_FALSE;
      break;
    case XML_ROLE_NONE:
      switch (tok) {
      case XML_TOK_BOM:
        handleDefault = XML_FALSE;
        break;
      }
      break;
    case XML_ROLE_DOCTYPE_NONE:
      if (parser->m_startDoctypeDeclHandler)
        handleDefault = XML_FALSE;
      break;
    case XML_ROLE_ENTITY_NONE:
      if (dtd->keepProcessing && parser->m_entityDeclHandler)
        handleDefault = XML_FALSE;
      break;
    case XML_ROLE_NOTATION_NONE:
      if (parser->m_notationDeclHandler)
        handleDefault = XML_FALSE;
      break;
    case XML_ROLE_ATTLIST_NONE:
      if (dtd->keepProcessing && parser->m_attlistDeclHandler)
        handleDefault = XML_FALSE;
      break;
    case XML_ROLE_ELEMENT_NONE:
      if (parser->m_elementDeclHandler)
        handleDefault = XML_FALSE;
      break;
    } /* end of big switch */

    if (handleDefault && parser->m_defaultHandler)
      reportDefault(parser, enc, s, next);

    switch (parser->m_parsingStatus.parsing) {
    case XML_SUSPENDED:
      *nextPtr = next;
      return XML_ERROR_NONE;
    case XML_FINISHED:
      return XML_ERROR_ABORTED;
    default:
      s = next;
      tok = XmlPrologTok(enc, s, end, &next);
    }
  }
  /* not reached */
}

static enum XML_Error PTRCALL
epilogProcessor(XML_Parser parser,
                const char *s,
                const char *end,
                const char **nextPtr)
{
  parser->m_processor = epilogProcessor;
  parser->m_eventPtr = s;
  for (;;) {
    const char *next = NULL;
    int tok = XmlPrologTok(parser->m_encoding, s, end, &next);
    parser->m_eventEndPtr = next;
    switch (tok) {
    /* report partial linebreak - it might be the last token */
    case -XML_TOK_PROLOG_S:
      if (parser->m_defaultHandler) {
        reportDefault(parser, parser->m_encoding, s, next);
        if (parser->m_parsingStatus.parsing == XML_FINISHED)
          return XML_ERROR_ABORTED;
      }
      *nextPtr = next;
      return XML_ERROR_NONE;
    case XML_TOK_NONE:
      *nextPtr = s;
      return XML_ERROR_NONE;
    case XML_TOK_PROLOG_S:
      if (parser->m_defaultHandler)
        reportDefault(parser, parser->m_encoding, s, next);
      break;
    case XML_TOK_PI:
      if (!reportProcessingInstruction(parser, parser->m_encoding, s, next))
        return XML_ERROR_NO_MEMORY;
      break;
    case XML_TOK_COMMENT:
      if (!reportComment(parser, parser->m_encoding, s, next))
        return XML_ERROR_NO_MEMORY;
      break;
    case XML_TOK_INVALID:
      parser->m_eventPtr = next;
      return XML_ERROR_INVALID_TOKEN;
    case XML_TOK_PARTIAL:
      if (!parser->m_parsingStatus.finalBuffer) {
        *nextPtr = s;
        return XML_ERROR_NONE;
      }
      return XML_ERROR_UNCLOSED_TOKEN;
    case XML_TOK_PARTIAL_CHAR:
      if (!parser->m_parsingStatus.finalBuffer) {
        *nextPtr = s;
        return XML_ERROR_NONE;
      }
      return XML_ERROR_PARTIAL_CHAR;
    default:
      return XML_ERROR_JUNK_AFTER_DOC_ELEMENT;
    }
    parser->m_eventPtr = s = next;
    switch (parser->m_parsingStatus.parsing) {
    case XML_SUSPENDED:
      *nextPtr = next;
      return XML_ERROR_NONE;
    case XML_FINISHED:
      return XML_ERROR_ABORTED;
    default: ;
    }
  }
}

static enum XML_Error
processInternalEntity(XML_Parser parser, ENTITY *entity,
                      XML_Bool betweenDecl)
{
  const char *textStart, *textEnd;
  const char *next;
  enum XML_Error result;
  OPEN_INTERNAL_ENTITY *openEntity;

  if (parser->m_freeInternalEntities) {
    openEntity = parser->m_freeInternalEntities;
    parser->m_freeInternalEntities = openEntity->next;
  }
  else {
    openEntity = (OPEN_INTERNAL_ENTITY *)MALLOC(parser, sizeof(OPEN_INTERNAL_ENTITY));
    if (!openEntity)
      return XML_ERROR_NO_MEMORY;
  }
  entity->open = XML_TRUE;
  entity->processed = 0;
  openEntity->next = parser->m_openInternalEntities;
  parser->m_openInternalEntities = openEntity;
  openEntity->entity = entity;
  openEntity->startTagLevel = parser->m_tagLevel;
  openEntity->betweenDecl = betweenDecl;
  openEntity->internalEventPtr = NULL;
  openEntity->internalEventEndPtr = NULL;
  textStart = (char *)entity->textPtr;
  textEnd = (char *)(entity->textPtr + entity->textLen);
  /* Set a safe default value in case 'next' does not get set */
  next = textStart;

#ifdef XML_DTD
  if (entity->is_param) {
    int tok = XmlPrologTok(parser->m_internalEncoding, textStart, textEnd, &next);
    result = doProlog(parser, parser->m_internalEncoding, textStart, textEnd, tok,
                      next, &next, XML_FALSE);
  }
  else
#endif /* XML_DTD */
    result = doContent(parser, parser->m_tagLevel, parser->m_internalEncoding, textStart,
                       textEnd, &next, XML_FALSE);

  if (result == XML_ERROR_NONE) {
    if (textEnd != next && parser->m_parsingStatus.parsing == XML_SUSPENDED) {
      entity->processed = (int)(next - textStart);
      parser->m_processor = internalEntityProcessor;
    }
    else {
      entity->open = XML_FALSE;
      parser->m_openInternalEntities = openEntity->next;
      /* put openEntity back in list of free instances */
      openEntity->next = parser->m_freeInternalEntities;
      parser->m_freeInternalEntities = openEntity;
    }
  }
  return result;
}

static enum XML_Error PTRCALL
internalEntityProcessor(XML_Parser parser,
                        const char *s,
                        const char *end,
                        const char **nextPtr)
{
  ENTITY *entity;
  const char *textStart, *textEnd;
  const char *next;
  enum XML_Error result;
  OPEN_INTERNAL_ENTITY *openEntity = parser->m_openInternalEntities;
  if (!openEntity)
    return XML_ERROR_UNEXPECTED_STATE;

  entity = openEntity->entity;
  textStart = ((char *)entity->textPtr) + entity->processed;
  textEnd = (char *)(entity->textPtr + entity->textLen);
  /* Set a safe default value in case 'next' does not get set */
  next = textStart;

#ifdef XML_DTD
  if (entity->is_param) {
    int tok = XmlPrologTok(parser->m_internalEncoding, textStart, textEnd, &next);
    result = doProlog(parser, parser->m_internalEncoding, textStart, textEnd, tok,
                      next, &next, XML_FALSE);
  }
  else
#endif /* XML_DTD */
    result = doContent(parser, openEntity->startTagLevel, parser->m_internalEncoding,
                       textStart, textEnd, &next, XML_FALSE);

  if (result != XML_ERROR_NONE)
    return result;
  else if (textEnd != next && parser->m_parsingStatus.parsing == XML_SUSPENDED) {
    entity->processed = (int)(next - (char *)entity->textPtr);
    return result;
  }
  else {
    entity->open = XML_FALSE;
    parser->m_openInternalEntities = openEntity->next;
    /* put openEntity back in list of free instances */
    openEntity->next = parser->m_freeInternalEntities;
    parser->m_freeInternalEntities = openEntity;
  }

#ifdef XML_DTD
  if (entity->is_param) {
    int tok;
    parser->m_processor = prologProcessor;
    tok = XmlPrologTok(parser->m_encoding, s, end, &next);
    return doProlog(parser, parser->m_encoding, s, end, tok, next, nextPtr,
                    (XML_Bool)!parser->m_parsingStatus.finalBuffer);
  }
  else
#endif /* XML_DTD */
  {
    parser->m_processor = contentProcessor;
    /* see externalEntityContentProcessor vs contentProcessor */
    return doContent(parser, parser->m_parentParser ? 1 : 0, parser->m_encoding, s, end,
                     nextPtr, (XML_Bool)!parser->m_parsingStatus.finalBuffer);
  }
}

static enum XML_Error PTRCALL
errorProcessor(XML_Parser parser,
               const char *UNUSED_P(s),
               const char *UNUSED_P(end),
               const char **UNUSED_P(nextPtr))
{
  return parser->m_errorCode;
}

static enum XML_Error
storeAttributeValue(XML_Parser parser, const ENCODING *enc, XML_Bool isCdata,
                    const char *ptr, const char *end,
                    STRING_POOL *pool)
{
  enum XML_Error result = appendAttributeValue(parser, enc, isCdata, ptr,
                                               end, pool);
  if (result)
    return result;
  if (!isCdata && poolLength(pool) && poolLastChar(pool) == 0x20)
    poolChop(pool);
  if (!poolAppendChar(pool, XML_T('\0')))
    return XML_ERROR_NO_MEMORY;
  return XML_ERROR_NONE;
}

static enum XML_Error
appendAttributeValue(XML_Parser parser, const ENCODING *enc, XML_Bool isCdata,
                     const char *ptr, const char *end,
                     STRING_POOL *pool)
{
  DTD * const dtd = parser->m_dtd;  /* save one level of indirection */
  for (;;) {
    const char *next;
    int tok = XmlAttributeValueTok(enc, ptr, end, &next);
    switch (tok) {
    case XML_TOK_NONE:
      return XML_ERROR_NONE;
    case XML_TOK_INVALID:
      if (enc == parser->m_encoding)
        parser->m_eventPtr = next;
      return XML_ERROR_INVALID_TOKEN;
    case XML_TOK_PARTIAL:
      if (enc == parser->m_encoding)
        parser->m_eventPtr = ptr;
      return XML_ERROR_INVALID_TOKEN;
    case XML_TOK_CHAR_REF:
      {
        XML_Char buf[XML_ENCODE_MAX];
        int i;
        int n = XmlCharRefNumber(enc, ptr);
        if (n < 0) {
          if (enc == parser->m_encoding)
            parser->m_eventPtr = ptr;
          return XML_ERROR_BAD_CHAR_REF;
        }
        if (!isCdata
            && n == 0x20 /* space */
            && (poolLength(pool) == 0 || poolLastChar(pool) == 0x20))
          break;
        n = XmlEncode(n, (ICHAR *)buf);
        /* The XmlEncode() functions can never return 0 here.  That
         * error return happens if the code point passed in is either
         * negative or greater than or equal to 0x110000.  The
         * XmlCharRefNumber() functions will all return a number
         * strictly less than 0x110000 or a negative value if an error
         * occurred.  The negative value is intercepted above, so
         * XmlEncode() is never passed a value it might return an
         * error for.
         */
        for (i = 0; i < n; i++) {
          if (!poolAppendChar(pool, buf[i]))
            return XML_ERROR_NO_MEMORY;
        }
      }
      break;
    case XML_TOK_DATA_CHARS:
      if (!poolAppend(pool, enc, ptr, next))
        return XML_ERROR_NO_MEMORY;
      break;
    case XML_TOK_TRAILING_CR:
      next = ptr + enc->minBytesPerChar;
      /* fall through */
    case XML_TOK_ATTRIBUTE_VALUE_S:
    case XML_TOK_DATA_NEWLINE:
      if (!isCdata && (poolLength(pool) == 0 || poolLastChar(pool) == 0x20))
        break;
      if (!poolAppendChar(pool, 0x20))
        return XML_ERROR_NO_MEMORY;
      break;
    case XML_TOK_ENTITY_REF:
      {
        const XML_Char *name;
        ENTITY *entity;
        char checkEntityDecl;
        XML_Char ch = (XML_Char) XmlPredefinedEntityName(enc,
                                              ptr + enc->minBytesPerChar,
                                              next - enc->minBytesPerChar);
        if (ch) {
          if (!poolAppendChar(pool, ch))
                return XML_ERROR_NO_MEMORY;
          break;
        }
        name = poolStoreString(&parser->m_temp2Pool, enc,
                               ptr + enc->minBytesPerChar,
                               next - enc->minBytesPerChar);
        if (!name)
          return XML_ERROR_NO_MEMORY;
        entity = (ENTITY *)lookup(parser, &dtd->generalEntities, name, 0);
        poolDiscard(&parser->m_temp2Pool);
        /* First, determine if a check for an existing declaration is needed;
           if yes, check that the entity exists, and that it is internal.
        */
        if (pool == &dtd->pool)  /* are we called from prolog? */
          checkEntityDecl =
#ifdef XML_DTD
              parser->m_prologState.documentEntity &&
#endif /* XML_DTD */
              (dtd->standalone
               ? !parser->m_openInternalEntities
               : !dtd->hasParamEntityRefs);
        else /* if (pool == &parser->m_tempPool): we are called from content */
          checkEntityDecl = !dtd->hasParamEntityRefs || dtd->standalone;
        if (checkEntityDecl) {
          if (!entity)
            return XML_ERROR_UNDEFINED_ENTITY;
          else if (!entity->is_internal)
            return XML_ERROR_ENTITY_DECLARED_IN_PE;
        }
        else if (!entity) {
          /* Cannot report skipped entity here - see comments on
             parser->m_skippedEntityHandler.
          if (parser->m_skippedEntityHandler)
            parser->m_skippedEntityHandler(parser->m_handlerArg, name, 0);
          */
          /* Cannot call the default handler because this would be
             out of sync with the call to the startElementHandler.
          if ((pool == &parser->m_tempPool) && parser->m_defaultHandler)
            reportDefault(parser, enc, ptr, next);
          */
          break;
        }
        if (entity->open) {
          if (enc == parser->m_encoding) {
            /* It does not appear that this line can be executed.
             *
             * The "if (entity->open)" check catches recursive entity
             * definitions.  In order to be called with an open
             * entity, it must have gone through this code before and
             * been through the recursive call to
             * appendAttributeValue() some lines below.  That call
             * sets the local encoding ("enc") to the parser's
             * internal encoding (internal_utf8 or internal_utf16),
             * which can never be the same as the principle encoding.
             * It doesn't appear there is another code path that gets
             * here with entity->open being TRUE.
             *
             * Since it is not certain that this logic is watertight,
             * we keep the line and merely exclude it from coverage
             * tests.
             */
            parser->m_eventPtr = ptr; /* LCOV_EXCL_LINE */
          }
          return XML_ERROR_RECURSIVE_ENTITY_REF;
        }
        if (entity->notation) {
          if (enc == parser->m_encoding)
            parser->m_eventPtr = ptr;
          return XML_ERROR_BINARY_ENTITY_REF;
        }
        if (!entity->textPtr) {
          if (enc == parser->m_encoding)
            parser->m_eventPtr = ptr;
          return XML_ERROR_ATTRIBUTE_EXTERNAL_ENTITY_REF;
        }
        else {
          enum XML_Error result;
          const XML_Char *textEnd = entity->textPtr + entity->textLen;
          entity->open = XML_TRUE;
          result = appendAttributeValue(parser, parser->m_internalEncoding, isCdata,
                                        (char *)entity->textPtr,
                                        (char *)textEnd, pool);
          entity->open = XML_FALSE;
          if (result)
            return result;
        }
      }
      break;
    default:
      /* The only token returned by XmlAttributeValueTok() that does
       * not have an explicit case here is XML_TOK_PARTIAL_CHAR.
       * Getting that would require an entity name to contain an
       * incomplete XML character (e.g. \xE2\x82); however previous
       * tokenisers will have already recognised and rejected such
       * names before XmlAttributeValueTok() gets a look-in.  This
       * default case should be retained as a safety net, but the code
       * excluded from coverage tests.
       *
       * LCOV_EXCL_START
       */
      if (enc == parser->m_encoding)
        parser->m_eventPtr = ptr;
      return XML_ERROR_UNEXPECTED_STATE;
      /* LCOV_EXCL_STOP */
    }
    ptr = next;
  }
  /* not reached */
}

static enum XML_Error
storeEntityValue(XML_Parser parser,
                 const ENCODING *enc,
                 const char *entityTextPtr,
                 const char *entityTextEnd)
{
  DTD * const dtd = parser->m_dtd;  /* save one level of indirection */
  STRING_POOL *pool = &(dtd->entityValuePool);
  enum XML_Error result = XML_ERROR_NONE;
#ifdef XML_DTD
  int oldInEntityValue = parser->m_prologState.inEntityValue;
  parser->m_prologState.inEntityValue = 1;
#endif /* XML_DTD */
  /* never return Null for the value argument in EntityDeclHandler,
     since this would indicate an external entity; therefore we
     have to make sure that entityValuePool.start is not null */
  if (!pool->blocks) {
    if (!poolGrow(pool))
      return XML_ERROR_NO_MEMORY;
  }

  for (;;) {
    const char *next;
    int tok = XmlEntityValueTok(enc, entityTextPtr, entityTextEnd, &next);
    switch (tok) {
    case XML_TOK_PARAM_ENTITY_REF:
#ifdef XML_DTD
      if (parser->m_isParamEntity || enc != parser->m_encoding) {
        const XML_Char *name;
        ENTITY *entity;
        name = poolStoreString(&parser->m_tempPool, enc,
                               entityTextPtr + enc->minBytesPerChar,
                               next - enc->minBytesPerChar);
        if (!name) {
          result = XML_ERROR_NO_MEMORY;
          goto endEntityValue;
        }
        entity = (ENTITY *)lookup(parser, &dtd->paramEntities, name, 0);
        poolDiscard(&parser->m_tempPool);
        if (!entity) {
          /* not a well-formedness error - see XML 1.0: WFC Entity Declared */
          /* cannot report skipped entity here - see comments on
             parser->m_skippedEntityHandler
          if (parser->m_skippedEntityHandler)
            parser->m_skippedEntityHandler(parser->m_handlerArg, name, 0);
          */
          dtd->keepProcessing = dtd->standalone;
          goto endEntityValue;
        }
        if (entity->open) {
          if (enc == parser->m_encoding)
            parser->m_eventPtr = entityTextPtr;
          result = XML_ERROR_RECURSIVE_ENTITY_REF;
          goto endEntityValue;
        }
        if (entity->systemId) {
          if (parser->m_externalEntityRefHandler) {
            dtd->paramEntityRead = XML_FALSE;
            entity->open = XML_TRUE;
            if (!parser->m_externalEntityRefHandler(parser->m_externalEntityRefHandlerArg,
                                          0,
                                          entity->base,
                                          entity->systemId,
                                          entity->publicId)) {
              entity->open = XML_FALSE;
              result = XML_ERROR_EXTERNAL_ENTITY_HANDLING;
              goto endEntityValue;
            }
            entity->open = XML_FALSE;
            if (!dtd->paramEntityRead)
              dtd->keepProcessing = dtd->standalone;
          }
          else
            dtd->keepProcessing = dtd->standalone;
        }
        else {
          entity->open = XML_TRUE;
          result = storeEntityValue(parser,
                                    parser->m_internalEncoding,
                                    (char *)entity->textPtr,
                                    (char *)(entity->textPtr
                                             + entity->textLen));
          entity->open = XML_FALSE;
          if (result)
            goto endEntityValue;
        }
        break;
      }
#endif /* XML_DTD */
      /* In the internal subset, PE references are not legal
         within markup declarations, e.g entity values in this case. */
      parser->m_eventPtr = entityTextPtr;
      result = XML_ERROR_PARAM_ENTITY_REF;
      goto endEntityValue;
    case XML_TOK_NONE:
      result = XML_ERROR_NONE;
      goto endEntityValue;
    case XML_TOK_ENTITY_REF:
    case XML_TOK_DATA_CHARS:
      if (!poolAppend(pool, enc, entityTextPtr, next)) {
        result = XML_ERROR_NO_MEMORY;
        goto endEntityValue;
      }
      break;
    case XML_TOK_TRAILING_CR:
      next = entityTextPtr + enc->minBytesPerChar;
      /* fall through */
    case XML_TOK_DATA_NEWLINE:
      if (pool->end == pool->ptr && !poolGrow(pool)) {
              result = XML_ERROR_NO_MEMORY;
        goto endEntityValue;
      }
      *(pool->ptr)++ = 0xA;
      break;
    case XML_TOK_CHAR_REF:
      {
        XML_Char buf[XML_ENCODE_MAX];
        int i;
        int n = XmlCharRefNumber(enc, entityTextPtr);
        if (n < 0) {
          if (enc == parser->m_encoding)
            parser->m_eventPtr = entityTextPtr;
          result = XML_ERROR_BAD_CHAR_REF;
          goto endEntityValue;
        }
        n = XmlEncode(n, (ICHAR *)buf);
        /* The XmlEncode() functions can never return 0 here.  That
         * error return happens if the code point passed in is either
         * negative or greater than or equal to 0x110000.  The
         * XmlCharRefNumber() functions will all return a number
         * strictly less than 0x110000 or a negative value if an error
         * occurred.  The negative value is intercepted above, so
         * XmlEncode() is never passed a value it might return an
         * error for.
         */
        for (i = 0; i < n; i++) {
          if (pool->end == pool->ptr && !poolGrow(pool)) {
            result = XML_ERROR_NO_MEMORY;
            goto endEntityValue;
          }
          *(pool->ptr)++ = buf[i];
        }
      }
      break;
    case XML_TOK_PARTIAL:
      if (enc == parser->m_encoding)
        parser->m_eventPtr = entityTextPtr;
      result = XML_ERROR_INVALID_TOKEN;
      goto endEntityValue;
    case XML_TOK_INVALID:
      if (enc == parser->m_encoding)
        parser->m_eventPtr = next;
      result = XML_ERROR_INVALID_TOKEN;
      goto endEntityValue;
    default:
      /* This default case should be unnecessary -- all the tokens
       * that XmlEntityValueTok() can return have their own explicit
       * cases -- but should be retained for safety.  We do however
       * exclude it from the coverage statistics.
       *
       * LCOV_EXCL_START
       */
      if (enc == parser->m_encoding)
        parser->m_eventPtr = entityTextPtr;
      result = XML_ERROR_UNEXPECTED_STATE;
      goto endEntityValue;
      /* LCOV_EXCL_STOP */
    }
    entityTextPtr = next;
  }
endEntityValue:
#ifdef XML_DTD
  parser->m_prologState.inEntityValue = oldInEntityValue;
#endif /* XML_DTD */
  return result;
}

static void FASTCALL
normalizeLines(XML_Char *s)
{
  XML_Char *p;
  for (;; s++) {
    if (*s == XML_T('\0'))
      return;
    if (*s == 0xD)
      break;
  }
  p = s;
  do {
    if (*s == 0xD) {
      *p++ = 0xA;
      if (*++s == 0xA)
        s++;
    }
    else
      *p++ = *s++;
  } while (*s);
  *p = XML_T('\0');
}

static int
reportProcessingInstruction(XML_Parser parser, const ENCODING *enc,
                            const char *start, const char *end)
{
  const XML_Char *target;
  XML_Char *data;
  const char *tem;
  if (!parser->m_processingInstructionHandler) {
    if (parser->m_defaultHandler)
      reportDefault(parser, enc, start, end);
    return 1;
  }
  start += enc->minBytesPerChar * 2;
  tem = start + XmlNameLength(enc, start);
  target = poolStoreString(&parser->m_tempPool, enc, start, tem);
  if (!target)
    return 0;
  poolFinish(&parser->m_tempPool);
  data = poolStoreString(&parser->m_tempPool, enc,
                        XmlSkipS(enc, tem),
                        end - enc->minBytesPerChar*2);
  if (!data)
    return 0;
  normalizeLines(data);
  parser->m_processingInstructionHandler(parser->m_handlerArg, target, data);
  poolClear(&parser->m_tempPool);
  return 1;
}

static int
reportComment(XML_Parser parser, const ENCODING *enc,
              const char *start, const char *end)
{
  XML_Char *data;
  if (!parser->m_commentHandler) {
    if (parser->m_defaultHandler)
      reportDefault(parser, enc, start, end);
    return 1;
  }
  data = poolStoreString(&parser->m_tempPool,
                         enc,
                         start + enc->minBytesPerChar * 4,
                         end - enc->minBytesPerChar * 3);
  if (!data)
    return 0;
  normalizeLines(data);
  parser->m_commentHandler(parser->m_handlerArg, data);
  poolClear(&parser->m_tempPool);
  return 1;
}

static void
reportDefault(XML_Parser parser, const ENCODING *enc,
              const char *s, const char *end)
{
  if (MUST_CONVERT(enc, s)) {
    enum XML_Convert_Result convert_res;
    const char **eventPP;
    const char **eventEndPP;
    if (enc == parser->m_encoding) {
      eventPP = &parser->m_eventPtr;
      eventEndPP = &parser->m_eventEndPtr;
    }
    else {
      /* To get here, two things must be true; the parser must be
       * using a character encoding that is not the same as the
       * encoding passed in, and the encoding passed in must need
       * conversion to the internal format (UTF-8 unless XML_UNICODE
       * is defined).  The only occasions on which the encoding passed
       * in is not the same as the parser's encoding are when it is
       * the internal encoding (e.g. a previously defined parameter
       * entity, already converted to internal format).  This by
       * definition doesn't need conversion, so the whole branch never
       * gets executed.
       *
       * For safety's sake we don't delete these lines and merely
       * exclude them from coverage statistics.
       *
       * LCOV_EXCL_START
       */
      eventPP = &(parser->m_openInternalEntities->internalEventPtr);
      eventEndPP = &(parser->m_openInternalEntities->internalEventEndPtr);
      /* LCOV_EXCL_STOP */
    }
    do {
      ICHAR *dataPtr = (ICHAR *)parser->m_dataBuf;
      convert_res = XmlConvert(enc, &s, end, &dataPtr, (ICHAR *)parser->m_dataBufEnd);
      *eventEndPP = s;
      parser->m_defaultHandler(parser->m_handlerArg, parser->m_dataBuf, (int)(dataPtr - (ICHAR *)parser->m_dataBuf));
      *eventPP = s;
    } while ((convert_res != XML_CONVERT_COMPLETED) && (convert_res != XML_CONVERT_INPUT_INCOMPLETE));
  }
  else
    parser->m_defaultHandler(parser->m_handlerArg, (XML_Char *)s, (int)((XML_Char *)end - (XML_Char *)s));
}


static int
defineAttribute(ELEMENT_TYPE *type, ATTRIBUTE_ID *attId, XML_Bool isCdata,
                XML_Bool isId, const XML_Char *value, XML_Parser parser)
{
  DEFAULT_ATTRIBUTE *att;
  if (value || isId) {
    /* The handling of default attributes gets messed up if we have
       a default which duplicates a non-default. */
    int i;
    for (i = 0; i < type->nDefaultAtts; i++)
      if (attId == type->defaultAtts[i].id)
        return 1;
    if (isId && !type->idAtt && !attId->xmlns)
      type->idAtt = attId;
  }
  if (type->nDefaultAtts == type->allocDefaultAtts) {
    if (type->allocDefaultAtts == 0) {
      type->allocDefaultAtts = 8;
      type->defaultAtts = (DEFAULT_ATTRIBUTE *)MALLOC(parser, type->allocDefaultAtts
                            * sizeof(DEFAULT_ATTRIBUTE));
      if (!type->defaultAtts) {
        type->allocDefaultAtts = 0;
        return 0;
      }
    }
    else {
      DEFAULT_ATTRIBUTE *temp;
      int count = type->allocDefaultAtts * 2;
      temp = (DEFAULT_ATTRIBUTE *)
        REALLOC(parser, type->defaultAtts, (count * sizeof(DEFAULT_ATTRIBUTE)));
      if (temp == NULL)
        return 0;
      type->allocDefaultAtts = count;
      type->defaultAtts = temp;
    }
  }
  att = type->defaultAtts + type->nDefaultAtts;
  att->id = attId;
  att->value = value;
  att->isCdata = isCdata;
  if (!isCdata)
    attId->maybeTokenized = XML_TRUE;
  type->nDefaultAtts += 1;
  return 1;
}

static int
setElementTypePrefix(XML_Parser parser, ELEMENT_TYPE *elementType)
{
  DTD * const dtd = parser->m_dtd;  /* save one level of indirection */
  const XML_Char *name;
  for (name = elementType->name; *name; name++) {
    if (*name == XML_T(ASCII_COLON)) {
      PREFIX *prefix;
      const XML_Char *s;
      for (s = elementType->name; s != name; s++) {
        if (!poolAppendChar(&dtd->pool, *s))
          return 0;
      }
      if (!poolAppendChar(&dtd->pool, XML_T('\0')))
        return 0;
      prefix = (PREFIX *)lookup(parser, &dtd->prefixes, poolStart(&dtd->pool),
                                sizeof(PREFIX));
      if (!prefix)
        return 0;
      if (prefix->name == poolStart(&dtd->pool))
        poolFinish(&dtd->pool);
      else
        poolDiscard(&dtd->pool);
      elementType->prefix = prefix;

    }
  }
  return 1;
}

static ATTRIBUTE_ID *
getAttributeId(XML_Parser parser, const ENCODING *enc,
               const char *start, const char *end)
{
  DTD * const dtd = parser->m_dtd;  /* save one level of indirection */
  ATTRIBUTE_ID *id;
  const XML_Char *name;
  if (!poolAppendChar(&dtd->pool, XML_T('\0')))
    return NULL;
  name = poolStoreString(&dtd->pool, enc, start, end);
  if (!name)
    return NULL;
  /* skip quotation mark - its storage will be re-used (like in name[-1]) */
  ++name;
  id = (ATTRIBUTE_ID *)lookup(parser, &dtd->attributeIds, name, sizeof(ATTRIBUTE_ID));
  if (!id)
    return NULL;
  if (id->name != name)
    poolDiscard(&dtd->pool);
  else {
    poolFinish(&dtd->pool);
    if (!parser->m_ns)
      ;
    else if (name[0] == XML_T(ASCII_x)
        && name[1] == XML_T(ASCII_m)
        && name[2] == XML_T(ASCII_l)
        && name[3] == XML_T(ASCII_n)
        && name[4] == XML_T(ASCII_s)
        && (name[5] == XML_T('\0') || name[5] == XML_T(ASCII_COLON))) {
      if (name[5] == XML_T('\0'))
        id->prefix = &dtd->defaultPrefix;
      else
        id->prefix = (PREFIX *)lookup(parser, &dtd->prefixes, name + 6, sizeof(PREFIX));
      id->xmlns = XML_TRUE;
    }
    else {
      int i;
      for (i = 0; name[i]; i++) {
        /* attributes without prefix are *not* in the default namespace */
        if (name[i] == XML_T(ASCII_COLON)) {
          int j;
          for (j = 0; j < i; j++) {
            if (!poolAppendChar(&dtd->pool, name[j]))
              return NULL;
          }
          if (!poolAppendChar(&dtd->pool, XML_T('\0')))
            return NULL;
          id->prefix = (PREFIX *)lookup(parser, &dtd->prefixes, poolStart(&dtd->pool),
                                        sizeof(PREFIX));
          if (!id->prefix)
            return NULL;
          if (id->prefix->name == poolStart(&dtd->pool))
            poolFinish(&dtd->pool);
          else
            poolDiscard(&dtd->pool);
          break;
        }
      }
    }
  }
  return id;
}

#define CONTEXT_SEP XML_T(ASCII_FF)

static const XML_Char *
getContext(XML_Parser parser)
{
  DTD * const dtd = parser->m_dtd;  /* save one level of indirection */
  HASH_TABLE_ITER iter;
  XML_Bool needSep = XML_FALSE;

  if (dtd->defaultPrefix.binding) {
    int i;
    int len;
    if (!poolAppendChar(&parser->m_tempPool, XML_T(ASCII_EQUALS)))
      return NULL;
    len = dtd->defaultPrefix.binding->uriLen;
    if (parser->m_namespaceSeparator)
      len--;
    for (i = 0; i < len; i++) {
      if (!poolAppendChar(&parser->m_tempPool, dtd->defaultPrefix.binding->uri[i])) {
        /* Because of memory caching, I don't believe this line can be
         * executed.
         *
         * This is part of a loop copying the default prefix binding
         * URI into the parser's temporary string pool.  Previously,
         * that URI was copied into the same string pool, with a
         * terminating NUL character, as part of setContext().  When
         * the pool was cleared, that leaves a block definitely big
         * enough to hold the URI on the free block list of the pool.
         * The URI copy in getContext() therefore cannot run out of
         * memory.
         *
         * If the pool is used between the setContext() and
         * getContext() calls, the worst it can do is leave a bigger
         * block on the front of the free list.  Given that this is
         * all somewhat inobvious and program logic can be changed, we
         * don't delete the line but we do exclude it from the test
         * coverage statistics.
         */
        return NULL; /* LCOV_EXCL_LINE */
      }
    }
    needSep = XML_TRUE;
  }

  hashTableIterInit(&iter, &(dtd->prefixes));
  for (;;) {
    int i;
    int len;
    const XML_Char *s;
    PREFIX *prefix = (PREFIX *)hashTableIterNext(&iter);
    if (!prefix)
      break;
    if (!prefix->binding) {
      /* This test appears to be (justifiable) paranoia.  There does
       * not seem to be a way of injecting a prefix without a binding
       * that doesn't get errored long before this function is called.
       * The test should remain for safety's sake, so we instead
       * exclude the following line from the coverage statistics.
       */
      continue; /* LCOV_EXCL_LINE */
    }
    if (needSep && !poolAppendChar(&parser->m_tempPool, CONTEXT_SEP))
      return NULL;
    for (s = prefix->name; *s; s++)
      if (!poolAppendChar(&parser->m_tempPool, *s))
        return NULL;
    if (!poolAppendChar(&parser->m_tempPool, XML_T(ASCII_EQUALS)))
      return NULL;
    len = prefix->binding->uriLen;
    if (parser->m_namespaceSeparator)
      len--;
    for (i = 0; i < len; i++)
      if (!poolAppendChar(&parser->m_tempPool, prefix->binding->uri[i]))
        return NULL;
    needSep = XML_TRUE;
  }


  hashTableIterInit(&iter, &(dtd->generalEntities));
  for (;;) {
    const XML_Char *s;
    ENTITY *e = (ENTITY *)hashTableIterNext(&iter);
    if (!e)
      break;
    if (!e->open)
      continue;
    if (needSep && !poolAppendChar(&parser->m_tempPool, CONTEXT_SEP))
      return NULL;
    for (s = e->name; *s; s++)
      if (!poolAppendChar(&parser->m_tempPool, *s))
        return 0;
    needSep = XML_TRUE;
  }

  if (!poolAppendChar(&parser->m_tempPool, XML_T('\0')))
    return NULL;
  return parser->m_tempPool.start;
}

static XML_Bool
setContext(XML_Parser parser, const XML_Char *context)
{
  DTD * const dtd = parser->m_dtd;  /* save one level of indirection */
  const XML_Char *s = context;

  while (*context != XML_T('\0')) {
    if (*s == CONTEXT_SEP || *s == XML_T('\0')) {
      ENTITY *e;
      if (!poolAppendChar(&parser->m_tempPool, XML_T('\0')))
        return XML_FALSE;
      e = (ENTITY *)lookup(parser, &dtd->generalEntities, poolStart(&parser->m_tempPool), 0);
      if (e)
        e->open = XML_TRUE;
      if (*s != XML_T('\0'))
        s++;
      context = s;
      poolDiscard(&parser->m_tempPool);
    }
    else if (*s == XML_T(ASCII_EQUALS)) {
      PREFIX *prefix;
      if (poolLength(&parser->m_tempPool) == 0)
        prefix = &dtd->defaultPrefix;
      else {
        if (!poolAppendChar(&parser->m_tempPool, XML_T('\0')))
          return XML_FALSE;
        prefix = (PREFIX *)lookup(parser, &dtd->prefixes, poolStart(&parser->m_tempPool),
                                  sizeof(PREFIX));
        if (!prefix)
          return XML_FALSE;
        if (prefix->name == poolStart(&parser->m_tempPool)) {
          prefix->name = poolCopyString(&dtd->pool, prefix->name);
          if (!prefix->name)
            return XML_FALSE;
        }
        poolDiscard(&parser->m_tempPool);
      }
      for (context = s + 1;
           *context != CONTEXT_SEP && *context != XML_T('\0');
           context++)
        if (!poolAppendChar(&parser->m_tempPool, *context))
          return XML_FALSE;
      if (!poolAppendChar(&parser->m_tempPool, XML_T('\0')))
        return XML_FALSE;
      if (addBinding(parser, prefix, NULL, poolStart(&parser->m_tempPool),
                     &parser->m_inheritedBindings) != XML_ERROR_NONE)
        return XML_FALSE;
      poolDiscard(&parser->m_tempPool);
      if (*context != XML_T('\0'))
        ++context;
      s = context;
    }
    else {
      if (!poolAppendChar(&parser->m_tempPool, *s))
        return XML_FALSE;
      s++;
    }
  }
  return XML_TRUE;
}

static void FASTCALL
normalizePublicId(XML_Char *publicId)
{
  XML_Char *p = publicId;
  XML_Char *s;
  for (s = publicId; *s; s++) {
    switch (*s) {
    case 0x20:
    case 0xD:
    case 0xA:
      if (p != publicId && p[-1] != 0x20)
        *p++ = 0x20;
      break;
    default:
      *p++ = *s;
    }
  }
  if (p != publicId && p[-1] == 0x20)
    --p;
  *p = XML_T('\0');
}

static DTD *
dtdCreate(const XML_Memory_Handling_Suite *ms)
{
  DTD *p = (DTD *)ms->malloc_fcn(sizeof(DTD));
  if (p == NULL)
    return p;
  poolInit(&(p->pool), ms);
  poolInit(&(p->entityValuePool), ms);
  hashTableInit(&(p->generalEntities), ms);
  hashTableInit(&(p->elementTypes), ms);
  hashTableInit(&(p->attributeIds), ms);
  hashTableInit(&(p->prefixes), ms);
#ifdef XML_DTD
  p->paramEntityRead = XML_FALSE;
  hashTableInit(&(p->paramEntities), ms);
#endif /* XML_DTD */
  p->defaultPrefix.name = NULL;
  p->defaultPrefix.binding = NULL;

  p->in_eldecl = XML_FALSE;
  p->scaffIndex = NULL;
  p->scaffold = NULL;
  p->scaffLevel = 0;
  p->scaffSize = 0;
  p->scaffCount = 0;
  p->contentStringLen = 0;

  p->keepProcessing = XML_TRUE;
  p->hasParamEntityRefs = XML_FALSE;
  p->standalone = XML_FALSE;
  return p;
}

static void
dtdReset(DTD *p, const XML_Memory_Handling_Suite *ms)
{
  HASH_TABLE_ITER iter;
  hashTableIterInit(&iter, &(p->elementTypes));
  for (;;) {
    ELEMENT_TYPE *e = (ELEMENT_TYPE *)hashTableIterNext(&iter);
    if (!e)
      break;
    if (e->allocDefaultAtts != 0)
      ms->free_fcn(e->defaultAtts);
  }
  hashTableClear(&(p->generalEntities));
#ifdef XML_DTD
  p->paramEntityRead = XML_FALSE;
  hashTableClear(&(p->paramEntities));
#endif /* XML_DTD */
  hashTableClear(&(p->elementTypes));
  hashTableClear(&(p->attributeIds));
  hashTableClear(&(p->prefixes));
  poolClear(&(p->pool));
  poolClear(&(p->entityValuePool));
  p->defaultPrefix.name = NULL;
  p->defaultPrefix.binding = NULL;

  p->in_eldecl = XML_FALSE;

  ms->free_fcn(p->scaffIndex);
  p->scaffIndex = NULL;
  ms->free_fcn(p->scaffold);
  p->scaffold = NULL;

  p->scaffLevel = 0;
  p->scaffSize = 0;
  p->scaffCount = 0;
  p->contentStringLen = 0;

  p->keepProcessing = XML_TRUE;
  p->hasParamEntityRefs = XML_FALSE;
  p->standalone = XML_FALSE;
}

static void
dtdDestroy(DTD *p, XML_Bool isDocEntity, const XML_Memory_Handling_Suite *ms)
{
  HASH_TABLE_ITER iter;
  hashTableIterInit(&iter, &(p->elementTypes));
  for (;;) {
    ELEMENT_TYPE *e = (ELEMENT_TYPE *)hashTableIterNext(&iter);
    if (!e)
      break;
    if (e->allocDefaultAtts != 0)
      ms->free_fcn(e->defaultAtts);
  }
  hashTableDestroy(&(p->generalEntities));
#ifdef XML_DTD
  hashTableDestroy(&(p->paramEntities));
#endif /* XML_DTD */
  hashTableDestroy(&(p->elementTypes));
  hashTableDestroy(&(p->attributeIds));
  hashTableDestroy(&(p->prefixes));
  poolDestroy(&(p->pool));
  poolDestroy(&(p->entityValuePool));
  if (isDocEntity) {
    ms->free_fcn(p->scaffIndex);
    ms->free_fcn(p->scaffold);
  }
  ms->free_fcn(p);
}

/* Do a deep copy of the DTD. Return 0 for out of memory, non-zero otherwise.
   The new DTD has already been initialized.
*/
static int
dtdCopy(XML_Parser oldParser, DTD *newDtd, const DTD *oldDtd, const XML_Memory_Handling_Suite *ms)
{
  HASH_TABLE_ITER iter;

  /* Copy the prefix table. */

  hashTableIterInit(&iter, &(oldDtd->prefixes));
  for (;;) {
    const XML_Char *name;
    const PREFIX *oldP = (PREFIX *)hashTableIterNext(&iter);
    if (!oldP)
      break;
    name = poolCopyString(&(newDtd->pool), oldP->name);
    if (!name)
      return 0;
    if (!lookup(oldParser, &(newDtd->prefixes), name, sizeof(PREFIX)))
      return 0;
  }

  hashTableIterInit(&iter, &(oldDtd->attributeIds));

  /* Copy the attribute id table. */

  for (;;) {
    ATTRIBUTE_ID *newA;
    const XML_Char *name;
    const ATTRIBUTE_ID *oldA = (ATTRIBUTE_ID *)hashTableIterNext(&iter);

    if (!oldA)
      break;
    /* Remember to allocate the scratch byte before the name. */
    if (!poolAppendChar(&(newDtd->pool), XML_T('\0')))
      return 0;
    name = poolCopyString(&(newDtd->pool), oldA->name);
    if (!name)
      return 0;
    ++name;
    newA = (ATTRIBUTE_ID *)lookup(oldParser, &(newDtd->attributeIds), name,
                                  sizeof(ATTRIBUTE_ID));
    if (!newA)
      return 0;
    newA->maybeTokenized = oldA->maybeTokenized;
    if (oldA->prefix) {
      newA->xmlns = oldA->xmlns;
      if (oldA->prefix == &oldDtd->defaultPrefix)
        newA->prefix = &newDtd->defaultPrefix;
      else
        newA->prefix = (PREFIX *)lookup(oldParser, &(newDtd->prefixes),
                                        oldA->prefix->name, 0);
    }
  }

  /* Copy the element type table. */

  hashTableIterInit(&iter, &(oldDtd->elementTypes));

  for (;;) {
    int i;
    ELEMENT_TYPE *newE;
    const XML_Char *name;
    const ELEMENT_TYPE *oldE = (ELEMENT_TYPE *)hashTableIterNext(&iter);
    if (!oldE)
      break;
    name = poolCopyString(&(newDtd->pool), oldE->name);
    if (!name)
      return 0;
    newE = (ELEMENT_TYPE *)lookup(oldParser, &(newDtd->elementTypes), name,
                                  sizeof(ELEMENT_TYPE));
    if (!newE)
      return 0;
    if (oldE->nDefaultAtts) {
      newE->defaultAtts = (DEFAULT_ATTRIBUTE *)
          ms->malloc_fcn(oldE->nDefaultAtts * sizeof(DEFAULT_ATTRIBUTE));
      if (!newE->defaultAtts) {
        return 0;
      }
    }
    if (oldE->idAtt)
      newE->idAtt = (ATTRIBUTE_ID *)
          lookup(oldParser, &(newDtd->attributeIds), oldE->idAtt->name, 0);
    newE->allocDefaultAtts = newE->nDefaultAtts = oldE->nDefaultAtts;
    if (oldE->prefix)
      newE->prefix = (PREFIX *)lookup(oldParser, &(newDtd->prefixes),
                                      oldE->prefix->name, 0);
    for (i = 0; i < newE->nDefaultAtts; i++) {
      newE->defaultAtts[i].id = (ATTRIBUTE_ID *)
          lookup(oldParser, &(newDtd->attributeIds), oldE->defaultAtts[i].id->name, 0);
      newE->defaultAtts[i].isCdata = oldE->defaultAtts[i].isCdata;
      if (oldE->defaultAtts[i].value) {
        newE->defaultAtts[i].value
            = poolCopyString(&(newDtd->pool), oldE->defaultAtts[i].value);
        if (!newE->defaultAtts[i].value)
          return 0;
      }
      else
        newE->defaultAtts[i].value = NULL;
    }
  }

  /* Copy the entity tables. */
  if (!copyEntityTable(oldParser,
                       &(newDtd->generalEntities),
                       &(newDtd->pool),
                       &(oldDtd->generalEntities)))
      return 0;

#ifdef XML_DTD
  if (!copyEntityTable(oldParser,
                       &(newDtd->paramEntities),
                       &(newDtd->pool),
                       &(oldDtd->paramEntities)))
      return 0;
  newDtd->paramEntityRead = oldDtd->paramEntityRead;
#endif /* XML_DTD */

  newDtd->keepProcessing = oldDtd->keepProcessing;
  newDtd->hasParamEntityRefs = oldDtd->hasParamEntityRefs;
  newDtd->standalone = oldDtd->standalone;

  /* Don't want deep copying for scaffolding */
  newDtd->in_eldecl = oldDtd->in_eldecl;
  newDtd->scaffold = oldDtd->scaffold;
  newDtd->contentStringLen = oldDtd->contentStringLen;
  newDtd->scaffSize = oldDtd->scaffSize;
  newDtd->scaffLevel = oldDtd->scaffLevel;
  newDtd->scaffIndex = oldDtd->scaffIndex;

  return 1;
}  /* End dtdCopy */

static int
copyEntityTable(XML_Parser oldParser,
                HASH_TABLE *newTable,
                STRING_POOL *newPool,
                const HASH_TABLE *oldTable)
{
  HASH_TABLE_ITER iter;
  const XML_Char *cachedOldBase = NULL;
  const XML_Char *cachedNewBase = NULL;

  hashTableIterInit(&iter, oldTable);

  for (;;) {
    ENTITY *newE;
    const XML_Char *name;
    const ENTITY *oldE = (ENTITY *)hashTableIterNext(&iter);
    if (!oldE)
      break;
    name = poolCopyString(newPool, oldE->name);
    if (!name)
      return 0;
    newE = (ENTITY *)lookup(oldParser, newTable, name, sizeof(ENTITY));
    if (!newE)
      return 0;
    if (oldE->systemId) {
      const XML_Char *tem = poolCopyString(newPool, oldE->systemId);
      if (!tem)
        return 0;
      newE->systemId = tem;
      if (oldE->base) {
        if (oldE->base == cachedOldBase)
          newE->base = cachedNewBase;
        else {
          cachedOldBase = oldE->base;
          tem = poolCopyString(newPool, cachedOldBase);
          if (!tem)
            return 0;
          cachedNewBase = newE->base = tem;
        }
      }
      if (oldE->publicId) {
        tem = poolCopyString(newPool, oldE->publicId);
        if (!tem)
          return 0;
        newE->publicId = tem;
      }
    }
    else {
      const XML_Char *tem = poolCopyStringN(newPool, oldE->textPtr,
                                            oldE->textLen);
      if (!tem)
        return 0;
      newE->textPtr = tem;
      newE->textLen = oldE->textLen;
    }
    if (oldE->notation) {
      const XML_Char *tem = poolCopyString(newPool, oldE->notation);
      if (!tem)
        return 0;
      newE->notation = tem;
    }
    newE->is_param = oldE->is_param;
    newE->is_internal = oldE->is_internal;
  }
  return 1;
}

#define INIT_POWER 6

static XML_Bool FASTCALL
keyeq(KEY s1, KEY s2)
{
  for (; *s1 == *s2; s1++, s2++)
    if (*s1 == 0)
      return XML_TRUE;
  return XML_FALSE;
}

static size_t
keylen(KEY s)
{
  size_t len = 0;
  for (; *s; s++, len++);
  return len;
}

static void
copy_salt_to_sipkey(XML_Parser parser, struct sipkey * key)
{
  key->k[0] = 0;
  key->k[1] = get_hash_secret_salt(parser);
}

static unsigned long FASTCALL
hash(XML_Parser parser, KEY s)
{
  struct siphash state;
  struct sipkey key;
  (void)sip24_valid;
  copy_salt_to_sipkey(parser, &key);
  sip24_init(&state, &key);
  sip24_update(&state, s, keylen(s) * sizeof(XML_Char));
  return (unsigned long)sip24_final(&state);
}

static NAMED *
lookup(XML_Parser parser, HASH_TABLE *table, KEY name, size_t createSize)
{
  size_t i;
  if (table->size == 0) {
    size_t tsize;
    if (!createSize)
      return NULL;
    table->power = INIT_POWER;
    /* table->size is a power of 2 */
    table->size = (size_t)1 << INIT_POWER;
    tsize = table->size * sizeof(NAMED *);
    table->v = (NAMED **)table->mem->malloc_fcn(tsize);
    if (!table->v) {
      table->size = 0;
      return NULL;
    }
    memset(table->v, 0, tsize);
    i = hash(parser, name) & ((unsigned long)table->size - 1);
  }
  else {
    unsigned long h = hash(parser, name);
    unsigned long mask = (unsigned long)table->size - 1;
    unsigned char step = 0;
    i = h & mask;
    while (table->v[i]) {
      if (keyeq(name, table->v[i]->name))
        return table->v[i];
      if (!step)
        step = PROBE_STEP(h, mask, table->power);
      i < step ? (i += table->size - step) : (i -= step);
    }
    if (!createSize)
      return NULL;

    /* check for overflow (table is half full) */
    if (table->used >> (table->power - 1)) {
      unsigned char newPower = table->power + 1;
      size_t newSize = (size_t)1 << newPower;
      unsigned long newMask = (unsigned long)newSize - 1;
      size_t tsize = newSize * sizeof(NAMED *);
      NAMED **newV = (NAMED **)table->mem->malloc_fcn(tsize);
      if (!newV)
        return NULL;
      memset(newV, 0, tsize);
      for (i = 0; i < table->size; i++)
        if (table->v[i]) {
          unsigned long newHash = hash(parser, table->v[i]->name);
          size_t j = newHash & newMask;
          step = 0;
          while (newV[j]) {
            if (!step)
              step = PROBE_STEP(newHash, newMask, newPower);
            j < step ? (j += newSize - step) : (j -= step);
          }
          newV[j] = table->v[i];
        }
      table->mem->free_fcn(table->v);
      table->v = newV;
      table->power = newPower;
      table->size = newSize;
      i = h & newMask;
      step = 0;
      while (table->v[i]) {
        if (!step)
          step = PROBE_STEP(h, newMask, newPower);
        i < step ? (i += newSize - step) : (i -= step);
      }
    }
  }
  table->v[i] = (NAMED *)table->mem->malloc_fcn(createSize);
  if (!table->v[i])
    return NULL;
  memset(table->v[i], 0, createSize);
  table->v[i]->name = name;
  (table->used)++;
  return table->v[i];
}

static void FASTCALL
hashTableClear(HASH_TABLE *table)
{
  size_t i;
  for (i = 0; i < table->size; i++) {
    table->mem->free_fcn(table->v[i]);
    table->v[i] = NULL;
  }
  table->used = 0;
}

static void FASTCALL
hashTableDestroy(HASH_TABLE *table)
{
  size_t i;
  for (i = 0; i < table->size; i++)
    table->mem->free_fcn(table->v[i]);
  table->mem->free_fcn(table->v);
}

static void FASTCALL
hashTableInit(HASH_TABLE *p, const XML_Memory_Handling_Suite *ms)
{
  p->power = 0;
  p->size = 0;
  p->used = 0;
  p->v = NULL;
  p->mem = ms;
}

static void FASTCALL
hashTableIterInit(HASH_TABLE_ITER *iter, const HASH_TABLE *table)
{
  iter->p = table->v;
  iter->end = iter->p + table->size;
}

static NAMED * FASTCALL
hashTableIterNext(HASH_TABLE_ITER *iter)
{
  while (iter->p != iter->end) {
    NAMED *tem = *(iter->p)++;
    if (tem)
      return tem;
  }
  return NULL;
}

static void FASTCALL
poolInit(STRING_POOL *pool, const XML_Memory_Handling_Suite *ms)
{
  pool->blocks = NULL;
  pool->freeBlocks = NULL;
  pool->start = NULL;
  pool->ptr = NULL;
  pool->end = NULL;
  pool->mem = ms;
}

static void FASTCALL
poolClear(STRING_POOL *pool)
{
  if (!pool->freeBlocks)
    pool->freeBlocks = pool->blocks;
  else {
    BLOCK *p = pool->blocks;
    while (p) {
      BLOCK *tem = p->next;
      p->next = pool->freeBlocks;
      pool->freeBlocks = p;
      p = tem;
    }
  }
  pool->blocks = NULL;
  pool->start = NULL;
  pool->ptr = NULL;
  pool->end = NULL;
}

static void FASTCALL
poolDestroy(STRING_POOL *pool)
{
  BLOCK *p = pool->blocks;
  while (p) {
    BLOCK *tem = p->next;
    pool->mem->free_fcn(p);
    p = tem;
  }
  p = pool->freeBlocks;
  while (p) {
    BLOCK *tem = p->next;
    pool->mem->free_fcn(p);
    p = tem;
  }
}

static XML_Char *
poolAppend(STRING_POOL *pool, const ENCODING *enc,
           const char *ptr, const char *end)
{
  if (!pool->ptr && !poolGrow(pool))
    return NULL;
  for (;;) {
    const enum XML_Convert_Result convert_res = XmlConvert(enc, &ptr, end, (ICHAR **)&(pool->ptr), (ICHAR *)pool->end);
    if ((convert_res == XML_CONVERT_COMPLETED) || (convert_res == XML_CONVERT_INPUT_INCOMPLETE))
      break;
    if (!poolGrow(pool))
      return NULL;
  }
  return pool->start;
}

static const XML_Char * FASTCALL
poolCopyString(STRING_POOL *pool, const XML_Char *s)
{
  do {
    if (!poolAppendChar(pool, *s))
      return NULL;
  } while (*s++);
  s = pool->start;
  poolFinish(pool);
  return s;
}

static const XML_Char *
poolCopyStringN(STRING_POOL *pool, const XML_Char *s, int n)
{
  if (!pool->ptr && !poolGrow(pool)) {
    /* The following line is unreachable given the current usage of
     * poolCopyStringN().  Currently it is called from exactly one
     * place to copy the text of a simple general entity.  By that
     * point, the name of the entity is already stored in the pool, so
     * pool->ptr cannot be NULL.
     *
     * If poolCopyStringN() is used elsewhere as it well might be,
     * this line may well become executable again.  Regardless, this
     * sort of check shouldn't be removed lightly, so we just exclude
     * it from the coverage statistics.
     */
    return NULL; /* LCOV_EXCL_LINE */
  }
  for (; n > 0; --n, s++) {
    if (!poolAppendChar(pool, *s))
      return NULL;
  }
  s = pool->start;
  poolFinish(pool);
  return s;
}

static const XML_Char * FASTCALL
poolAppendString(STRING_POOL *pool, const XML_Char *s)
{
  while (*s) {
    if (!poolAppendChar(pool, *s))
      return NULL;
    s++;
  }
  return pool->start;
}

static XML_Char *
poolStoreString(STRING_POOL *pool, const ENCODING *enc,
                const char *ptr, const char *end)
{
  if (!poolAppend(pool, enc, ptr, end))
    return NULL;
  if (pool->ptr == pool->end && !poolGrow(pool))
    return NULL;
  *(pool->ptr)++ = 0;
  return pool->start;
}

static size_t
poolBytesToAllocateFor(int blockSize)
{
  /* Unprotected math would be:
  ** return offsetof(BLOCK, s) + blockSize * sizeof(XML_Char);
  **
  ** Detect overflow, avoiding _signed_ overflow undefined behavior
  ** For a + b * c we check b * c in isolation first, so that addition of a
  ** on top has no chance of making us accept a small non-negative number
  */
  const size_t stretch = sizeof(XML_Char);  /* can be 4 bytes */

  if (blockSize <= 0)
    return 0;

  if (blockSize > (int)(INT_MAX / stretch))
    return 0;

  {
    const int stretchedBlockSize = blockSize * (int)stretch;
    const int bytesToAllocate = (int)(
        offsetof(BLOCK, s) + (unsigned)stretchedBlockSize);
    if (bytesToAllocate < 0)
      return 0;

    return (size_t)bytesToAllocate;
  }
}

static XML_Bool FASTCALL
poolGrow(STRING_POOL *pool)
{
  if (pool->freeBlocks) {
    if (pool->start == 0) {
      pool->blocks = pool->freeBlocks;
      pool->freeBlocks = pool->freeBlocks->next;
      pool->blocks->next = NULL;
      pool->start = pool->blocks->s;
      pool->end = pool->start + pool->blocks->size;
      pool->ptr = pool->start;
      return XML_TRUE;
    }
    if (pool->end - pool->start < pool->freeBlocks->size) {
      BLOCK *tem = pool->freeBlocks->next;
      pool->freeBlocks->next = pool->blocks;
      pool->blocks = pool->freeBlocks;
      pool->freeBlocks = tem;
      memcpy(pool->blocks->s, pool->start,
             (pool->end - pool->start) * sizeof(XML_Char));
      pool->ptr = pool->blocks->s + (pool->ptr - pool->start);
      pool->start = pool->blocks->s;
      pool->end = pool->start + pool->blocks->size;
      return XML_TRUE;
    }
  }
  if (pool->blocks && pool->start == pool->blocks->s) {
    BLOCK *temp;
    int blockSize = (int)((unsigned)(pool->end - pool->start)*2U);
    size_t bytesToAllocate;

    /* NOTE: Needs to be calculated prior to calling `realloc`
             to avoid dangling pointers: */
    const ptrdiff_t offsetInsideBlock = pool->ptr - pool->start;

    if (blockSize < 0) {
      /* This condition traps a situation where either more than
       * INT_MAX/2 bytes have already been allocated.  This isn't
       * readily testable, since it is unlikely that an average
       * machine will have that much memory, so we exclude it from the
       * coverage statistics.
       */
      return XML_FALSE; /* LCOV_EXCL_LINE */
    }

    bytesToAllocate = poolBytesToAllocateFor(blockSize);
    if (bytesToAllocate == 0)
      return XML_FALSE;

    temp = (BLOCK *)
      pool->mem->realloc_fcn(pool->blocks, (unsigned)bytesToAllocate);
    if (temp == NULL)
      return XML_FALSE;
    pool->blocks = temp;
    pool->blocks->size = blockSize;
    pool->ptr = pool->blocks->s + offsetInsideBlock;
    pool->start = pool->blocks->s;
    pool->end = pool->start + blockSize;
  }
  else {
    BLOCK *tem;
    int blockSize = (int)(pool->end - pool->start);
    size_t bytesToAllocate;

    if (blockSize < 0) {
      /* This condition traps a situation where either more than
       * INT_MAX bytes have already been allocated (which is prevented
       * by various pieces of program logic, not least this one, never
       * mind the unlikelihood of actually having that much memory) or
       * the pool control fields have been corrupted (which could
       * conceivably happen in an extremely buggy user handler
       * function).  Either way it isn't readily testable, so we
       * exclude it from the coverage statistics.
       */
      return XML_FALSE;  /* LCOV_EXCL_LINE */
    }

    if (blockSize < INIT_BLOCK_SIZE)
      blockSize = INIT_BLOCK_SIZE;
    else {
      /* Detect overflow, avoiding _signed_ overflow undefined behavior */
      if ((int)((unsigned)blockSize * 2U) < 0) {
        return XML_FALSE;
      }
      blockSize *= 2;
    }

    bytesToAllocate = poolBytesToAllocateFor(blockSize);
    if (bytesToAllocate == 0)
      return XML_FALSE;

    tem = (BLOCK *)pool->mem->malloc_fcn(bytesToAllocate);
    if (!tem)
      return XML_FALSE;
    tem->size = blockSize;
    tem->next = pool->blocks;
    pool->blocks = tem;
    if (pool->ptr != pool->start)
      memcpy(tem->s, pool->start,
             (pool->ptr - pool->start) * sizeof(XML_Char));
    pool->ptr = tem->s + (pool->ptr - pool->start);
    pool->start = tem->s;
    pool->end = tem->s + blockSize;
  }
  return XML_TRUE;
}

static int FASTCALL
nextScaffoldPart(XML_Parser parser)
{
  DTD * const dtd = parser->m_dtd;  /* save one level of indirection */
  CONTENT_SCAFFOLD * me;
  int next;

  if (!dtd->scaffIndex) {
    dtd->scaffIndex = (int *)MALLOC(parser, parser->m_groupSize * sizeof(int));
    if (!dtd->scaffIndex)
      return -1;
    dtd->scaffIndex[0] = 0;
  }

  if (dtd->scaffCount >= dtd->scaffSize) {
    CONTENT_SCAFFOLD *temp;
    if (dtd->scaffold) {
      temp = (CONTENT_SCAFFOLD *)
        REALLOC(parser, dtd->scaffold, dtd->scaffSize * 2 * sizeof(CONTENT_SCAFFOLD));
      if (temp == NULL)
        return -1;
      dtd->scaffSize *= 2;
    }
    else {
      temp = (CONTENT_SCAFFOLD *)MALLOC(parser, INIT_SCAFFOLD_ELEMENTS
                                        * sizeof(CONTENT_SCAFFOLD));
      if (temp == NULL)
        return -1;
      dtd->scaffSize = INIT_SCAFFOLD_ELEMENTS;
    }
    dtd->scaffold = temp;
  }
  next = dtd->scaffCount++;
  me = &dtd->scaffold[next];
  if (dtd->scaffLevel) {
    CONTENT_SCAFFOLD *parent = &dtd->scaffold[dtd->scaffIndex[dtd->scaffLevel-1]];
    if (parent->lastchild) {
      dtd->scaffold[parent->lastchild].nextsib = next;
    }
    if (!parent->childcnt)
      parent->firstchild = next;
    parent->lastchild = next;
    parent->childcnt++;
  }
  me->firstchild = me->lastchild = me->childcnt = me->nextsib = 0;
  return next;
}

static void
build_node(XML_Parser parser,
           int src_node,
           XML_Content *dest,
           XML_Content **contpos,
           XML_Char **strpos)
{
  DTD * const dtd = parser->m_dtd;  /* save one level of indirection */
  dest->type = dtd->scaffold[src_node].type;
  dest->quant = dtd->scaffold[src_node].quant;
  if (dest->type == XML_CTYPE_NAME) {
    const XML_Char *src;
    dest->name = *strpos;
    src = dtd->scaffold[src_node].name;
    for (;;) {
      *(*strpos)++ = *src;
      if (!*src)
        break;
      src++;
    }
    dest->numchildren = 0;
    dest->children = NULL;
  }
  else {
    unsigned int i;
    int cn;
    dest->numchildren = dtd->scaffold[src_node].childcnt;
    dest->children = *contpos;
    *contpos += dest->numchildren;
    for (i = 0, cn = dtd->scaffold[src_node].firstchild;
         i < dest->numchildren;
         i++, cn = dtd->scaffold[cn].nextsib) {
      build_node(parser, cn, &(dest->children[i]), contpos, strpos);
    }
    dest->name = NULL;
  }
}

static XML_Content *
build_model (XML_Parser parser)
{
  DTD * const dtd = parser->m_dtd;  /* save one level of indirection */
  XML_Content *ret;
  XML_Content *cpos;
  XML_Char * str;
  int allocsize = (dtd->scaffCount * sizeof(XML_Content)
                   + (dtd->contentStringLen * sizeof(XML_Char)));

  ret = (XML_Content *)MALLOC(parser, allocsize);
  if (!ret)
    return NULL;

  str =  (XML_Char *) (&ret[dtd->scaffCount]);
  cpos = &ret[1];

  build_node(parser, 0, ret, &cpos, &str);
  return ret;
}

static ELEMENT_TYPE *
getElementType(XML_Parser parser,
               const ENCODING *enc,
               const char *ptr,
               const char *end)
{
  DTD * const dtd = parser->m_dtd;  /* save one level of indirection */
  const XML_Char *name = poolStoreString(&dtd->pool, enc, ptr, end);
  ELEMENT_TYPE *ret;

  if (!name)
    return NULL;
  ret = (ELEMENT_TYPE *) lookup(parser, &dtd->elementTypes, name, sizeof(ELEMENT_TYPE));
  if (!ret)
    return NULL;
  if (ret->name != name)
    poolDiscard(&dtd->pool);
  else {
    poolFinish(&dtd->pool);
    if (!setElementTypePrefix(parser, ret))
      return NULL;
  }
  return ret;
}

static XML_Char *
copyString(const XML_Char *s,
           const XML_Memory_Handling_Suite *memsuite)
{
    int charsRequired = 0;
    XML_Char *result;

    /* First determine how long the string is */
    while (s[charsRequired] != 0) {
      charsRequired++;
    }
    /* Include the terminator */
    charsRequired++;

    /* Now allocate space for the copy */
    result = memsuite->malloc_fcn(charsRequired * sizeof(XML_Char));
    if (result == NULL)
        return NULL;
    /* Copy the original into place */
    memcpy(result, s, charsRequired * sizeof(XML_Char));
    return result;
}

#include "apr.h"
#include "apr_strings.h"

#define APR_WANT_STDIO          /* for sprintf() */
#define APR_WANT_STRFUNC
#include "apr_want.h"

#include "apr_xml.h"

#include "apu_config.h"

#if defined(HAVE_XMLPARSE_XMLPARSE_H)
#include <xmlparse/xmlparse.h>
#elif defined(HAVE_XMLTOK_XMLPARSE_H)
#include <xmltok/xmlparse.h>
#elif defined(HAVE_XML_XMLPARSE_H)
#include <xml/xmlparse.h>
#else
#include <expat.h>
#endif

#define DEBUG_CR "\r\n"

static const char APR_KW_xmlns[] = { 0x78, 0x6D, 0x6C, 0x6E, 0x73, '\0' };
static const char APR_KW_xmlns_lang[] = { 0x78, 0x6D, 0x6C, 0x3A, 0x6C, 0x61, 0x6E, 0x67, '\0' };
static const char APR_KW_DAV[] = { 0x44, 0x41, 0x56, 0x3A, '\0' };

/* errors related to namespace processing */
#define APR_XML_NS_ERROR_UNKNOWN_PREFIX (-1000)
#define APR_XML_NS_ERROR_INVALID_DECL (-1001)

/* test for a namespace prefix that begins with [Xx][Mm][Ll] */
#define APR_XML_NS_IS_RESERVED(name) \
	( (name[0] == 0x58 || name[0] == 0x78) && \
	  (name[1] == 0x4D || name[1] == 0x6D) && \
	  (name[2] == 0x4C || name[2] == 0x6C) )


/* the real (internal) definition of the parser context */
struct apr_xml_parser {
    apr_xml_doc *doc;		/* the doc we're parsing */
    apr_pool_t *p;		/* the pool we allocate from */
    apr_xml_elem *cur_elem;	/* current element */

    int error;			/* an error has occurred */
#define APR_XML_ERROR_EXPAT             1
#define APR_XML_ERROR_PARSE_DONE        2
/* also: public APR_XML_NS_ERROR_* values (if any) */

    XML_Parser xp;              /* the actual (Expat) XML parser */
    enum XML_Error xp_err;      /* stored Expat error code */
};

/* struct for scoping namespace declarations */
typedef struct apr_xml_ns_scope {
    const char *prefix;		/* prefix used for this ns */
    int ns;			/* index into namespace table */
    int emptyURI;		/* the namespace URI is the empty string */
    struct apr_xml_ns_scope *next;	/* next scoped namespace */
} apr_xml_ns_scope;


/* return namespace table index for a given prefix */
static int find_prefix(apr_xml_parser *parser, const char *prefix)
{
    apr_xml_elem *elem = parser->cur_elem;

    /*
    ** Walk up the tree, looking for a namespace scope that defines this
    ** prefix.
    */
    for (; elem; elem = elem->parent) {
	apr_xml_ns_scope *ns_scope;

	for (ns_scope = elem->ns_scope; ns_scope; ns_scope = ns_scope->next) {
	    if (strcmp(prefix, ns_scope->prefix) == 0) {
		if (ns_scope->emptyURI) {
		    /*
		    ** It is possible to set the default namespace to an
		    ** empty URI string; this resets the default namespace
		    ** to mean "no namespace." We just found the prefix
		    ** refers to an empty URI, so return "no namespace."
		    */
		    return APR_XML_NS_NONE;
		}

		return ns_scope->ns;
	    }
	}
    }

    /*
     * If the prefix is empty (""), this means that a prefix was not
     * specified in the element/attribute. The search that was performed
     * just above did not locate a default namespace URI (which is stored
     * into ns_scope with an empty prefix). This means the element/attribute
     * has "no namespace". We have a reserved value for this.
     */
    if (*prefix == '\0') {
	return APR_XML_NS_NONE;
    }

    /* not found */
    return APR_XML_NS_ERROR_UNKNOWN_PREFIX;
}

/* return original prefix given ns index */
static const char * find_prefix_name(const apr_xml_elem *elem, int ns, int parent)
{
    /*
    ** Walk up the tree, looking for a namespace scope that defines this
    ** prefix.
    */
    for (; elem; elem = parent ? elem->parent : NULL) {
	apr_xml_ns_scope *ns_scope = elem->ns_scope;

	for (; ns_scope; ns_scope = ns_scope->next) {
	    if (ns_scope->ns == ns)
		return ns_scope->prefix;
	}
    }
    /* not found */
    return "";
}


static void start_handler(void *userdata, const char *name, const char **attrs)
{
    apr_xml_parser *parser = userdata;
    apr_xml_elem *elem;
    apr_xml_attr *attr;
    apr_xml_attr *prev;
    char *colon;
    const char *quoted;
    char *elem_name;

    /* punt once we find an error */
    if (parser->error)
	return;

    elem = apr_pcalloc(parser->p, sizeof(*elem));

    /* prep the element */
    elem->name = elem_name = apr_pstrdup(parser->p, name);

    /* fill in the attributes (note: ends up in reverse order) */
    while (*attrs) {
	attr = apr_palloc(parser->p, sizeof(*attr));
	attr->name = apr_pstrdup(parser->p, *attrs++);
	attr->value = apr_pstrdup(parser->p, *attrs++);
	attr->next = elem->attr;
	elem->attr = attr;
    }

    /* hook the element into the tree */
    if (parser->cur_elem == NULL) {
	/* no current element; this also becomes the root */
	parser->cur_elem = parser->doc->root = elem;
    }
    else {
	/* this element appeared within the current elem */
	elem->parent = parser->cur_elem;

	/* set up the child/sibling links */
	if (elem->parent->last_child == NULL) {
	    /* no first child either */
	    elem->parent->first_child = elem->parent->last_child = elem;
	}
	else {
	    /* hook onto the end of the parent's children */
	    elem->parent->last_child->next = elem;
	    elem->parent->last_child = elem;
	}

	/* this element is now the current element */
	parser->cur_elem = elem;
    }

    /* scan the attributes for namespace declarations */
    for (prev = NULL, attr = elem->attr;
	 attr;
	 attr = attr->next) {
	if (strncmp(attr->name, APR_KW_xmlns, 5) == 0) {
	    const char *prefix = &attr->name[5];
	    apr_xml_ns_scope *ns_scope;

	    /* test for xmlns:foo= form and xmlns= form */
	    if (*prefix == 0x3A) {
                /* a namespace prefix declaration must have a
                   non-empty value. */
                if (attr->value[0] == '\0') {
                    parser->error = APR_XML_NS_ERROR_INVALID_DECL;
                    return;
                }
		++prefix;
            }
	    else if (*prefix != '\0') {
		/* advance "prev" since "attr" is still present */
		prev = attr;
		continue;
	    }

	    /* quote the URI before we ever start working with it */
	    quoted = apr_xml_quote_string(parser->p, attr->value, 1);

	    /* build and insert the new scope */
	    ns_scope = apr_pcalloc(parser->p, sizeof(*ns_scope));
	    ns_scope->prefix = prefix;
	    ns_scope->ns = apr_xml_insert_uri(parser->doc->namespaces, quoted);
	    ns_scope->emptyURI = *quoted == '\0';
	    ns_scope->next = elem->ns_scope;
	    elem->ns_scope = ns_scope;

	    /* remove this attribute from the element */
	    if (prev == NULL)
		elem->attr = attr->next;
	    else
		prev->next = attr->next;

	    /* Note: prev will not be advanced since we just removed "attr" */
	}
	else if (strcmp(attr->name, APR_KW_xmlns_lang) == 0) {
	    /* save away the language (in quoted form) */
	    elem->lang = apr_xml_quote_string(parser->p, attr->value, 1);

	    /* remove this attribute from the element */
	    if (prev == NULL)
		elem->attr = attr->next;
	    else
		prev->next = attr->next;

	    /* Note: prev will not be advanced since we just removed "attr" */
	}
	else {
	    /* advance "prev" since "attr" is still present */
	    prev = attr;
	}
    }

    /*
    ** If an xml:lang attribute didn't exist (lang==NULL), then copy the
    ** language from the parent element (if present).
    **
    ** NOTE: elem_size() *depends* upon this pointer equality.
    */
    if (elem->lang == NULL && elem->parent != NULL)
	elem->lang = elem->parent->lang;

    /* adjust the element's namespace */
    colon = strchr(elem_name, 0x3A);
    if (colon == NULL) {
	/*
	 * The element is using the default namespace, which will always
	 * be found. Either it will be "no namespace", or a default
	 * namespace URI has been specified at some point.
	 */
	elem->ns = find_prefix(parser, "");
    }
    else if (APR_XML_NS_IS_RESERVED(elem->name)) {
	elem->ns = APR_XML_NS_NONE;
    }
    else {
	*colon = '\0';
	elem->ns = find_prefix(parser, elem->name);
	elem->name = colon + 1;

	if (APR_XML_NS_IS_ERROR(elem->ns)) {
	    parser->error = elem->ns;
	    return;
	}
    }

    /* adjust all remaining attributes' namespaces */
    for (attr = elem->attr; attr; attr = attr->next) {
        /*
         * apr_xml_attr defines this as "const" but we dup'd it, so we
         * know that we can change it. a bit hacky, but the existing
         * structure def is best.
         */
        char *attr_name = (char *)attr->name;

	colon = strchr(attr_name, 0x3A);
	if (colon == NULL) {
	    /*
	     * Attributes do NOT use the default namespace. Therefore,
	     * we place them into the "no namespace" category.
	     */
	    attr->ns = APR_XML_NS_NONE;
	}
	else if (APR_XML_NS_IS_RESERVED(attr->name)) {
	    attr->ns = APR_XML_NS_NONE;
	}
	else {
	    *colon = '\0';
	    attr->ns = find_prefix(parser, attr->name);
	    attr->name = colon + 1;

	    if (APR_XML_NS_IS_ERROR(attr->ns)) {
		parser->error = attr->ns;
		return;
	    }
	}
    }
}

static void end_handler(void *userdata, const char *name)
{
    apr_xml_parser *parser = userdata;

    /* punt once we find an error */
    if (parser->error)
	return;

    /* pop up one level */
    parser->cur_elem = parser->cur_elem->parent;
}

static void cdata_handler(void *userdata, const char *data, int len)
{
    apr_xml_parser *parser = userdata;
    apr_xml_elem *elem;
    apr_text_header *hdr;
    const char *s;

    /* punt once we find an error */
    if (parser->error)
	return;

    elem = parser->cur_elem;
    s = apr_pstrndup(parser->p, data, len);

    if (elem->last_child == NULL) {
	/* no children yet. this cdata follows the start tag */
	hdr = &elem->first_cdata;
    }
    else {
	/* child elements exist. this cdata follows the last child. */
	hdr = &elem->last_child->following_cdata;
    }

    apr_text_append(parser->p, hdr, s);
}

static apr_status_t cleanup_parser(void *ctx)
{
    apr_xml_parser *parser = ctx;

    XML_ParserFree(parser->xp);
    parser->xp = NULL;

    return APR_SUCCESS;
}

#if XML_MAJOR_VERSION > 1
/* Stop the parser if an entity declaration is hit. */
static void entity_declaration(void *userData, const XML_Char *entityName,
                               int is_parameter_entity, const XML_Char *value,
                               int value_length, const XML_Char *base,
                               const XML_Char *systemId, const XML_Char *publicId,
                               const XML_Char *notationName)
{
    apr_xml_parser *parser = userData;

    XML_StopParser(parser->xp, XML_FALSE);
}
#else
/* A noop default_handler. */
static void default_handler(void *userData, const XML_Char *s, int len)
{
}
#endif

APU_DECLARE(apr_xml_parser *) apr_xml_parser_create(apr_pool_t *pool)
{
    apr_xml_parser *parser = apr_pcalloc(pool, sizeof(*parser));

    parser->p = pool;
    parser->doc = apr_pcalloc(pool, sizeof(*parser->doc));

    parser->doc->namespaces = apr_array_make(pool, 5, sizeof(const char *));

    /* ### is there a way to avoid hard-coding this? */
    apr_xml_insert_uri(parser->doc->namespaces, APR_KW_DAV);

    parser->xp = XML_ParserCreate(NULL);
    if (parser->xp == NULL) {
        (*apr_pool_abort_get(pool))(APR_ENOMEM);
        return NULL;
    }

    apr_pool_cleanup_register(pool, parser, cleanup_parser,
                              apr_pool_cleanup_null);

    XML_SetUserData(parser->xp, parser);
    XML_SetElementHandler(parser->xp, start_handler, end_handler);
    XML_SetCharacterDataHandler(parser->xp, cdata_handler);

    /* Prevent the "billion laughs" attack against expat by disabling
     * internal entity expansion.  With 2.x, forcibly stop the parser
     * if an entity is declared - this is safer and a more obvious
     * failure mode.  With older versions, installing a noop
     * DefaultHandler means that internal entities will be expanded as
     * the empty string, which is also sufficient to prevent the
     * attack. */
#if XML_MAJOR_VERSION > 1
    XML_SetEntityDeclHandler(parser->xp, entity_declaration);
#else
    XML_SetDefaultHandler(parser->xp, default_handler);
#endif

    return parser;
}

static apr_status_t do_parse(apr_xml_parser *parser,
                             const char *data, apr_size_t len,
                             int is_final)
{
    if (parser->xp == NULL) {
        parser->error = APR_XML_ERROR_PARSE_DONE;
    }
    else {
        int rv = XML_Parse(parser->xp, data, (int)len, is_final);

        if (rv == 0) {
            parser->error = APR_XML_ERROR_EXPAT;
            parser->xp_err = XML_GetErrorCode(parser->xp);
        }
    }

    /* ### better error code? */
    return parser->error ? APR_EGENERAL : APR_SUCCESS;
}

APU_DECLARE(apr_status_t) apr_xml_parser_feed(apr_xml_parser *parser,
                                              const char *data,
                                              apr_size_t len)
{
    return do_parse(parser, data, len, 0 /* is_final */);
}

APU_DECLARE(apr_status_t) apr_xml_parser_done(apr_xml_parser *parser,
                                              apr_xml_doc **pdoc)
{
    char end;
    apr_status_t status = do_parse(parser, &end, 0, 1 /* is_final */);

    /* get rid of the parser */
    (void) apr_pool_cleanup_run(parser->p, parser, cleanup_parser);

    if (status)
        return status;

    if (pdoc != NULL)
        *pdoc = parser->doc;
    return APR_SUCCESS;
}

APU_DECLARE(char *) apr_xml_parser_geterror(apr_xml_parser *parser,
                                            char *errbuf,
                                            apr_size_t errbufsize)
{
    int error = parser->error;
    const char *msg;

    /* clear our record of an error */
    parser->error = 0;

    switch (error) {
    case 0:
        msg = "No error.";
        break;

    case APR_XML_NS_ERROR_UNKNOWN_PREFIX:
        msg = "An undefined namespace prefix was used.";
        break;

    case APR_XML_NS_ERROR_INVALID_DECL:
        msg = "A namespace prefix was defined with an empty URI.";
        break;

    case APR_XML_ERROR_EXPAT:
        (void) apr_snprintf(errbuf, errbufsize,
                            "XML parser error code: %s (%d)",
                            XML_ErrorString(parser->xp_err), parser->xp_err);
        return errbuf;

    case APR_XML_ERROR_PARSE_DONE:
        msg = "The parser is not active.";
        break;

    default:
        msg = "There was an unknown error within the XML body.";
        break;
    }

    (void) apr_cpystrn(errbuf, msg, errbufsize);
    return errbuf;
}

APU_DECLARE(apr_status_t) apr_xml_parse_file(apr_pool_t *p,
                                             apr_xml_parser **parser,
                                             apr_xml_doc **ppdoc,
                                             apr_file_t *xmlfd,
                                             apr_size_t buffer_length)
{
    apr_status_t rv;
    char *buffer;
    apr_size_t length;

    *parser = apr_xml_parser_create(p);
    if (*parser == NULL) {
        /* FIXME: returning an error code would be nice,
         * but we dont get one ;( */
        return APR_EGENERAL;
    }
    buffer = apr_palloc(p, buffer_length);
    length = buffer_length;

    rv = apr_file_read(xmlfd, buffer, &length);

    while (rv == APR_SUCCESS) {
        rv = apr_xml_parser_feed(*parser, buffer, length);
        if (rv != APR_SUCCESS) {
            return rv;
        }

        length = buffer_length;
        rv = apr_file_read(xmlfd, buffer, &length);
    }
    if (rv != APR_EOF) {
        return rv;
    }
    rv = apr_xml_parser_done(*parser, ppdoc);
    *parser = NULL;
    return rv;
}

APU_DECLARE(void) apr_text_append(apr_pool_t * p, apr_text_header *hdr,
                                  const char *text)
{
    apr_text *t = apr_palloc(p, sizeof(*t));

    t->text = text;
    t->next = NULL;

    if (hdr->first == NULL) {
	/* no text elements yet */
	hdr->first = hdr->last = t;
    }
    else {
	/* append to the last text element */
	hdr->last->next = t;
	hdr->last = t;
    }
}


/* ---------------------------------------------------------------
**
** XML UTILITY FUNCTIONS
*/

/*
** apr_xml_quote_string: quote an XML string
**
** Replace '<', '>', and '&' with '&lt;', '&gt;', and '&amp;'.
** If quotes is true, then replace '"' with '&quot;'.
**
** quotes is typically set to true for XML strings that will occur within
** double quotes -- attribute values.
*/
APU_DECLARE(const char *) apr_xml_quote_string(apr_pool_t *p, const char *s,
                                               int quotes)
{
    const char *scan;
    apr_size_t len = 0;
    apr_size_t extra = 0;
    char *qstr;
    char *qscan;
    char c;

    for (scan = s; (c = *scan) != '\0'; ++scan, ++len) {
	if (c == '<' || c == '>')
	    extra += 3;		/* &lt; or &gt; */
	else if (c == '&')
	    extra += 4;		/* &amp; */
	else if (quotes && c == '"')
	    extra += 5;		/* &quot; */
    }

    /* nothing to do? */
    if (extra == 0)
	return s;

    qstr = apr_palloc(p, len + extra + 1);
    for (scan = s, qscan = qstr; (c = *scan) != '\0'; ++scan) {
	if (c == '<') {
	    *qscan++ = '&';
	    *qscan++ = 'l';
	    *qscan++ = 't';
	    *qscan++ = ';';
	}
	else if (c == '>') {
	    *qscan++ = '&';
	    *qscan++ = 'g';
	    *qscan++ = 't';
	    *qscan++ = ';';
	}
	else if (c == '&') {
	    *qscan++ = '&';
	    *qscan++ = 'a';
	    *qscan++ = 'm';
	    *qscan++ = 'p';
	    *qscan++ = ';';
	}
	else if (quotes && c == '"') {
	    *qscan++ = '&';
	    *qscan++ = 'q';
	    *qscan++ = 'u';
	    *qscan++ = 'o';
	    *qscan++ = 't';
	    *qscan++ = ';';
	}
	else {
	    *qscan++ = c;
	}
    }

    *qscan = '\0';
    return qstr;
}

/* how many characters for the given integer? */
#define APR_XML_NS_LEN(ns) ((ns) < 10 ? 1 : (ns) < 100 ? 2 : (ns) < 1000 ? 3 : \
                            (ns) < 10000 ? 4 : (ns) < 100000 ? 5 : \
                            (ns) < 1000000 ? 6 : (ns) < 10000000 ? 7 : \
                            (ns) < 100000000 ? 8 : (ns) < 1000000000 ? 9 : 10)

static apr_size_t text_size(const apr_text *t)
{
    apr_size_t size = 0;

    for (; t; t = t->next)
	size += strlen(t->text);
    return size;
}

static apr_size_t elem_size(const apr_xml_elem *elem, int style,
                            apr_array_header_t *namespaces, int *ns_map)
{
    apr_size_t size;

    if (style == APR_XML_X2T_FULL || style == APR_XML_X2T_FULL_NS_LANG ||
	style == APR_XML_X2T_PARSED) {
	const apr_xml_attr *attr;

	size = 0;

	if (style == APR_XML_X2T_FULL_NS_LANG) {
	    int i;

	    /*
	    ** The outer element will contain xmlns:ns%d="%s" attributes
	    ** and an xml:lang attribute, if applicable.
	    */

	    for (i = namespaces->nelts; i--;) {
		/* compute size of: ' xmlns:ns%d="%s"' */
		size += (9 + APR_XML_NS_LEN(i) + 2 +
			 strlen(APR_XML_GET_URI_ITEM(namespaces, i)) + 1);
	    }

	    if (elem->lang != NULL) {
		/* compute size of: ' xml:lang="%s"' */
		size += 11 + strlen(elem->lang) + 1;
	    }
	}
	else if (style == APR_XML_X2T_PARSED) {
	    apr_xml_ns_scope *ns_scope = elem->ns_scope;

	    /* compute size of: ' xmlns:%s="%s"' */
	    for (; ns_scope; ns_scope = ns_scope->next) {
		size += 10 + strlen(find_prefix_name(elem, ns_scope->ns, 0)) +
			     strlen(APR_XML_GET_URI_ITEM(namespaces, ns_scope->ns));
	    }

	    if (elem->lang != NULL) {
		/* compute size of: ' xml:lang="%s"' */
		size += 11 + strlen(elem->lang) + 1;
	    }
	}

	if (elem->ns == APR_XML_NS_NONE) {
	    /* compute size of: <%s> */
	    size += 1 + strlen(elem->name) + 1;
	}
	else if (style == APR_XML_X2T_PARSED) {
	    /* compute size of: <%s:%s> */
	    size += 3 + strlen(find_prefix_name(elem, elem->ns, 1)) + strlen(elem->name);
	}
	else {
	    int ns = ns_map ? ns_map[elem->ns] : elem->ns;

	    /* compute size of: <ns%d:%s> */
	    size += 3 + APR_XML_NS_LEN(ns) + 1 + strlen(elem->name) + 1;
	}

	if (APR_XML_ELEM_IS_EMPTY(elem)) {
	    /* insert a closing "/" */
	    size += 1;
	}
	else {
	    /*
	     * two of above plus "/":
	     *     <ns%d:%s> ... </ns%d:%s>
	     * OR  <%s> ... </%s>
	     */
	    size = 2 * size + 1;
	}

	for (attr = elem->attr; attr; attr = attr->next) {
	    if (attr->ns == APR_XML_NS_NONE) {
		/* compute size of: ' %s="%s"' */
		size += 1 + strlen(attr->name) + 2 + strlen(attr->value) + 1;
	    }
	    else if (style == APR_XML_X2T_PARSED) {
		/* compute size of: ' %s:%s="%s"' */
		size += 5 + strlen(find_prefix_name(elem, attr->ns, 1)) + strlen(attr->name) + strlen(attr->value);
	    }
	    else {
		/* compute size of: ' ns%d:%s="%s"' */
                int ns = ns_map ? ns_map[attr->ns] : attr->ns;
                size += 3 + APR_XML_NS_LEN(ns) + 1 + strlen(attr->name) + 2 + strlen(attr->value) + 1;
	    }
	}

	/*
	** If the element has an xml:lang value that is *different* from
	** its parent, then add the thing in: ' xml:lang="%s"'.
	**
	** NOTE: we take advantage of the pointer equality established by
	** the parsing for "inheriting" the xml:lang values from parents.
	*/
	if (elem->lang != NULL &&
	    (elem->parent == NULL || elem->lang != elem->parent->lang)) {
	    size += 11 + strlen(elem->lang) + 1;
	}
    }
    else if (style == APR_XML_X2T_LANG_INNER) {
	/*
	 * This style prepends the xml:lang value plus a null terminator.
	 * If a lang value is not present, then we insert a null term.
	 */
	size = elem->lang ? strlen(elem->lang) + 1 : 1;
    }
    else
	size = 0;

    size += text_size(elem->first_cdata.first);

    for (elem = elem->first_child; elem; elem = elem->next) {
	/* the size of the child element plus the CDATA that follows it */
	size += (elem_size(elem, style == APR_XML_X2T_PARSED ? APR_XML_X2T_PARSED : APR_XML_X2T_FULL, NULL, ns_map) +
		 text_size(elem->following_cdata.first));
    }

    return size;
}

static char *write_text(char *s, const apr_text *t)
{
    for (; t; t = t->next) {
	apr_size_t len = strlen(t->text);
	memcpy(s, t->text, len);
	s += len;
    }
    return s;
}

static char *write_elem(char *s, const apr_xml_elem *elem, int style,
			apr_array_header_t *namespaces, int *ns_map)
{
    const apr_xml_elem *child;
    apr_size_t len;
    int ns;

    if (style == APR_XML_X2T_FULL || style == APR_XML_X2T_FULL_NS_LANG ||
	style == APR_XML_X2T_PARSED) {
	int empty = APR_XML_ELEM_IS_EMPTY(elem);
	const apr_xml_attr *attr;

	if (elem->ns == APR_XML_NS_NONE)
	    len = sprintf(s, "<%s", elem->name);
	else if (style == APR_XML_X2T_PARSED)
	    len = sprintf(s, "<%s:%s", find_prefix_name(elem, elem->ns, 1), elem->name);
	else {
	    ns = ns_map ? ns_map[elem->ns] : elem->ns;
	    len = sprintf(s, "<ns%d:%s", ns, elem->name);
	}
	s += len;

	for (attr = elem->attr; attr; attr = attr->next) {
	    if (attr->ns == APR_XML_NS_NONE)
		len = sprintf(s, " %s=\"%s\"", attr->name, attr->value);
	    else if (style == APR_XML_X2T_PARSED)
		len = sprintf(s, " %s:%s=\"%s\"",
			      find_prefix_name(elem, attr->ns, 1), attr->name, attr->value);
	    else {
		ns = ns_map ? ns_map[attr->ns] : attr->ns;
		len = sprintf(s, " ns%d:%s=\"%s\"", ns, attr->name, attr->value);
	    }
	    s += len;
	}

	/* add the xml:lang value if necessary */
	if (elem->lang != NULL &&
	    (style == APR_XML_X2T_FULL_NS_LANG ||
	     elem->parent == NULL ||
	     elem->lang != elem->parent->lang)) {
	    len = sprintf(s, " xml:lang=\"%s\"", elem->lang);
	    s += len;
	}

	/* add namespace definitions, if required */
	if (style == APR_XML_X2T_FULL_NS_LANG) {
	    int i;

	    for (i = namespaces->nelts; i--;) {
		len = sprintf(s, " xmlns:ns%d=\"%s\"", i,
			      APR_XML_GET_URI_ITEM(namespaces, i));
		s += len;
	    }
	}
	else if (style == APR_XML_X2T_PARSED) {
	    apr_xml_ns_scope *ns_scope = elem->ns_scope;

	    for (; ns_scope; ns_scope = ns_scope->next) {
		const char *prefix = find_prefix_name(elem, ns_scope->ns, 0);

		len = sprintf(s, " xmlns%s%s=\"%s\"",
			      *prefix ? ":" : "", *prefix ? prefix : "",
			      APR_XML_GET_URI_ITEM(namespaces, ns_scope->ns));
		s += len;
	    }
	}

	/* no more to do. close it up and go. */
	if (empty) {
	    *s++ = '/';
	    *s++ = '>';
	    return s;
	}

	/* just close it */
	*s++ = '>';
    }
    else if (style == APR_XML_X2T_LANG_INNER) {
	/* prepend the xml:lang value */
	if (elem->lang != NULL) {
	    len = strlen(elem->lang);
	    memcpy(s, elem->lang, len);
	    s += len;
	}
	*s++ = '\0';
    }

    s = write_text(s, elem->first_cdata.first);

    for (child = elem->first_child; child; child = child->next) {
	s = write_elem(s, child,
		       style == APR_XML_X2T_PARSED ? APR_XML_X2T_PARSED : APR_XML_X2T_FULL,
		       NULL, ns_map);
	s = write_text(s, child->following_cdata.first);
    }

    if (style == APR_XML_X2T_FULL || style == APR_XML_X2T_FULL_NS_LANG || style == APR_XML_X2T_PARSED) {
	if (elem->ns == APR_XML_NS_NONE)
	    len = sprintf(s, "</%s>", elem->name);
	else if (style == APR_XML_X2T_PARSED)
	    len = sprintf(s, "</%s:%s>", find_prefix_name(elem, elem->ns, 1), elem->name);
	else {
	    ns = ns_map ? ns_map[elem->ns] : elem->ns;
	    len = sprintf(s, "</ns%d:%s>", ns, elem->name);
	}
	s += len;
    }

    return s;
}

APU_DECLARE(void) apr_xml_quote_elem(apr_pool_t *p, apr_xml_elem *elem)
{
    apr_text *scan_txt;
    apr_xml_attr *scan_attr;
    apr_xml_elem *scan_elem;

    /* convert the element's text */
    for (scan_txt = elem->first_cdata.first;
	 scan_txt != NULL;
	 scan_txt = scan_txt->next) {
	scan_txt->text = apr_xml_quote_string(p, scan_txt->text, 0);
    }
    for (scan_txt = elem->following_cdata.first;
	 scan_txt != NULL;
	 scan_txt = scan_txt->next) {
	scan_txt->text = apr_xml_quote_string(p, scan_txt->text, 0);
    }

    /* convert the attribute values */
    for (scan_attr = elem->attr;
	 scan_attr != NULL;
	 scan_attr = scan_attr->next) {
	scan_attr->value = apr_xml_quote_string(p, scan_attr->value, 1);
    }

    /* convert the child elements */
    for (scan_elem = elem->first_child;
	 scan_elem != NULL;
	 scan_elem = scan_elem->next) {
	apr_xml_quote_elem(p, scan_elem);
    }
}

/* convert an element to a text string */
APU_DECLARE(void) apr_xml_to_text(apr_pool_t * p, const apr_xml_elem *elem,
                                  int style, apr_array_header_t *namespaces,
                                  int *ns_map, const char **pbuf,
                                  apr_size_t *psize)
{
    /* get the exact size, plus a null terminator */
    apr_size_t size = elem_size(elem, style, namespaces, ns_map) + 1;
    char *s = apr_palloc(p, size);

    (void) write_elem(s, elem, style, namespaces, ns_map);
    s[size - 1] = '\0';

    *pbuf = s;
    if (psize)
	*psize = size;
}

APU_DECLARE(const char *) apr_xml_empty_elem(apr_pool_t * p,
                                             const apr_xml_elem *elem)
{
    if (elem->ns == APR_XML_NS_NONE) {
	/*
	 * The prefix (xml...) is already within the prop name, or
	 * the element simply has no prefix.
	 */
	return apr_psprintf(p, "<%s/>" DEBUG_CR, elem->name);
    }

    return apr_psprintf(p, "<ns%d:%s/>" DEBUG_CR, elem->ns, elem->name);
}

/* return the URI's (existing) index, or insert it and return a new index */
APU_DECLARE(int) apr_xml_insert_uri(apr_array_header_t *uri_array,
                                    const char *uri)
{
    int i;
    const char **pelt;

    /* never insert an empty URI; this index is always APR_XML_NS_NONE */
    if (*uri == '\0')
        return APR_XML_NS_NONE;  

    for (i = uri_array->nelts; i--;) {
	if (strcmp(uri, APR_XML_GET_URI_ITEM(uri_array, i)) == 0)
	    return i;
    }

    pelt = apr_array_push(uri_array);
    *pelt = uri;		/* assume uri is const or in a pool */
    return uri_array->nelts - 1;
}

/* convert the element to EBCDIC */
#if APR_CHARSET_EBCDIC
static apr_status_t apr_xml_parser_convert_elem(apr_xml_elem *e,
                                                apr_xlate_t *convset)
{
    apr_xml_attr *a;
    apr_xml_elem *ec;
    apr_text *t;
    apr_size_t inbytes_left, outbytes_left;
    apr_status_t status;

    inbytes_left = outbytes_left = strlen(e->name);
    status = apr_xlate_conv_buffer(convset, e->name,  &inbytes_left, (char *) e->name, &outbytes_left);
    if (status) {
        return status;
    }

    for (t = e->first_cdata.first; t != NULL; t = t->next) {
        inbytes_left = outbytes_left = strlen(t->text);
        status = apr_xlate_conv_buffer(convset, t->text, &inbytes_left, (char *) t->text, &outbytes_left);
        if (status) {
            return status;
        }
    }

    for (t = e->following_cdata.first;  t != NULL; t = t->next) {
        inbytes_left = outbytes_left = strlen(t->text);
        status = apr_xlate_conv_buffer(convset, t->text, &inbytes_left, (char *) t->text, &outbytes_left);
        if (status) {
            return status;
        }
    }

    for (a = e->attr; a != NULL; a = a->next) {
        inbytes_left = outbytes_left = strlen(a->name);
        status = apr_xlate_conv_buffer(convset, a->name, &inbytes_left, (char *) a->name, &outbytes_left);
        if (status) {
            return status;
        }
        inbytes_left = outbytes_left = strlen(a->value);
        status = apr_xlate_conv_buffer(convset, a->value, &inbytes_left, (char *) a->value, &outbytes_left);
        if (status) {
            return status;
        }
    }

    for (ec = e->first_child; ec != NULL; ec = ec->next) {
        status = apr_xml_parser_convert_elem(ec, convset);
        if (status) {
            return status;
        }
    }
    return APR_SUCCESS;
}

/* convert the whole document to EBCDIC */
APU_DECLARE(apr_status_t) apr_xml_parser_convert_doc(apr_pool_t *pool,
                                                     apr_xml_doc *pdoc,
                                                     apr_xlate_t *convset)
{
    apr_status_t status;
    /* Don't convert the namespaces: they are constant! */
    if (pdoc->namespaces != NULL) {
        int i;
        apr_array_header_t *namespaces;
        namespaces = apr_array_make(pool, pdoc->namespaces->nelts, sizeof(const char *));
        if (namespaces == NULL)
            return APR_ENOMEM;
        for (i = 0; i < pdoc->namespaces->nelts; i++) {
            apr_size_t inbytes_left, outbytes_left;
            char *ptr = (char *) APR_XML_GET_URI_ITEM(pdoc->namespaces, i);
            ptr = apr_pstrdup(pool, ptr);
            if ( ptr == NULL)
                return APR_ENOMEM;
            inbytes_left = outbytes_left = strlen(ptr);
            status = apr_xlate_conv_buffer(convset, ptr, &inbytes_left, ptr, &outbytes_left);
            if (status) {
                return status;
            }
            apr_xml_insert_uri(namespaces, ptr);
        }
        pdoc->namespaces = namespaces;
    }
    return apr_xml_parser_convert_elem(pdoc->root, convset);
}
#endif
