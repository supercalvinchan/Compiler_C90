#!/bin/bash

if [[ "$1" != "" ]] ; then
    compiler="$1"
else
    compiler="bin/c_compiler"
fi

have_compiler=0
if [[ ! -f bin/c_compiler ]] ; then
    >&2 echo "Warning : cannot find compiler at path ${compiler}. Only checking C reference against python reference."
    have_compiler=1
fi

input_dir="final"

working="tmp/final"
mkdir -p ${working}

PASSED=0
CHECKED=0

for i in ${input_dir}/*.c ; do
    base=$(echo $i | sed -E -e "s|${input_dir}/([^.]+)[.]c|\1|g");

    # Compile the reference C version
    gcc $i -o $working/$base

    # Run the reference C version
    $working/$base
    REF_C_OUT=$?

    if [[ ${have_compiler} -eq 0 ]] ; then

        # Create the DUT python version by invoking the compiler with translation flags
        $compiler --translate $i -o ${working}/$base-got.py

        # Run the DUT python version
        python3 ${working}/$base-got.py
        GOT_P_OUT=$?
    fi

    if [[ ${have_compiler} -ne 0 ]] ; then
        echo "$base, Fail, No C compiler/translator"
    elif [[ $REF_C_OUT -ne $GOT_P_OUT ]] ; then
        echo "$base, Fail, Expected ${REF_C_OUT}, got ${GOT_P_OUT}"
    else
	PASSED=$((${PASSED}+1));
        echo "$base, Pass"
    fi
    CHECKED=$((${CHECKED}+1));

done
echo "========================="
echo "Passed ${PASSED} out of ${CHECKED}".