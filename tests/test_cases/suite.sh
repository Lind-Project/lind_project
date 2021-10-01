mkdir -p test_out
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
x86_64-nacl-gcc-4.4.3 hello.c -o test_out/hello -std=gnu99;
for var in "${totalarray[@]}"; do
    echo "Compiling test: $var"
    varnexe="${var%.*}.nexe";
    x86_64-nacl-gcc-4.4.3 $var -o test_out/$varnexe -std=gnu99 -lpthread;
    varnonexe="${var%.*}";
    gcc $var -o test_out/$varnonexe -lpthread
done
echo "Copying test cases"
lindfs cp $PWD/test_out/ /automated_tests/ &> /dev/null

echo "Executing deterministic test cases"
for var in "${deterministicinput[@]}"; do
    echo "------------------------------------------------------------------"
    echo "Running test: $var"
    nexefile="${var%.*}.nexe";
    varnonexe="${var%.*}";
    exec 3>&2
    exec 2> /dev/null
    lindoutput=$(lind "/automated_tests/$nexefile");
    regularoutput=$(./test_out/$varnonexe)
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
    regularoutput="$(./test_out/$varnonexe)";
    exec 2>&3

    if [ "$verbose" = true ] ; then
        echo "lindoutput:"
        echo "$lindoutput"
        echo "------------------------------------------------------------------"
        echo "regularoutput"
        echo "$regularoutput"
        echo "------------------------------------------------------------------"
        echo "Does lindoutput fit to regularoutput in script?"
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

rm ./test_out/* &> /dev/null
lindfs deltree "/automated_tests/" &> /dev/null

echo "------------------------------------------------------------------"

if [  "$error" == 0 ]; then
    echo "All tests passed.";
else 
    echo "Some tests have failed."; 
    echo "$detfails deterministic tests and $nondetfails non-deterministic tests have failed."
fi;

exit $error
