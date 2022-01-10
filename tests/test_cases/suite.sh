mkdir -p automated_tests
deterministicinput=()
nondeterministicinput=()
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
            echo "Invalid command line argument $var"
            exit;;
        *)
            for arg in $(cat "$var"); do
                arglist+=("$arg");
            done;;
    esac;
done;

error=0
echo ${deterministicinput[@]}
echo ${nondeterministicinput[@]}
totalarray=( "${deterministicinput[@]}" "${nondeterministicinput[@]}" )
echo "Compiling test cases"

for var in "${totalarray[@]}"; do
    echo "Compiling test: $var"
    varnexe="${var%.*}.nexe";
    x86_64-nacl-gcc-4.4.3 $var -o automated_tests/$varnexe -std=gnu99 -lpthread;
    varnonexe="${var%.*}";
    gcc $var -o automated_tests/$varnonexe -lpthread
done
echo "Copying test cases"
lindfs cp $PWD/automated_tests/ /automated_tests/ &> /dev/null
lindfs cp $PWD/testfile.txt /testfile.txt &> /dev/null # Copies the text file to be used in several test files.

echo "Executing deterministic test cases"
for var in "${deterministicinput[@]}"; do
    echo "------------------------------------------------------------------"
    echo "Running test: $var"
    nexefile="${var%.*}.nexe";
    varnonexe="${var%.*}";
    exec 3>&2
    exec 2> /dev/null
    lindoutput=$(lind "/automated_tests/$nexefile");
    regularoutput=$(./automated_tests/$varnonexe)
    exec 2>&3

    if [ "$verbose" = true ] ; then
        echo "lindoutput"
        echo "$lindoutput"
        echo "regularoutput"
        echo "$regularoutput"
        echo "Does lindoutput == regularoutput?"
    fi

    if [[ "$lindoutput" = "$regularoutput" ]]; then
        echo TEST PASSED;
    else 
        echo TEST FAILED; 
        error=1;
        detfails=$((detfails+1))
    fi;
done
echo "------------------------------------------------------------------"
echo "Executing nondeterministic test cases"
for var in "${nondeterministicinput[@]}"; do
    echo "------------------------------------------------------------------"
    echo "Running test: $var"

    nexefile="${var%.*}.nexe";
    varnonexe="${var%.*}";
    exec 3>&2
    exec 2> /dev/null
    lindoutput="$(lind "/automated_tests/$nexefile")";
    regularoutput="$(./automated_tests/$varnonexe)";
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

    fi;
done

rm ./automated_tests/* &> /dev/null
lindfs deltree "/automated_tests/" &> /dev/null
lindfs rm "/testfile.txt" &> /dev/null

echo "------------------------------------------------------------------"

if [  "$error" == 0 ]; then
    echo "All tests passed.";
else 
    echo "Some tests have failed."; 
    echo "$detfails deterministic tests and $nondetfails non-deterministic tests have failed."
fi;

exit $error
