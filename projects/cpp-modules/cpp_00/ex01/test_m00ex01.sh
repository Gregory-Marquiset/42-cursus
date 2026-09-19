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
./phonebook << EOF > .output.txt 2>&1
EXIT
EOF
echo -n "Enter command: " > .expected.txt 2>&1
if diff -q .output.txt .expected.txt >> /dev/null 2>&1; then
    echo -e "\033[1;32mValide\033[0m"
    echo -e "\033[1;32mValide\033[0m" >> debug.txt
else
    echo -e "\033[1;33mOutput phonebook:\033[0m" >> debug.txt
    cat .output.txt >> debug.txt
    echo -e "\033[1;33mOutput expected:\033[0m" >> debug.txt
    cat .expected.txt >> debug.txt
    echo -e "\033[1;31mInvalide\033[0m"
    echo -e "\033[1;31mInvalide\n\033[0m" >> debug.txt
    all_tests_passed=false
fi

# Test 2
echo -e "\033[1;36mTest 2:\033[0m" >> debug.txt
echo -e "\033[1;36mTest 2:\033[0m"
./phonebook << EOF > .output.txt 2>&1
ADD
Gregory
Marquiset
Quardannault
07.71.69.27.25
Regrete d'avoir perdu des annees de vie sur Halo 3 et Dark souls.
SEARCH
1
EXIT
EOF
echo -n "Enter command: First name: Last name: \
Nickname: Phone number: Darkest secret: Enter command: \
     Index|First name| Last name|  Nickname|
--------------------------------------------
         1|   Gregory| Marquiset|Quardanna.|
         2|          |          |          |
         3|          |          |          |
         4|          |          |          |
         5|          |          |          |
         6|          |          |          |
         7|          |          |          |
         8|          |          |          |
Enter the index of the contact to view details (1-8): First name: Gregory
Last name: Marquiset
Nickname: Quardannault
Phone number: 07.71.69.27.25
Darkest secret: Regrete d'avoir perdu des annees de vie sur Halo 3 et Dark souls.
Enter command: " > .expected.txt 2>&1
if diff -q .output.txt .expected.txt >> /dev/null 2>&1; then
    echo -e "\033[1;32mValide\033[0m"
    echo -e "\033[1;32mValide\033[0m" >> debug.txt
else
    echo -e "\033[1;33mOutput phonebook:\033[0m" >> debug.txt
    cat .output.txt >> debug.txt
    echo -e "\033[1;33mOutput expected:\033[0m" >> debug.txt
    cat .expected.txt >> debug.txt
    echo -e "\033[1;31mInvalide\033[0m"
    echo -e "\033[1;31mInvalide\n\033[0m" >> debug.txt
    all_tests_passed=false
fi

# # Test 3
echo -e "\033[1;36mTest 3:\033[0m" >> debug.txt
echo -e "\033[1;36mTest 3:\033[0m"
./phonebook << EOF > .output.txt 2>&1
ADD
Gregory
Marquiset
Quardannault
07.71.69.27.25
Regrete d'avoir perdu des annees de vie sur Halo 3 et Dark souls.
ADD
Charles-louis
Dutel
WPMad
07.52.62.45.23
Ne sait pas faire un parse sans segfault.
ADD
Maxime
Torgue
Maxou2603
06.56.81.12.20 
Genre il boite mais en vrais il roule juste du cul.
ADD
David
Wayenborgh
22dewey22
06.55.91.11.73
Assume pas d'etre de droite.
ADD
Marie
Langlois
Maria
07.64.25.10.11
Choisi mal ces potes.
ADD
Garfi
Garfi
Garfi
Garfi
Garfi garfi garfi garfi.
ADD
Vincent
Fresnais
???
07.94.61.20.23
Probablement l'homme le plus beau du monde.
ADD
Laura
Nunez Torres
???
07.56.95.99.42
La meuf est bretonne, y parait. 
SEARCH
4
ADD
Xavier
Niel
Le xav
07.80.56.55.23
...
SEARCH
1
EXIT
EOF
echo -n "Enter command: First name: Last name: Nickname: Phone number: \
Darkest secret: Enter command: First name: Last name: Nickname: \
Phone number: Darkest secret: Enter command: First name: Last name: \
Nickname: Phone number: Darkest secret: Enter command: First name: \
Last name: Nickname: Phone number: Darkest secret: Enter command: \
First name: Last name: Nickname: Phone number: Darkest secret: \
Enter command: First name: Last name: Nickname: Phone number: \
Darkest secret: Enter command: First name: Last name: Nickname: \
Phone number: Darkest secret: Enter command: First name: Last name: \
Nickname: Phone number: Darkest secret: Enter command: \
     Index|First name| Last name|  Nickname|
--------------------------------------------
         1|   Gregory| Marquiset|Quardanna.|
         2|Charles-l.|     Dutel|     WPMad|
         3|    Maxime|    Torgue| Maxou2603|
         4|     David|Wayenborgh| 22dewey22|
         5|     Marie|  Langlois|     Maria|
         6|     Garfi|     Garfi|     Garfi|
         7|   Vincent|  Fresnais|       ???|
         8|     Laura|Nunez Tor.|       ???|
