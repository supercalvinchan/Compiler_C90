#!/bin/bash

# Try to find a portable way of getting rid of
# any stray carriage returns
if which dos2unix ; then
    DOS2UNIX="dos2unix"
elif which fromdos ; then
    DOS2UNIX="fromdos"
else
    # This works on a GNU version of sed. I think this
    # will work in OSX as well, but don't have a machine
    # on which to test that. From reading the OSX docs,
    # it looks compatible.
    # The code \x0D is the ASCII code of carriage-return,
    # so it the regex should delete any CRs at the end of
    # a line (or anywhere in a line)
    DOS2UNIX="sed -e s/\x0D//g -"
    # Tested for combinations of:
    # - Ubuntu
    # - Cygwin
    # and inputs formats:
    # - LF
    # - CRLF
fi

echo "========================================"
echo " Cleaning the temporaries and outputs"
make clean
echo " Force building bin/c_translator "
make bin/c_compiler -B
if [[ "$?" -ne 0 ]]; then
    echo "Build failed.";
fi

if [[ -z "$1" ]]; then
    COMPILER=bin/c_compiler
else
    COMPILER=$1
fi

echo ""
echo "========================================"
echo " Testing compiler : ${COMPILER}"
echo ""

PASSED=0
CHECKED=0

mkdir -p working

for DRIVER in test_deliverable/testcases/*_driver.c ; do
    CHECKED=$(( CHECKED+1 ))
    NAME=$(basename $DRIVER _driver.c)
    TESTCODE=test_deliverable/testcases/$NAME.c

     printf "Test case %-15s :\t" $NAME

    # Compile driver with normal GCC
    mips-linux-gnu-gcc -c $DRIVER -o working/${NAME}_driver.o 2> working/${NAME}_driver.compile.stderr
    if [[ $? -ne 0 ]]; then
      echo "$?"
      printf "\e[1;31mError\e[0m : Couldn't compile driver program using GCC.\n"
      continue
    fi

    # Compile test function with compiler under test to assembly
    cat $TESTCODE | $COMPILER > working/$NAME.s  2> working/${NAME}.compile.stderr
    if [[ $? -ne 0 ]]; then
        echo "$?"
        printf "\e[1;31mError\e[0m : Compiler returned error message.\n"
        continue
    fi

    # Link driver object and assembly into executable
    mips-linux-gnu-gcc -static working/${NAME}.s working/${NAME}_driver.o -o working/${NAME}.elf 2> working/${NAME}.link.stderr
    if [[ $? -ne 0 ]]; then
        echo "$?"
        printf "\e[1;31mError\e[0m : Linker returned error message.\n"
        continue
    fi

    # Run the actual executable
    qemu-mips working/${NAME}.elf
    RESULT=$?

    if [[ "$RESULT" -ne 0 ]]; then
         printf "\e[1;31mError\e[0m : Testcase returned $RESULT, but expected 0.\n"
    continue
    fi

    printf "\e[1;32mPass\e[0m\n"
    PASSED=$(( PASSED+1 ))
    

RELEASE=$(lsb_release -d)
if [[ $? -ne 0 ]]; then
    echo ""
    echo "Warning: This appears not to be a Linux environment"
    echo "         Make sure you do a final run on a lab machine or an Ubuntu VM"
else
    grep -q "Ubuntu 16.04" <(echo $RELEASE)
    FOUND=$?

    if [[ $FOUND -ne 0 ]]; then
        echo ""
        echo "Warning: This appears not to be the target environment"
        echo "         Make sure you do a final run on a lab machine or an Ubuntu VM"
    fi
fi
done
