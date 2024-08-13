/* PR c/27747 */
/* This is supposed to succeed only if
   the target defines HANDLE_PRAGMA_PACK_PUSH_POP
   and doesn't define HANDLE_PRAGMA_PACK_WITH_EXPANSION.  */
/* { dg-do compile { target { ! { powerpc-ibm-aix* *-*-solaris2* fido-*-* m68k-*-* sh*-[us]*-elf m32c-*-* } } } } */

#define push bar
#define foo _Pragma ("pack(push)")
foo
int i;
#pragma pack(pop)
