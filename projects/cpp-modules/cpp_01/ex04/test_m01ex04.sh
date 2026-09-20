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

cat << EOF > .test.txt
The goal of these modules is to introduce you to Object-Oriented Programming.
This will be the starting point of your C++ journey. Many languages are recommended
to learn OOP. We decided to choose C++ since it’s derived from your old friend C.
Because this is a complex language, and in order to keep things simple, your code will
comply with the C++98 standard.
We are aware modern C++ is way different in a lot of aspects. So if you want to
become a proficient C++ developer, it’s up to you to go further after the 42 Common
Core!
EOF

# Test 1
echo -e "\033[1;36mTest 1:\033[0m" >> debug.txt
echo -e "\033[1;36mTest 1:\033[0m"
./sed .test.txt your my
cat << EOF > .expected.txt 2>&1
The goal of these modules is to introduce you to Object-Oriented Programming.
This will be the starting point of my C++ journey. Many languages are recommended
to learn OOP. We decided to choose C++ since it’s derived from my old friend C.
Because this is a complex language, and in order to keep things simple, my code will
comply with the C++98 standard.
We are aware modern C++ is way different in a lot of aspects. So if you want to
become a proficient C++ developer, it’s up to you to go further after the 42 Common
Core!
EOF
if (diff -q .expected.txt .test.txt.replace >> /dev/null 2>&1); then
    echo -e "\033[1;32mValide\033[0m"
    echo -e "\033[1;32mValide\033[0m" >> debug.txt
else
    echo -e "\033[1;33mOutput sed:\033[0m" >> debug.txt
    cat .test.txt.replace >> debug.txt
    echo -e "\033[1;33mOutput .expected:\033[0m" >> debug.txt
    cat .test.txt >> debug.txt
    echo -e "\033[1;31mInvalide\033[0m"
    echo -e "\033[1;31mInvalide\n\033[0m" >> debug.txt
    all_tests_passed=false
fi

# Test 2
echo -e "\033[1;36mTest 2:\033[0m" >> debug.txt
echo -e "\033[1;36mTest 2:\033[0m"
./sed .test.txt your > .output.txt 2>&1
cat << EOF > .expected.txt 2>&1
Usage: ./sed <filename> <s1> <s2>
EOF
if (diff -q .expected.txt .output.txt >> /dev/null 2>&1); then
    echo -e "\033[1;32mValide\033[0m"
    echo -e "\033[1;32mValide\033[0m" >> debug.txt
else
    echo -e "\033[1;33mOutput sed:\033[0m" >> debug.txt
    cat .output.txt >> debug.txt
    echo -e "\033[1;33mOutput expected:\033[0m" >> debug.txt
    cat .expected.txt >> debug.txt
    echo -e "\033[1;31mInvalide\033[0m"
    echo -e "\033[1;31mInvalide\n\033[0m" >> debug.txt
    all_tests_passed=false
fi

# Test 3
echo -e "\033[1;36mTest 3:\033[0m" >> debug.txt
echo -e "\033[1;36mTest 3:\033[0m"
./sed .test.txt your "" > .output.txt 2>&1
cat << EOF > .expected.txt 2>&1
Error : No empty string allow.
EOF
if (diff -q .expected.txt .output.txt >> /dev/null 2>&1); then
    echo -e "\033[1;32mValide\033[0m"
    echo -e "\033[1;32mValide\033[0m" >> debug.txt
else
    echo -e "\033[1;33mOutput sed:\033[0m" >> debug.txt
    cat .output.txt >> debug.txt
    echo -e "\033[1;33mOutput expected:\033[0m" >> debug.txt
    cat .expected.txt >> debug.txt
    echo -e "\033[1;31mInvalide\033[0m"
    echo -e "\033[1;31mInvalide\n\033[0m" >> debug.txt
    all_tests_passed=false
fi

# Test 4
echo -e "\033[1;36mTest 4:\033[0m" >> debug.txt
echo -e "\033[1;36mTest 4:\033[0m"
./sed .nofile.txt your my > .output.txt 2>&1
cat << EOF > .expected.txt 2>&1
Error : filename or right invalid for: .nofile.txt
EOF
if (diff -q .expected.txt .output.txt >> /dev/null 2>&1); then
    echo -e "\033[1;32mValide\033[0m"
    echo -e "\033[1;32mValide\033[0m" >> debug.txt
else
    echo -e "\033[1;33mOutput sed:\033[0m" >> debug.txt
    cat .output.txt >> debug.txt
    echo -e "\033[1;33mOutput expected:\033[0m" >> debug.txt
    cat .expected.txt >> debug.txt
    echo -e "\033[1;31mInvalide\033[0m"
    echo -e "\033[1;31mInvalide\n\033[0m" >> debug.txt
    all_tests_passed=false
