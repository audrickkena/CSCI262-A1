Name: Audrick Ken Ancheta Francisco
UOWID: 6748752

ALL FILES SUBMITTED ARE DECLARED MY WORK (WITH THE EXCEPTION OF THE MD5 IMPLEMENTATION FROM: http://www.zedwood.com/article/cpp-md5-function)

Reduction function formula used: r = H(password) modulo numOfPasswords, where H is the hashing algorithm (MD5).

Compilation and running instructions:
1) Ensure MINGW-w64 gcc is installed on windows machine (guide: https://www.msys2.org/) or mac/linux is able to run g++ in terminal/bash
2) Type 'g++ -std=c++11 *.cpp -o Rainbow' and hit enter to compile the project
3) Type '.\Rainbow {textfile here}' and hit enter to run the program