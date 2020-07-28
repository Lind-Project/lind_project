
:mod:`symbol` --- Constants used with Python parse trees
========================================================

.. module:: symbol
   :synopsis: Constants representing internal nodes of the parse tree.
.. sectionauthor:: Fred L. Drake, Jr. <fdrake@acm.org>


This module provides constants which represent the numeric values of internal
nodes of the parse tree.  Unlike most Python constants, these use lower-case
names.  Refer to the file :file:`Grammar/Grammar` in the Python distribution for
the definitions of the names in the context of the language grammar.  The
specific numeric values which the names map to may change between Python
versions.

This module also provides one additional data object:


.. data:: sym_name

   Dictionary mapping the numeric values of the constants defined in this module
   back to name strings, allowing more human-readable representation of parse trees
   to be generated.


.. seealso::

   Module :mod:`parser`
      The second example for the :mod:`parser` module shows how to use the
      :mod:`symbol` module.

