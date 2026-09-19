#!/bin/bash

all_tests_passed=true

# ---------------------- Tests Makefile ----------------------
echo -e "\033[1;33mRunning Makefile commands...\033[0m"
echo -e "\033[1;33mRunning Makefile commands...\033[0m" > debug.txt

# Test make
echo -e "\033[1;36mRunning make...\033[0m"
echo -e "\033[1;36mRunning make...\033[0m" >> debug.txt
make > .make.txt 2>&1
if [ $? -ne 0 ]; then
    cat .make.txt >> debug.txt
    echo -e "\033[1;31mInvalide\033[0m"
    echo -e "\033[1;31mInvalide\n\033[0m" >> debug.txt
    all_tests_passed=false
else
    echo -e "\033[1;32mValide\033[0m"
    echo -e "\033[1;32mValide\033[0m" >> debug.txt
fi

# Test make clean
echo -e "\033[1;36mRunning make clean...\033[0m"
echo -e "\033[1;36mRunning make clean...\033[0m" >> debug.txt
make clean > .make.txt 2>&1
if [ $? -ne 0 ]; then
    cat .make.txt >> debug.txt
    echo -e "\033[1;31mInvalide\033[0m"
    echo -e "\033[1;31mInvalide\n\033[0m" >> debug.txt
    all_tests_passed=false
else
    echo -e "\033[1;32mValide\033[0m"
    echo -e "\033[1;32mValide\033[0m" >> debug.txt
fi

# Test make re
echo -e "\033[1;36mRunning make re...\033[0m"
echo -e "\033[1;36mRunning make re...\033[0m" >> debug.txt
make re > .make.txt 2>&1
if [ $? -ne 0 ]; then
    cat .make.txt >> debug.txt
    echo -e "\033[1;31mInvalide\033[0m"
    echo -e "\033[1;31mInvalide\n\033[0m" >> debug.txt
    all_tests_passed=false
else
    echo -e "\033[1;32mValide\033[0m"
    echo -e "\033[1;32mValide\033[0m" >> debug.txt
fi

# ---------------------- Tests exercice ----------------------
echo -e "\n\033[1;33m\nRunning tests...\033[0m" >> debug.txt
echo -e "\n\033[1;33mRunning tests...\033[0m"

# Test 1
echo -e "\033[1;36mTest 1:\033[0m" >> debug.txt
echo -e "\033[1;36mTest 1:\033[0m"
./ref > .output.txt 2>&1
A1=$(grep "Address of str:" .output.txt | awk '{print $4}')
A2=$(grep "Address of strptr:" .output.txt | awk '{print $4}')
A3=$(grep "Address of strref:" .output.txt | awk '{print $4}')
cat .output.txt | awk '{ if ($NF ~ /^0x[0-9a-fA-F]+$/) $NF=""; print }' | sed 's/  *$//' > .filtered_output.txt
cat << EOF > .expected.txt 2>&1
Adress of str:
Adress of strptr:
Adress of strref:

Value of str: HI THIS IS BRAIN
Value of strptr: HI THIS IS BRAIN
Value of strref: HI THIS IS BRAIN
EOF
if (diff -q .filtered_output.txt .expected.txt >> /dev/null 2>&1 && [ "$A1" == "$A2" ] && [ "$A1" == "$A3" ] ); then
    echo -e "\033[1;32mValide\033[0m"
    echo -e "\033[1;32mValide\033[0m" >> debug.txt
else
    echo -e "\033[1;33mOutput ref:\033[0m" >> debug.txt
    cat .filtered_output.txt >> debug.txt
    echo -e "\033[1;33mOutput expected:\033[0m" >> debug.txt
    cat .expected.txt >> debug.txt
    echo -e "\033[1;31mInvalide\033[0m"
    echo -e "\033[1;31mInvalide\n\033[0m" >> debug.txt
    all_tests_passed=false
fi

# ---------------------- Tests valgrind ----------------------
echo -e "\n\033[1;33mRunning valgrind...\033[0m"
echo -e "\n\033[1;33mRunning valgrind...\033[0m" >> debug.txt

# Valgrind Test 1
echo -e "\033[1;36mValgrind Test 1:\033[0m" >> debug.txt
echo -e "\033[1;36mValgrind Test 1:\033[0m"
valgrind --leak-check=full ./ref > .valgrind.txt 2>&1
if grep -q "ERROR SUMMARY: 0 errors" .valgrind.txt; then
    echo -e "\033[1;32mValide\033[0m" >> debug.txt
    echo -e "\033[1;32mValide\033[0m"
else
    cat .valgrind.txt >> debug.txt
    echo -e "\033[1;31mInvalide\033[0m"
    echo -e "\033[1;31mInvalide\n\033[0m" >> debug.txt
    all_tests_passed=false
fi

# ---------------------- Fin et netoyage ----------------------
echo -e "\n\033[1;33mRunning Makefile commands...\033[0m"
echo -e "\n\033[1;33mRunning Makefile commands...\033[0m" >> debug.txt
echo -e "\033[1;36mRunning make fclean...\033[0m"
echo -e "\033[1;36mRunning make fclean...\033[0m" >> debug.txt
make fclean > .make.txt 2>&1
if [ $? -ne 0 ]; then
    cat .make.txt >> debug.txt
    echo -e "\033[1;31mInvalide\033[0m"
    echo -e "\033[1;31mInvalide\033[0m" >> debug.txt
    all_tests_passed=false
else
    echo -e "\033[1;32mValide\033[0m"
    echo -e "\033[1;32mValide\033[0m" >> debug.txt
fi

rm -f .make.txt .expected.txt .valgrind.txt .output.txt .filtered_output.txt

if $all_tests_passed; then
    rm -f debug.txt
    echo -e "\n\033[1;32mTous les tests sont valides.\033[0m"
else
    echo -e "\n\033[1;31mCertains tests ont échoué. Consultez debug.txt pour les détails.\033[0m"
fi