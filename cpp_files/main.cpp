#include <string>
#include <iostream>
#include <vector>

#include "readfile.h"

using namespace std;

void mainMenu(string passfile, vector<string> passwords);

int main(int argc, char* argv[]) //argc stores number of command line arguments while argv[] is an array of char pointers of the arguments
{
    string passfile = argv[1]; //argv[1] is the first argument passed when running .\Rainbow {arg1,...} as argv[0] is reserved for the name of the executable
    vector<string> passwords;
    mainMenu(passfile, passwords);
    return 0;
}

void mainMenu(string passfile, vector<string> passwords)
{
    readfile(passfile, passwords);
    getPasswords(passwords);
}