fi

# Test 5
echo -e "\033[1;36mTest 5:\033[0m" >> debug.txt
echo -e "\033[1;36mTest 5:\033[0m"
./sed .test.txt absent my
cat << EOF > .expected.txt 2>&1
The goal of these modules is to introduce you to Object-Oriented Programming.
This will be the starting point of your C++ journey. Many languages are recommended
to learn OOP. We decided to choose C++ since it’s derived from your old friend C.
Because this is a complex language, and in order to keep things simple, your code will
comply with the C++98 standard.
We are aware modern C++ is way different in a lot of aspects. So if you want to
become a proficient C++ developer, it’s up to you to go further after the 42 Common
Core!
EOF
if (diff -q .expected.txt .test.txt.replace >> /dev/null 2>&1); then
    echo -e "\033[1;32mValide\033[0m"
    echo -e "\033[1;32mValide\033[0m" >> debug.txt
else
    echo -e "\033[1;33mOutput sed:\033[0m" >> debug.txt
    cat .test.txt.replace >> debug.txt
    echo -e "\033[1;33mOutput .expected:\033[0m" >> debug.txt
    cat .test.txt >> debug.txt
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
valgrind --leak-check=full ./sed .test.txt your my > .valgrind.txt 2>&1
if grep -q "ERROR SUMMARY: 0 errors" .valgrind.txt; then
    echo -e "\033[1;32mValide\033[0m" >> debug.txt
    echo -e "\033[1;32mValide\033[0m"
else
    cat .valgrind.txt >> debug.txt
    echo -e "\033[1;31mInvalide\033[0m"
    echo -e "\033[1;31mInvalide\n\033[0m" >> debug.txt
    all_tests_passed=false
fi

# Valgrind Test 2
echo -e "\033[1;36mValgrind Test 2:\033[0m" >> debug.txt
echo -e "\033[1;36mValgrind Test 2:\033[0m"
valgrind --leak-check=full ./sed .test.txt your > .valgrind.txt 2>&1
if grep -q "ERROR SUMMARY: 0 errors" .valgrind.txt; then
    echo -e "\033[1;32mValide\033[0m" >> debug.txt
    echo -e "\033[1;32mValide\033[0m"
else
    cat .valgrind.txt >> debug.txt
    echo -e "\033[1;31mInvalide\033[0m"
    echo -e "\033[1;31mInvalide\n\033[0m" >> debug.txt
    all_tests_passed=false
fi

# Valgrind Test 3
echo -e "\033[1;36mValgrind Test 3:\033[0m" >> debug.txt
echo -e "\033[1;36mValgrind Test 3:\033[0m"
valgrind --leak-check=full ./sed .test.txt your "" > .valgrind.txt 2>&1
if grep -q "ERROR SUMMARY: 0 errors" .valgrind.txt; then
    echo -e "\033[1;32mValide\033[0m" >> debug.txt
    echo -e "\033[1;32mValide\033[0m"
else
    cat .valgrind.txt >> debug.txt
    echo -e "\033[1;31mInvalide\033[0m"
    echo -e "\033[1;31mInvalide\n\033[0m" >> debug.txt
    all_tests_passed=false
fi

# Valgrind Test 4
echo -e "\033[1;36mValgrind Test 4:\033[0m" >> debug.txt
echo -e "\033[1;36mValgrind Test 4:\033[0m"
valgrind --leak-check=full ./sed .nofile.txt your my > .valgrind.txt 2>&1
if grep -q "ERROR SUMMARY: 0 errors" .valgrind.txt; then
    echo -e "\033[1;32mValide\033[0m" >> debug.txt
    echo -e "\033[1;32mValide\033[0m"
else
    cat .valgrind.txt >> debug.txt
    echo -e "\033[1;31mInvalide\033[0m"
    echo -e "\033[1;31mInvalide\n\033[0m" >> debug.txt
    all_tests_passed=false
fi

# Valgrind Test 5
echo -e "\033[1;36mValgrind Test 5:\033[0m" >> debug.txt
echo -e "\033[1;36mValgrind Test 5:\033[0m"
valgrind --leak-check=full ./sed .test.txt absent my > .valgrind.txt 2>&1
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

rm -f .make.txt .valgrind.txt .expected.txt .output.txt .test.txt .test.txt.replace

if $all_tests_passed; then
    rm -f debug.txt
    echo -e "\n\033[1;32mTous les tests sont valides.\033[0m"
else
    echo -e "\n\033[1;31mCertains tests ont échoué. Consultez debug.txt pour les détails.\033[0m"
fi