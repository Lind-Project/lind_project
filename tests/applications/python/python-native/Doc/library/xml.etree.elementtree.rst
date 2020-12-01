
:mod:`xml.etree.ElementTree` --- The ElementTree XML API
========================================================

.. module:: xml.etree.ElementTree
   :synopsis: Implementation of the ElementTree API.
.. moduleauthor:: Fredrik Lundh <fredrik@pythonware.com>


.. versionadded:: 2.5

The :class:`Element` type is a flexible container object, designed to store
hierarchical data structures in memory.  The type can be described as a cross
between a list and a dictionary.

Each element has a number of properties associated with it:

* a tag which is a string identifying what kind of data this element represents
  (the element type, in other words).

* a number of attributes, stored in a Python dictionary.

* a text string.

* an optional tail string.

* a number of child elements, stored in a Python sequence

To create an element instance, use the :class:`Element` constructor or the
:func:`SubElement` factory function.

The :class:`ElementTree` class can be used to wrap an element structure, and
convert it from and to XML.

A C implementation of this API is available as :mod:`xml.etree.cElementTree`.

See http://effbot.org/zone/element-index.htm for tutorials and links to other
docs.  Fredrik Lundh's page is also the location of the development version of
the xml.etree.ElementTree.

.. versionchanged:: 2.7
   The ElementTree API is updated to 1.3.  For more information, see
   `Introducing ElementTree 1.3
   <http://effbot.org/zone/elementtree-13-intro.htm>`_.


.. _elementtree-functions:

Functions
---------


.. function:: Comment(text=None)

   Comment element factory.  This factory function creates a special element
   that will be serialized as an XML comment by the standard serializer.  The
   comment string can be either a bytestring or a Unicode string.  *text* is a
   string containing the comment string.  Returns an element instance
   representing a comment.


.. function:: dump(elem)

   Writes an element tree or element structure to sys.stdout.  This function
   should be used for debugging only.

   The exact output format is implementation dependent.  In this version, it's
   written as an ordinary XML file.

   *elem* is an element tree or an individual element.


.. function:: fromstring(text)

   Parses an XML section from a string constant.  Same as :func:`XML`.  *text*
   is a string containing XML data.  Returns an :class:`Element` instance.


.. function:: fromstringlist(sequence, parser=None)

   Parses an XML document from a sequence of string fragments.  *sequence* is a
   list or other sequence containing XML data fragments.  *parser* is an
   optional parser instance.  If not given, the standard :class:`XMLParser`
   parser is used.  Returns an :class:`Element` instance.

   .. versionadded:: 2.7


.. function:: iselement(element)

   Checks if an object appears to be a valid element object.  *element* is an
   element instance.  Returns a true value if this is an element object.


.. function:: iterparse(source, events=None, parser=None)

   Parses an XML section into an element tree incrementally, and reports what's
   going on to the user.  *source* is a filename or file object containing XML
   data.  *events* is a list of events to report back.  If omitted, only "end"
   events are reported.  *parser* is an optional parser instance.  If not
   given, the standard :class:`XMLParser` parser is used.  Returns an
   :term:`iterator` providing ``(event, elem)`` pairs.

   .. note::

      :func:`iterparse` only guarantees that it has seen the ">"
      character of a starting tag when it emits a "start" event, so the
      attributes are defined, but the contents of the text and tail attributes
      are undefined at that point.  The same applies to the element children;
      they may or may not be present.

      If you need a fully populated element, look for "end" events instead.


.. function:: parse(source, parser=None)

   Parses an XML section into an element tree.  *source* is a filename or file
   object containing XML data.  *parser* is an optional parser instance.  If
   not given, the standard :class:`XMLParser` parser is used.  Returns an
   :class:`ElementTree` instance.


.. function:: ProcessingInstruction(target, text=None)

   PI element factory.  This factory function creates a special element that
   will be serialized as an XML processing instruction.  *target* is a string
   containing the PI target.  *text* is a string containing the PI contents, if
   given.  Returns an element instance, representing a processing instruction.


.. function:: register_namespace(prefix, uri)

   Registers a namespace prefix.  The registry is global, and any existing
   mapping for either the given prefix or the namespace URI will be removed.
   *prefix* is a namespace prefix.  *uri* is a namespace uri.  Tags and
   attributes in this namespace will be serialized with the given prefix, if at
   all possible.

   .. versionadded:: 2.7


.. function:: SubElement(parent, tag, attrib={}, **extra)

   Subelement factory.  This function creates an element instance, and appends
   it to an existing element.

   The element name, attribute names, and attribute values can be either
   bytestrings or Unicode strings.  *parent* is the parent element.  *tag* is
   the subelement name.  *attrib* is an optional dictionary, containing element
   attributes.  *extra* contains additional attributes, given as keyword
   arguments.  Returns an element instance.


