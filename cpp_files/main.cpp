#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ios> //used to get stream size
#include <limits> //used to get numeric limits
#include <regex> //used to get regex

#include "readfile.h"
#include "password.h"
#include "reduction.h"
#include "writefile.h"

using namespace std;

void mainMenu(const string &passfile, vector<password> &passwords, vector<password*> &rainbow);
void reductionLoop(vector<password> &passwords, const int &startPos);
bool rainbowSort(password* p1, password* p2);
int isHashInRainbow(const string &hashVal, const vector<password*> &rainbow);
int rainbowHashReduction(vector<password> &passwords, const int &startPos, string userHash);
int rainbowReduction(vector<password> &passwords, vector<password*> &rainbow, int rainbowPos, string userHash);
bool isUserHashValid(string &userHash);

int main(int argc, char* argv[]) //argc stores number of command line arguments while argv[] is an array of char pointers of the arguments
{
    string passfile = argv[1]; //argv[1] is the first argument passed when running .\Rainbow {arg1,...} as argv[0] is reserved for the name of the executable
    vector<password> passwords;
    vector<password*> rainbow;
    mainMenu(passfile, passwords, rainbow);
    return 0;
}

void mainMenu(const string &passfile, vector<password> &passwords, vector<password*> &rainbow)
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
    getPasswords(passwords); 
    // - for displaying all passwords

    sort(rainbow.begin(), rainbow.end(), rainbowSort);

    // for(int i = 0; i < rainbow.size(); i++)
    // {
    //     cout << "Rainbow elem " << i << ":" << endl;
    //     cout << " Password: " << (*(rainbow.at(i))).getPassword() << endl;
    //     cout << " final hash: " << (*(rainbow.at(i))).getFinalHash() << endl; 
    // } 
    // - for displaying all records in rainbow vector
    
    writefile(rainbow);
    string userHash;
    string userPreImage;
    cout << "Number of lines in Rainbow.txt: " << rainbow.size() << endl;
    cout << endl << endl << "Please enter a hash value to process: ";
    cin >> userHash;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer
    while(isUserHashValid(userHash) == false)
    {
        cout << "The hash value you entered is not valid. Please try again (Hash value): ";
        cin >> userHash;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer
    }
    int searchRes = isHashInRainbow(userHash, rainbow);
    int searchCount = 0;
    string tempHash = userHash;
    while(searchRes == -1 && searchCount < (passwords.size() * 10)) //if userHash is not in rainbow AND searchCount hasn't exceeded limit
    {
        tempHash = passwords.at(reduceHash(tempHash, passwords.size())).getHash();
        searchRes = isHashInRainbow(tempHash, rainbow);
        searchCount++;
    }
    if (searchRes != -1) //if the userHash or a reduction of it is found in rainbow table, find the preimage
    {
        int rainbowRes = rainbowReduction(passwords, rainbow, searchRes, userHash);
        if(rainbowRes != -1)
        {
            cout << "The preimage of the hash(" << userHash << ") is: " << passwords.at(rainbowRes).getPassword() << endl;
        }
        else
        {
            cout << "Sorry but the preimage of the hash(" << userHash << ") cannot be found." << endl;
        }
    }
    else //if the userHash or a reduction of it doesn't exist
    {
        cout << "Sorry, the rainbow table seems to have encountered an issue when the hash (" << userHash << ") is entered." << endl;
        cout << "This is most likely due to the rainbow table generation." << endl;
    }
}

void reductionLoop(vector<password> &passwords, const int &startPos)
{
    string finalHash;
    int currPos = startPos; //initiallise currPos to startPos 
    for(int j = 0; j < 4; j++)
    {
        password* currPass = &passwords.at(currPos); //get password at currPos
        currPos = reduceHash((*currPass).getHash(), passwords.size()); //getting the position of the new password after reduction of currPass hash
        passwords.at(currPos).setIsUsed(true); //setting the isUsed setting to true to indicate that password has been used for reduction
        finalHash = passwords.at(currPos).getHash(); //setting the temporary finalHash to the hash of the password with currPos in passwords vector
    }
    passwords.at(startPos).setFinalHash(finalHash); //setting the finalHash of a password to the result of the temporary finalHash after looping 4 times
}

bool rainbowSort(password* p1, password* p2)
{
    return ((*p1).getFinalHash() < (*p2).getFinalHash()); 
}

int isHashInRainbow(const string &hashVal, const vector<password*> &rainbow)
{
    for(int i = 0; i < rainbow.size(); i++)
    {
        password rainPass = *(rainbow.at(i));
        if(hashVal.compare(rainPass.getFinalHash()) == 0)
        {
            return i;
        }
    }
    return -1;
}

int rainbowHashReduction(vector<password> &passwords, const int &startPos, string userHash) //reduction of one entry in rainbow table, done when userhash is in rainbow table
{
    int currPos = startPos;
    for(int j = 0; j < 5; j++)
    {
        password* currPass = &passwords.at(currPos);
        if(userHash.compare((*currPass).getHash()) == 0) //if hash user entered same as hash of currPass
        {
            return currPos;
        }
        currPos = reduceHash((*currPass).getHash(), passwords.size());
    }
    return -1;
}

int rainbowReduction(vector<password> &passwords, vector<password*> &rainbow, int rainbowPos, string userHash) //manages reduction for the whole rainbow table
{
    int maxCount = rainbow.size(); //number of times the loop should execute, limited by size of the rainbow table
    int currCount = 0; //number of times the loop has executed
    while(currCount < maxCount)
    {
        if(rainbowPos == maxCount)
        {
            rainbowPos = 0;
        }
        int passPos = (*(rainbow.at(rainbowPos))).getPos();
        int reductionRes = rainbowHashReduction(passwords, passPos, userHash);
        if(reductionRes == -1)
        {
            currCount += 1;
            rainbowPos += 1;
        }
        else
        {
            return reductionRes;
        }
    }
    return -1;
}

bool isUserHashValid(string &userHash)
{
    string lowerHash;
    regex checkUpper("[A-Z]+");
    for(int i = 0; i < userHash.length(); i++)
    {
        if(regex_match(userHash.substr(i, 1), checkUpper))
        {
            lowerHash += tolower(userHash[i]);
        }
        else
        {
            lowerHash += userHash[i];
        }
    }
    userHash = lowerHash;
    regex strExpr("([a-f]|[0-9])+");
    if(regex_match(userHash, strExpr) && userHash.length() == 32)
    {
        return true;
    }
    return false;
}