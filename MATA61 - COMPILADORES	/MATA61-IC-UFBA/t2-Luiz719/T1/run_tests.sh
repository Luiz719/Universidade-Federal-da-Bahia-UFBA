#!/bin/bash
# no parameter
# requires dirs: tests/inputs, tests/oracle, tests/outputs
# requires program "bminus" -- your lexer.

T1=$(pwd)
tests="$T1/tests"
inputs=/inputs/
outputs=/outputs/
oracle=/oracle/


# The function total_files reports a total number of files for a given directory. 
function total_files {
        find $1 -type f | wc -l
}

echo "T1 - 2023.1"
echo

# Build your B- lexer using the compile.sh script
echo "- Compiling bminus lexer ..."
$($T1/compile.sh)
echo "Done"
echo

# Then copy the executable file "bminus" to the tests folder.
cp "$T1/bminus" $tests

cd "$tests$inputs"
mytests=$(ls)
cd "$tests"

echo "- Running tests ..."
echo "Number of test cases: `total_files "$tests$inputs"`"

for t in $mytests; do
    name="$(basename $t .bm).out"
    echo "Running $t ..."
    ./bminus "$tests$inputs$t"  "$tests$outputs$name"
    n1=`diff -bB -iw "$tests$outputs$name" "$tests$oracle$name" | grep "^>" | wc -l`
    n2=`diff -bB -iw "$tests$outputs$name" "$tests$oracle$name" | grep "^<" | wc -l`
    if [[ $n1 -eq 0 ]] && [[ $n2 -eq 0 ]] ; then
        echo "OK"
    else
        echo "FAIL"
    fi
done

echo
echo "Done"

rm "$T1/bminus" 
cd "$T1"