.. function:: tostring(element, encoding="us-ascii", method="xml")

   Generates a string representation of an XML element, including all
   subelements.  *element* is an :class:`Element` instance.  *encoding* [1]_ is
   the output encoding (default is US-ASCII).  *method* is either ``"xml"``,
   ``"html"`` or ``"text"`` (default is ``"xml"``).  Returns an encoded string
   containing the XML data.


.. function:: tostringlist(element, encoding="us-ascii", method="xml")

   Generates a string representation of an XML element, including all
   subelements.  *element* is an :class:`Element` instance.  *encoding* [1]_ is
   the output encoding (default is US-ASCII).   *method* is either ``"xml"``,
   ``"html"`` or ``"text"`` (default is ``"xml"``).  Returns a list of encoded
   strings containing the XML data.  It does not guarantee any specific
   sequence, except that ``"".join(tostringlist(element)) ==
   tostring(element)``.

   .. versionadded:: 2.7


.. function:: XML(text, parser=None)

   Parses an XML section from a string constant.  This function can be used to
   embed "XML literals" in Python code.  *text* is a string containing XML
   data.  *parser* is an optional parser instance.  If not given, the standard
   :class:`XMLParser` parser is used.  Returns an :class:`Element` instance.


.. function:: XMLID(text, parser=None)

   Parses an XML section from a string constant, and also returns a dictionary
   which maps from element id:s to elements.  *text* is a string containing XML
   data.  *parser* is an optional parser instance.  If not given, the standard
   :class:`XMLParser` parser is used.  Returns a tuple containing an
   :class:`Element` instance and a dictionary.


.. _elementtree-element-objects:

Element Objects
---------------


.. class:: Element(tag, attrib={}, **extra)

   Element class.  This class defines the Element interface, and provides a
   reference implementation of this interface.

   The element name, attribute names, and attribute values can be either
   bytestrings or Unicode strings.  *tag* is the element name.  *attrib* is
   an optional dictionary, containing element attributes.  *extra* contains
   additional attributes, given as keyword arguments.


   .. attribute:: tag

      A string identifying what kind of data this element represents (the
      element type, in other words).


   .. attribute:: text

      The *text* attribute can be used to hold additional data associated with
      the element.  As the name implies this attribute is usually a string but
      may be any application-specific object.  If the element is created from
      an XML file the attribute will contain any text found between the element
      tags.


   .. attribute:: tail

      The *tail* attribute can be used to hold additional data associated with
      the element.  This attribute is usually a string but may be any
      application-specific object.  If the element is created from an XML file
      the attribute will contain any text found after the element's end tag and
      before the next tag.


   .. attribute:: attrib

      A dictionary containing the element's attributes.  Note that while the
      *attrib* value is always a real mutable Python dictionary, an ElementTree
      implementation may choose to use another internal representation, and
      create the dictionary only if someone asks for it.  To take advantage of
      such implementations, use the dictionary methods below whenever possible.

   The following dictionary-like methods work on the element attributes.


   .. method:: clear()

      Resets an element.  This function removes all subelements, clears all
      attributes, and sets the text and tail attributes to None.


   .. method:: get(key, default=None)

      Gets the element attribute named *key*.

      Returns the attribute value, or *default* if the attribute was not found.


   .. method:: items()

      Returns the element attributes as a sequence of (name, value) pairs.  The
      attributes are returned in an arbitrary order.


   .. method:: keys()

      Returns the elements attribute names as a list.  The names are returned
      in an arbitrary order.


   .. method:: set(key, value)

      Set the attribute *key* on the element to *value*.

   The following methods work on the element's children (subelements).


   .. method:: append(subelement)

      Adds the element *subelement* to the end of this elements internal list
      of subelements.


   .. method:: extend(subelements)

      Appends *subelements* from a sequence object with zero or more elements.
      Raises :exc:`AssertionError` if a subelement is not a valid object.

      .. versionadded:: 2.7


   .. method:: find(match)

      Finds the first subelement matching *match*.  *match* may be a tag name
      or path.  Returns an element instance or ``None``.


   .. method:: findall(match)

      Finds all matching subelements, by tag name or path.  Returns a list
      containing all matching elements in document order.


   .. method:: findtext(match, default=None)

      Finds text for the first subelement matching *match*.  *match* may be
      a tag name or path.  Returns the text content of the first matching
      element, or *default* if no element was found.  Note that if the matching
      element has no text content an empty string is returned.


   .. method:: getchildren()

      .. deprecated:: 2.7
         Use ``list(elem)`` or iteration.


   .. method:: getiterator(tag=None)

      .. deprecated:: 2.7
         Use method :meth:`Element.iter` instead.


   .. method:: insert(index, element)

      Inserts a subelement at the given position in this element.


   .. method:: iter(tag=None)

      Creates a tree :term:`iterator` with the current element as the root.
      The iterator iterates over this element and all elements below it, in
      document (depth first) order.  If *tag* is not ``None`` or ``'*'``, only
      elements whose tag equals *tag* are returned from the iterator.  If the
      tree structure is modified during iteration, the result is undefined.


   .. method:: iterfind(match)

      Finds all matching subelements, by tag name or path.  Returns an iterable
      yielding all matching elements in document order.

      .. versionadded:: 2.7


   .. method:: itertext()

      Creates a text iterator.  The iterator loops over this element and all
      subelements, in document order, and returns all inner text.

      .. versionadded:: 2.7


   .. method:: makeelement(tag, attrib)

      Creates a new element object of the same type as this element.  Do not
      call this method, use the :func:`SubElement` factory function instead.


   .. method:: remove(subelement)

      Removes *subelement* from the element.  Unlike the find\* methods this
      method compares elements based on the instance identity, not on tag value
      or contents.

   :class:`Element` objects also support the following sequence type methods
   for working with subelements: :meth:`__delitem__`, :meth:`__getitem__`,
   :meth:`__setitem__`, :meth:`__len__`.

   Caution: Elements with no subelements will test as ``False``.  This behavior
   will change in future versions.  Use specific ``len(elem)`` or ``elem is
   None`` test instead. ::

     element = root.find('foo')

     if not element:  # careful!
         print "element not found, or element has no subelements"

     if element is None:
         print "element not found"