Enter the index of the contact to view details (1-8): First name: David
Last name: Wayenborgh
Nickname: 22dewey22
Phone number: 06.55.91.11.73
Darkest secret: Assume pas d'etre de droite.
Enter command: First name: Last name: Nickname: Phone number: \
Darkest secret: Enter command: \
     Index|First name| Last name|  Nickname|
--------------------------------------------
         1|    Xavier|      Niel|    Le xav|
         2|Charles-l.|     Dutel|     WPMad|
         3|    Maxime|    Torgue| Maxou2603|
         4|     David|Wayenborgh| 22dewey22|
         5|     Marie|  Langlois|     Maria|
         6|     Garfi|     Garfi|     Garfi|
         7|   Vincent|  Fresnais|       ???|
         8|     Laura|Nunez Tor.|       ???|
Enter the index of the contact to view details (1-8): First name: Xavier
Last name: Niel
Nickname: Le xav
Phone number: 07.80.56.55.23
Darkest secret: ...
Enter command: " > .expected.txt 2>&1
if diff -q .output.txt .expected.txt >> /dev/null 2>&1; then
    echo -e "\033[1;32mValide\033[0m"
    echo -e "\033[1;32mValide\033[0m" >> debug.txt
else
    echo -e "\033[1;33mOutput phonebook:\033[0m" >> debug.txt
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
./phonebook << EOF > .output.txt 2>&1
invalid
invalid
EOF
echo -n "Enter command: Command invalide.
Enter command: Command invalide.
Enter command: " > .expected.txt 2>&1
if diff -q .output.txt .expected.txt >> /dev/null 2>&1; then
    echo -e "\033[1;32mValide\033[0m"
    echo -e "\033[1;32mValide\033[0m" >> debug.txt
else
    echo -e "\033[1;33mOutput phonebook:\033[0m" >> debug.txt
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
./phonebook << EOF > .output.txt 2>&1
ADD
Gregory
EOF
echo -n "Enter command: First name: Last name: Nickname: \
Phone number: Darkest secret: Enter command: " > .expected.txt 2>&1
if diff -q .output.txt .expected.txt >> /dev/null 2>&1; then
    echo -e "\033[1;32mValide\033[0m"
    echo -e "\033[1;32mValide\033[0m" >> debug.txt
else
    echo -e "\033[1;33mOutput phonebook:\033[0m" >> debug.txt
    cat .output.txt >> debug.txt
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
valgrind --leak-check=full ./phonebook << EOF > .valgrind.txt 2>&1
EXIT
EOF
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
valgrind --leak-check=full ./phonebook << EOF > .valgrind.txt 2>&1
ADD
Gregory
Marquiset
Quardannault
07.71.69.27.25
Regrete d'avoir perdu des annees de vie sur Halo 3 et Dark souls.
SEARCH
1
EXIT
EOF
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
valgrind --leak-check=full ./phonebook << EOF > .valgrind.txt 2>&1
ADD
Gregory
Marquiset
Quardannault
07.71.69.27.25
Regrete d'avoir perdu des annees de vie sur Halo 3 et Dark souls.
ADD
Charles-louis
Dutel
WPMad
07.52.62.45.23
Ne sait pas faire un parse sans segfault.
ADD
Maxime
Torgue
Maxou2603
06.56.81.12.20 
Genre il boite mais en vrais il roule juste du cul.
ADD
David
Wayenborgh
22dewey22
06.55.91.11.73
Assume pas d'etre de droite.
ADD
Marie
Langlois
Maria
07.64.25.10.11
Choisi mal ces potes.
ADD
Garfi
Garfi
Garfi
Garfi
Garfi garfi garfi garfi.
ADD
Vincent
Fresnais
???
07.94.61.20.23
Probablement l'homme le plus beau du monde.
ADD
Laura
Nunez Torres
???
07.56.95.99.42
La meuf est bretonne, y parait. 
SEARCH
4
ADD
Xavier
Niel
Le xav
07.80.56.55.23
...
SEARCH
1
EXIT
EOF
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
valgrind --leak-check=full ./phonebook << EOF > .valgrind.txt 2>&1
invalid
invalid
EOF
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
valgrind --leak-check=full ./phonebook << EOF > .valgrind.txt 2>&1
ADD
Gregory
EOF
if grep -q "ERROR SUMMARY: 0 errors" .valgrind.txt; then
    echo -e "\033[1;32mValide\033[0m" >> debug.txt
    echo -e "\033[1;32mValide\033[0m"
else
    cat .valgrind.txt >> debug.txt
    echo -e "\033[1;31mInvalide\033[0m"
    echo -e "\033[1;31mInvalide\033[0m" >> debug.txt
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

rm -f .make.txt .expected.txt .valgrind.txt .output.txt

if $all_tests_passed; then
    rm -f debug.txt
    echo -e "\n\033[1;32mTous les tests sont valides.\033[0m"
else
    echo -e "\n\033[1;31mCertains tests ont échoué. Consultez debug.txt pour les détails.\033[0m"
fi