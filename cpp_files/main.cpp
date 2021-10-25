#include <string>
#include <iostream>
#include <vector>

#include "readfile.h"
#include "password.h"
#include "reduction.h"

using namespace std;

void mainMenu(string passfile, vector<password> &passwords);
void reductionLoop(vector<password> &passwords, const int &startPos);

int main(int argc, char* argv[]) //argc stores number of command line arguments while argv[] is an array of char pointers of the arguments
{
    string passfile = argv[1]; //argv[1] is the first argument passed when running .\Rainbow {arg1,...} as argv[0] is reserved for the name of the executable
    vector<password> passwords;
    vector<password*> rainbow;
    mainMenu(passfile, passwords);
    return 0;
}

void mainMenu(string passfile, vector<password> &passwords, vector<password*> &rainbow)
{
    readfile(passfile, passwords);
    for(int i = 0; i < passwords.size(); i++)
    {
        password* currPass = &passwords.at(i);
        if((*currPass).getIsUsed() == false)
        {
            (*currPass).setIsUsed(true);
            reductionLoop(passwords, i);
            rainbow.push_back(currPass);
        }
    }
    sort(rainbow.begin(), rainbow.end(), rainbowSort);
    for(int i = 0; i < rainbow.size(); i++)
    {
        cout << "Rainbow elem " << i << ":" << endl;
        cout << " Password: " << (*(rainbow.at(i))).getPassword() << endl;
        cout << " final hash: " << (*(rainbow.at(i))).getFinalHash() << endl; 
    }
}

void reductionLoop(vector<password> &passwords, const int &startPos)
{
    string finalHash;
    int currPos = startPos;
    for(int j = 0; j < 4; j++)
    {
        password* currPass = &passwords.at(currPos);
        currPos = reduceHash((*currPass).getHash(), passwords.size());
        passwords.at(currPos).setIsUsed(true);
        finalHash = passwords.at(currPos).getHash();
    }
    passwords.at(startPos).setFinalHash(finalHash);
}

bool rainbowSort(password* p1, password* p2)
{
    return ((*p1).getFinalHash() < (*p2).getFinalHash()); 
}