.. _elementtree-elementtree-objects:

ElementTree Objects
-------------------


.. class:: ElementTree(element=None, file=None)

   ElementTree wrapper class.  This class represents an entire element
   hierarchy, and adds some extra support for serialization to and from
   standard XML.

   *element* is the root element.  The tree is initialized with the contents
   of the XML *file* if given.


   .. method:: _setroot(element)

      Replaces the root element for this tree.  This discards the current
      contents of the tree, and replaces it with the given element.  Use with
      care.  *element* is an element instance.


   .. method:: find(match)

      Finds the first toplevel element matching *match*.  *match* may be a tag
      name or path.  Same as getroot().find(match).  Returns the first matching
      element, or ``None`` if no element was found.


   .. method:: findall(match)

      Finds all matching subelements, by tag name or path.  Same as
      getroot().findall(match).  *match* may be a tag name or path.  Returns a
      list containing all matching elements, in document order.


   .. method:: findtext(match, default=None)

      Finds the element text for the first toplevel element with given tag.
      Same as getroot().findtext(match).  *match* may be a tag name or path.
      *default* is the value to return if the element was not found.  Returns
      the text content of the first matching element, or the default value no
      element was found.  Note that if the element is found, but has no text
      content, this method returns an empty string.


   .. method:: getiterator(tag=None)

      .. deprecated:: 2.7
         Use method :meth:`ElementTree.iter` instead.


   .. method:: getroot()

      Returns the root element for this tree.


   .. method:: iter(tag=None)

      Creates and returns a tree iterator for the root element.  The iterator
      loops over all elements in this tree, in section order.  *tag* is the tag
      to look for (default is to return all elements)


   .. method:: iterfind(match)

      Finds all matching subelements, by tag name or path.  Same as
      getroot().iterfind(match). Returns an iterable yielding all matching
      elements in document order.

      .. versionadded:: 2.7


   .. method:: parse(source, parser=None)

      Loads an external XML section into this element tree.  *source* is a file
      name or file object.  *parser* is an optional parser instance.  If not
      given, the standard XMLParser parser is used.  Returns the section
      root element.


   .. method:: write(file, encoding="us-ascii", xml_declaration=None, method="xml")

      Writes the element tree to a file, as XML.  *file* is a file name, or a
      file object opened for writing.  *encoding* [1]_ is the output encoding
      (default is US-ASCII).  *xml_declaration* controls if an XML declaration
      should be added to the file.  Use False for never, True for always, None
      for only if not US-ASCII or UTF-8 (default is None).  *method* is either
      ``"xml"``, ``"html"`` or ``"text"`` (default is ``"xml"``).  Returns an
      encoded string.

This is the XML file that is going to be manipulated::

    <html>
        <head>
            <title>Example page</title>
        </head>
        <body>
            <p>Moved to <a href="http://example.org/">example.org</a>
            or <a href="http://example.com/">example.com</a>.</p>
        </body>
    </html>

