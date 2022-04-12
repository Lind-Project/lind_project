#TODO ideal: Check if Lind has coreutils/bash by file checks, if they're present; already installed, skip installing part.

echo "Installing bash..."
cd /home/lind/lind_project/src/scripts
./load_bash.sh
echo "Installing coreutils..."
cd /home/lind/lind_project/src/scripts
./load_coreutils.sh
cd /home/lind/lind_project/tests/test_cases/coreutils_suite

lindfs deltree "/script_tests/" &> /dev/null

deterministicscript=()
failarray=()
verbose=false
detfails=0

for var in "$@"; do
    case "$var" in
        -v)
            verbose=true;;
        -d)
            declare -n arglist='deterministicscript';;
        -*)
            echo "Invalid command line argument $var, usage: ./coreutils_suite.sh bashtests.txt (-v)"
            exit;;
        *)
            for arg in $(cat "$var"); do
                arglist+=("$arg");
            done;;
    esac;
done;

#Script to give them all chmod +x $var, so they can be executable.
chmod +x *.sh

error=0
echo ${arglist[@]}
echo ${deterministicscript[@]}
totalarray=("${arglist[@]}")

echo "Copying test cases..." #change


lindfs cp $PWD /script_tests/ &> /dev/null

mkdir script_tests
cp * script_tests/

echo "Executing deterministic test cases"
for var in "${arglist[@]}"; do
    echo "=================================================================="
    echo "Running test: $var"
    scriptfile="${var%.*}";
    echo $scriptfile
    exec 3>&1
    exec 1>&2
    lindoutput=$(lind /bin/bash "/script_tests/${scriptfile}.sh");
    regularoutput=$(./${scriptfile}.sh)
    exec 2>&3

    if [ "$verbose" = true ] ; then
        echo "Lind Output:"
        echo "$lindoutput"
        echo "------------------------------------------------------------------"
        echo "Regular Output:"
        echo "$regularoutput"
        echo "------------------------------------------------------------------"
        echo "Does lind output fit to regular output in script?"
    fi

    if [[ "$lindoutput" = "$regularoutput" ]]; then
        echo TEST PASSED;
    else
        echo TEST FAILED;
        error=1;
        detfails=$((detfails+1))
        failarray+=($var)
    fi;
done
echo "******************************************************************"

lindfs deltree "/script_tests/" &> /dev/null
rm -rf script_tests

if [  "$error" == 0 ]; then
    echo "All tests passed.";
else
    echo "Some tests have failed.";
    echo "$detfails deterministic tests and $nondetfails non-deterministic tests have failed."
    echo "Failed tests:"
    echo "${failarray[*]}"
fi;

exit $error