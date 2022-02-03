#!/bin/bash

# Run the tests in all the databases
# The script is designed for a Trusty environment.
#
# The variables TEST_PAST, TEST_FUTURE, DONT_TEST_PRESENT can be used to test
# against unsupported Postgres versions and skip tests with supported ones.
#
# The variables TEST_VERBOSE enables verbose test log.
#
# The variables can be set in the travis configuration
# (https://travis-ci.org/psycopg/psycopg2/settings)

set -e -x

run_test () {
    VERSION=$1
    DBNAME=psycopg2_test
    if [[ -n "$TEST_VERBOSE" ]]; then
        VERBOSE=--verbose
    else
        VERBOSE=
    fi

    # Port number: 9.6 -> 50906
    port=$(( 50000 + $(echo $VERSION \
        | sed 's/\(.\+\)\.\(.\+\)/100 * \1 + \2/') ))

    printf "\n\nRunning tests against PostgreSQL $VERSION (port $port)\n\n"
    export PSYCOPG2_TESTDB=$DBNAME
    export PSYCOPG2_TESTDB_HOST=localhost
    export PSYCOPG2_TESTDB_PORT=$port
    export PSYCOPG2_TESTDB_USER=travis
    export PSYCOPG2_TEST_REPL_DSN=
    unset PSYCOPG2_TEST_GREEN
    python -c \
        "from psycopg2 import tests; tests.unittest.main(defaultTest='tests.test_suite')" \
        $VERBOSE

    printf "\n\nRunning tests against PostgreSQL $VERSION (green mode)\n\n"
    export PSYCOPG2_TEST_GREEN=1
    python -c \
        "from psycopg2 import tests; tests.unittest.main(defaultTest='tests.test_suite')" \
        $VERBOSE
}

# Postgres versions supported by Travis CI
if [[ -z "$DONT_TEST_PRESENT" ]]; then
    run_test 9.6
    run_test 9.5
    run_test 9.4
    run_test 9.3
    run_test 9.2
fi

# Unsupported postgres versions that we still support
# Images built by https://github.com/psycopg/psycopg2-wheels/tree/build-dinosaurs
if [[ -n "$TEST_PAST" ]]; then
    run_test 7.4
    run_test 8.0
    run_test 8.1
    run_test 8.2
    run_test 8.3
    run_test 8.4
    run_test 9.0
    run_test 9.1
fi

# Postgres built from master
if [[ -n "$TEST_FUTURE" ]]; then
    run_test 10.0
fi