Example of changing the attribute "target" of every link in first paragraph::

    >>> from xml.etree.ElementTree import ElementTree
    >>> tree = ElementTree()
    >>> tree.parse("index.xhtml")
    <Element 'html' at 0xb77e6fac>
    >>> p = tree.find("body/p")     # Finds first occurrence of tag p in body
    >>> p
    <Element 'p' at 0xb77ec26c>
    >>> links = list(p.iter("a"))   # Returns list of all links
    >>> links
    [<Element 'a' at 0xb77ec2ac>, <Element 'a' at 0xb77ec1cc>]
    >>> for i in links:             # Iterates through all found links
    ...     i.attrib["target"] = "blank"
    >>> tree.write("output.xhtml")

.. _elementtree-qname-objects:

QName Objects
-------------


.. class:: QName(text_or_uri, tag=None)

   QName wrapper.  This can be used to wrap a QName attribute value, in order
   to get proper namespace handling on output.  *text_or_uri* is a string
   containing the QName value, in the form {uri}local, or, if the tag argument
   is given, the URI part of a QName.  If *tag* is given, the first argument is
   interpreted as an URI, and this argument is interpreted as a local name.
   :class:`QName` instances are opaque.


.. _elementtree-treebuilder-objects:

TreeBuilder Objects
-------------------


.. class:: TreeBuilder(element_factory=None)

   Generic element structure builder.  This builder converts a sequence of
   start, data, and end method calls to a well-formed element structure.  You
   can use this class to build an element structure using a custom XML parser,
   or a parser for some other XML-like format.  The *element_factory* is called
   to create new :class:`Element` instances when given.


   .. method:: close()

      Flushes the builder buffers, and returns the toplevel document
      element.  Returns an :class:`Element` instance.


   .. method:: data(data)

      Adds text to the current element.  *data* is a string.  This should be
      either a bytestring, or a Unicode string.


   .. method:: end(tag)

      Closes the current element.  *tag* is the element name.  Returns the
      closed element.


   .. method:: start(tag, attrs)

      Opens a new element.  *tag* is the element name.  *attrs* is a dictionary
      containing element attributes.  Returns the opened element.


   In addition, a custom :class:`TreeBuilder` object can provide the
   following method:

   .. method:: doctype(name, pubid, system)

      Handles a doctype declaration.  *name* is the doctype name.  *pubid* is
      the public identifier.  *system* is the system identifier.  This method
      does not exist on the default :class:`TreeBuilder` class.

      .. versionadded:: 2.7


.. _elementtree-xmlparser-objects:

XMLParser Objects
-----------------


.. class:: XMLParser(html=0, target=None, encoding=None)

   :class:`Element` structure builder for XML source data, based on the expat
   parser.  *html* are predefined HTML entities.  This flag is not supported by
   the current implementation.  *target* is the target object.  If omitted, the
   builder uses an instance of the standard TreeBuilder class.  *encoding* [1]_
   is optional.  If given, the value overrides the encoding specified in the
   XML file.


   .. method:: close()

      Finishes feeding data to the parser.  Returns an element structure.


   .. method:: doctype(name, pubid, system)

      .. deprecated:: 2.7
         Define the :meth:`TreeBuilder.doctype` method on a custom TreeBuilder
         target.


   .. method:: feed(data)

      Feeds data to the parser.  *data* is encoded data.

:meth:`XMLParser.feed` calls *target*\'s :meth:`start` method
for each opening tag, its :meth:`end` method for each closing tag,
and data is processed by method :meth:`data`.  :meth:`XMLParser.close`
calls *target*\'s method :meth:`close`.
:class:`XMLParser` can be used not only for building a tree structure.
This is an example of counting the maximum depth of an XML file::

    >>> from xml.etree.ElementTree import XMLParser
    >>> class MaxDepth:                     # The target object of the parser
    ...     maxDepth = 0
    ...     depth = 0
    ...     def start(self, tag, attrib):   # Called for each opening tag.
    ...         self.depth += 1
    ...         if self.depth > self.maxDepth:
    ...             self.maxDepth = self.depth
    ...     def end(self, tag):             # Called for each closing tag.
    ...         self.depth -= 1
    ...     def data(self, data):
    ...         pass            # We do not need to do anything with data.
    ...     def close(self):    # Called when all data has been parsed.
    ...         return self.maxDepth
    ...
    >>> target = MaxDepth()
    >>> parser = XMLParser(target=target)
    >>> exampleXml = """
    ... <a>
    ...   <b>
    ...   </b>
    ...   <b>
    ...     <c>
    ...       <d>
    ...       </d>
    ...     </c>
    ...   </b>
    ... </a>"""
    >>> parser.feed(exampleXml)
    >>> parser.close()
    4


.. rubric:: Footnotes

.. [#] The encoding string included in XML output should conform to the
   appropriate standards.  For example, "UTF-8" is valid, but "UTF8" is
   not.  See http://www.w3.org/TR/2006/REC-xml11-20060816/#NT-EncodingDecl
   and http://www.iana.org/assignments/character-sets.
