Frequently Asked Questions
==========================

.. sectionauthor:: Daniele Varrazzo <daniele.varrazzo@gmail.com>

Here are a few gotchas you may encounter using `psycopg2`.  Feel free to
suggest new entries!


.. _faq-transactions:

Problems with transactions handling
-----------------------------------

.. _faq-idle-in-transaction:
.. cssclass:: faq

Why does `!psycopg2` leave database sessions "idle in transaction"?
    Psycopg normally starts a new transaction the first time a query is
    executed, e.g. calling `cursor.execute()`, even if the command is a
    :sql:`SELECT`.  The transaction is not closed until an explicit
    `~connection.commit()` or `~connection.rollback()`.

    If you are writing a long-living program, you should probably make sure to
    call one of the transaction closing methods before leaving the connection
    unused for a long time (which may also be a few seconds, depending on the
    concurrency level in your database).  Alternatively you can use a
    connection in `~connection.autocommit` mode to avoid a new transaction to
    be started at the first command.


.. _faq-transaction-aborted:
.. cssclass:: faq

I receive the error *current transaction is aborted, commands ignored until end of transaction block* and can't do anything else!
    There was a problem *in the previous* command to the database, which
    resulted in an error.  The database will not recover automatically from
    this condition: you must run a `~connection.rollback()` before sending
    new commands to the session (if this seems too harsh, remember that
    PostgreSQL supports nested transactions using the |SAVEPOINT|_ command).

    .. |SAVEPOINT| replace:: :sql:`SAVEPOINT`
    .. _SAVEPOINT: http://www.postgresql.org/docs/current/static/sql-savepoint.html


.. _faq-transaction-aborted-multiprocess:
.. cssclass:: faq

Why do I get the error *current transaction is aborted, commands ignored until end of transaction block* when I use `!multiprocessing` (or any other forking system) and not when use `!threading`?
    Psycopg's connections can't be shared across processes (but are thread
    safe).  If you are forking the Python process make sure to create a new
    connection in each forked child. See :ref:`thread-safety` for further
    informations.


.. _faq-types:

Problems with type conversions
------------------------------

.. _faq-cant-adapt:
.. cssclass:: faq

Why does `!cursor.execute()` raise the exception *can't adapt*?
    Psycopg converts Python objects in a SQL string representation by looking
    at the object class.  The exception is raised when you are trying to pass
    as query parameter an object for which there is no adapter registered for
    its class.  See :ref:`adapting-new-types` for informations.


.. _faq-number-required:
.. cssclass:: faq

I can't pass an integer or a float parameter to my query: it says *a number is required*, but *it is* a number!
    In your query string, you always have to use ``%s``  placeholders,
    even when passing a number.  All Python objects are converted by Psycopg
    in their SQL representation, so they get passed to the query as strings.
    See :ref:`query-parameters`. ::

        >>> cur.execute("INSERT INTO numbers VALUES (%d)", (42,)) # WRONG
        >>> cur.execute("INSERT INTO numbers VALUES (%s)", (42,)) # correct


.. _faq-not-all-arguments-converted:
.. cssclass:: faq

I try to execute a query but it fails with the error *not all arguments converted during string formatting* (or *object does not support indexing*). Why?
    Psycopg always require positional arguments to be passed as a sequence, even
    when the query takes a single parameter.  And remember that to make a
    single item tuple in Python you need a comma!  See :ref:`query-parameters`.
    ::

        >>> cur.execute("INSERT INTO foo VALUES (%s)", "bar")    # WRONG
        >>> cur.execute("INSERT INTO foo VALUES (%s)", ("bar"))  # WRONG
        >>> cur.execute("INSERT INTO foo VALUES (%s)", ("bar",)) # correct
        >>> cur.execute("INSERT INTO foo VALUES (%s)", ["bar"])  # correct


.. _faq-unicode:
.. cssclass:: faq

My database is Unicode, but I receive all the strings as UTF-8 `!str`. Can I receive `!unicode` objects instead?
    The following magic formula will do the trick::

        psycopg2.extensions.register_type(psycopg2.extensions.UNICODE)
        psycopg2.extensions.register_type(psycopg2.extensions.UNICODEARRAY)

    See :ref:`unicode-handling` for the gory details.


.. _faq-float:
.. cssclass:: faq

