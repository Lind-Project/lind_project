#TODO ideal: Check if Lind has coreutils/bash by file checks, if they're present; already installed, skip installing part.
BASE_DIR=$LIND_NATIVE_HOME

binoutput=$(lindfs ls bin/)
if [[ ${binoutput} != *"bin/bash"* ]];then
   echo "Installing bash..."
   cd $BASE_DIR/src/scripts/base
   ./compile_bash.sh
   ./load_bash.sh
fi
if [[ ${binoutput} != *"bin/ls"* ]];then
   echo "Installing coreutils..."
   cd $BASE_DIR/src/scripts/base
   ./compile_coreutils.sh
   ./load_coreutils.sh
fi

cd $BASE_DIR/tests/test_cases/coreutils_suite

lindfs deltree "/script_tests/" &> /dev/null

deterministicinput=()
nondeterministicinput=()
failarray=()
verbose=false
nondetfails=0
detfails=0

declare -n arglist='nondeterministicinput'
for var in "$@"; do
    case "$var" in
        -v)
            verbose=true;;
        -d)
            declare -n arglist='deterministicinput';;
        -*)
            echo "Invalid command line argument $var, usage: ./coreutils_suite.sh nondets.txt -d bashdets.txt (-v)"
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
echo ${deterministicinput[@]}
echo ${nondeterministicinput[@]}
totalarray=( "${deterministicinput[@]}" "${nondeterministicinput[@]}" )

echo "Copying test cases..." #change

lindfs cp $PWD /script_tests/ &> /dev/null

mkdir tempfolder
./prep.sh 

mkdir script_tests
cp * script_tests/

echo "Executing deterministic test cases"
for var in "${deterministicinput[@]}"; do
    echo "=================================================================="
    echo "Running test: $var"
    scriptfile="${var%.*}";
    echo $scriptfile
    exec 3>&1
    exec 1>&2
    lindoutput=$(lind /bin/bash "/script_tests/${scriptfile}.sh");
    regularoutput=$(./${scriptfile}.sh 2>&1)
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
echo "Executing nondeterministic test cases"
for var in "${nondeterministicinput[@]}"; do
    echo "=================================================================="
    echo "Running test: $var"
    scriptfile="${var%.*}";
    echo $scriptfile
    exec 3>&1
    exec 1>&2
    lindoutput=$(lind /bin/bash "/script_tests/${scriptfile}.sh");
    regularoutput=$(./${scriptfile}.sh 2>&1)
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

    python2 "${var%.*}.py" "$lindoutput" "$regularoutput"
    if [  "$?" == 0 ]; then
        echo TEST PASSED;
    else 
        echo TEST FAILED; 
        error=1;
        nondetfails=$((nondetfails+1))
        failarray+=($var)
    fi;
done


lindfs deltree "/script_tests/" &> /dev/null
rm -rf script_tests
rm -rf tempfolder

echo "******************************************************************"
if [  "$error" == 0 ]; then
    echo "All tests passed.";
else
    echo "Some tests have failed.";
    echo "$detfails deterministic tests and $nondetfails non-deterministic tests have failed."
    echo "Failed tests:"
    echo "${failarray[*]}"
fi;

exit $error