Psycopg converts :sql:`decimal`\/\ :sql:`numeric` database types into Python `!Decimal` objects. Can I have `!float` instead?
    You can register a customized adapter for PostgreSQL decimal type::

        DEC2FLOAT = psycopg2.extensions.new_type(
            psycopg2.extensions.DECIMAL.values,
            'DEC2FLOAT',
            lambda value, curs: float(value) if value is not None else None)
        psycopg2.extensions.register_type(DEC2FLOAT)

    See :ref:`type-casting-from-sql-to-python` to read the relevant
    documentation. If you find `!psycopg2.extensions.DECIMAL` not available, use
    `!psycopg2._psycopg.DECIMAL` instead.


.. _faq-json-adapt:
.. cssclass:: faq

Psycopg automatically converts PostgreSQL :sql:`json` data into Python objects. How can I receive strings instead?
    The easiest way to avoid JSON parsing is to register a no-op function with
    `~psycopg2.extras.register_default_json()`::

        psycopg2.extras.register_default_json(loads=lambda x: x)

    See :ref:`adapt-json` for further details.


.. _faq-jsonb-adapt:
.. cssclass:: faq

Psycopg converts :sql:`json` values into Python objects but :sql:`jsonb` values are returned as strings. Can :sql:`jsonb` be converted automatically?
    Automatic conversion of :sql:`jsonb` values is supported from Psycopg
    release 2.5.4. For previous versions you can register the :sql:`json`
    typecaster on the :sql:`jsonb` oids (which are known and not suppsed to
    change in future PostgreSQL versions)::

        psycopg2.extras.register_json(oid=3802, array_oid=3807, globally=True)

    See :ref:`adapt-json` for further details.


.. _faq-identifier:
.. cssclass:: faq

How can I pass field/table names to a query?
    The arguments in the `~cursor.execute()` methods can only represent data
    to pass to the query: they cannot represent a table or field name::

        # This doesn't work
        cur.execute("insert into %s values (%s)", ["my_table", 42])

    If you want to build a query dynamically you can use the objects exposed
    by the `psycopg2.sql` module::

        cur.execute(
            sql.SQL("insert into %s values (%%s)") % [sql.Identifier("my_table")],
            [42])


.. _faq-bytea-9.0:
.. cssclass:: faq

Transferring binary data from PostgreSQL 9.0 doesn't work.
    PostgreSQL 9.0 uses by default `the "hex" format`__ to transfer
    :sql:`bytea` data: the format can't be parsed by the libpq 8.4 and
    earlier. The problem is solved in Psycopg 2.4.1, that uses its own parser
    for the :sql:`bytea` format. For previous Psycopg releases, three options
    to solve the problem are:

    - set the bytea_output__ parameter to ``escape`` in the server;
    - execute the database command ``SET bytea_output TO escape;`` in the
      session before reading binary data;
    - upgrade the libpq library on the client to at least 9.0.

    .. __: http://www.postgresql.org/docs/current/static/datatype-binary.html
    .. __: http://www.postgresql.org/docs/current/static/runtime-config-client.html#GUC-BYTEA-OUTPUT


.. _faq-array:
.. cssclass:: faq

Arrays of *TYPE* are not casted to list.
    Arrays are only casted to list when their oid is known, and an array
    typecaster is registered for them. If there is no typecaster, the array is
    returned unparsed from PostgreSQL (e.g. ``{a,b,c}``). It is easy to create
    a generic arrays typecaster, returning a list of array: an example is
    provided in the `~psycopg2.extensions.new_array_type()` documentation.


.. _faq-best-practices:

Best practices
--------------

.. _faq-reuse-cursors:
.. cssclass:: faq

When should I save and re-use a cursor as opposed to creating a new one as needed?
    Cursors are lightweight objects and creating lots of them should not pose
    any kind of problem. But note that cursors used to fetch result sets will
    cache the data and use memory in proportion to the result set size. Our
    suggestion is to almost always create a new cursor and dispose old ones as
    soon as the data is not required anymore (call `~cursor.close()` on
    them.) The only exception are tight loops where one usually use the same
    cursor for a whole bunch of :sql:`INSERT`\s or :sql:`UPDATE`\s.


.. _faq-reuse-connections:
.. cssclass:: faq

When should I save and re-use a connection as opposed to creating a new one as needed?
    Creating a connection can be slow (think of SSL over TCP) so the best
    practice is to create a single connection and keep it open as long as
    required. It is also good practice to rollback or commit frequently (even
    after a single :sql:`SELECT` statement) to make sure the backend is never
    left "idle in transaction".  See also `psycopg2.pool` for lightweight
    connection pooling.


.. _faq-named-cursors:
.. cssclass:: faq

What are the advantages or disadvantages of using named cursors?
    The only disadvantages is that they use up resources on the server and
    that there is a little overhead because a at least two queries (one to
    create the cursor and one to fetch the initial result set) are issued to
    the backend. The advantage is that data is fetched one chunk at a time:
    using small `~cursor.fetchmany()` values it is possible to use very
    little memory on the client and to skip or discard parts of the result set.


.. _faq-interrupt-query:
.. cssclass:: faq

How do I interrupt a long-running query in an interactive shell?
    Normally the interactive shell becomes unresponsive to :kbd:`Ctrl-C` when
    running a query. Using a connection in green mode allows Python to
    receive and handle the interrupt, although it may leave the connection
    broken, if the async callback doesn't handle the `!KeyboardInterrupt`
    correctly.

    Starting from psycopg 2.6.2, the `~psycopg2.extras.wait_select` callback
    can handle a :kbd:`Ctrl-C` correctly. For previous versions, you can use
    `this implementation`__.

    .. __: http://initd.org/psycopg/articles/2014/07/20/cancelling-postgresql-statements-python/

    .. code-block:: pycon

        >>> psycopg2.extensions.set_wait_callback(psycopg2.extras.wait_select)
        >>> cnn = psycopg2.connect('')
        >>> cur = cnn.cursor()
        >>> cur.execute("select pg_sleep(10)")
        ^C
        Traceback (most recent call last):
          File "<stdin>", line 1, in <module>
          QueryCanceledError: canceling statement due to user request

        >>> cnn.rollback()
        >>> # You can use the connection and cursor again from here


.. _faq-compile:

Problems compiling and deploying psycopg2
-----------------------------------------

.. _faq-python-h:
.. cssclass:: faq

I can't compile `!psycopg2`: the compiler says *error: Python.h: No such file or directory*. What am I missing?
    You need to install a Python development package: it is usually called
    ``python-dev``.


.. _faq-libpq-fe-h:
.. cssclass:: faq

I can't compile `!psycopg2`: the compiler says *error: libpq-fe.h: No such file or directory*. What am I missing?
    You need to install the development version of the libpq: the package is
    usually called ``libpq-dev``.


.. _faq-lo_truncate:
.. cssclass:: faq

`!psycopg2` raises `!ImportError` with message *_psycopg.so: undefined symbol: lo_truncate* when imported.
    This means that Psycopg was compiled with |lo_truncate|_ support (*i.e.*
    the libpq used at compile time was version >= 8.3) but at runtime an older
    libpq dynamic library is found.

    Fast-forward several years, if the message reports *undefined symbol:
    lo_truncate64* it means that Psycopg was built with large objects 64 bits
    API support (*i.e.* the libpq used at compile time was at least 9.3) but
    at runtime an older libpq dynamic library is found.

    You can use::

        $ ldd /path/to/packages/psycopg2/_psycopg.so | grep libpq

    to find what is the libpq dynamic library used at runtime.

    You can avoid the problem by using the same version of the
    :program:`pg_config` at install time and the libpq at runtime.

    .. |lo_truncate| replace:: `!lo_truncate()`
    .. _lo_truncate: http://www.postgresql.org/docs/current/static/lo-interfaces.html#LO-TRUNCATE


.. _faq-import-mod_wsgi:
.. cssclass:: faq

Psycopg raises *ImportError: cannot import name tz* on import in mod_wsgi / ASP, but it works fine otherwise.
    If `!psycopg2` is installed in an egg_ (e.g. because installed by
    :program:`easy_install`), the user running the program may be unable to
    write in the `eggs cache`__. Set the env variable
    :envvar:`PYTHON_EGG_CACHE` to a writable directory. With modwsgi you can
    use the WSGIPythonEggs__ directive.

    .. _egg: http://peak.telecommunity.com/DevCenter/PythonEggs
    .. __: http://stackoverflow.com/questions/2192323/what-is-the-python-egg-cache-python-egg-cache
    .. __: http://code.google.com/p/modwsgi/wiki/ConfigurationDirectives#WSGIPythonEggs

