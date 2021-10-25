#include <iostream>
#include <fstream>
#include <iomanip>

#include "readfile.h"
using namespace std;

void readfile(string filename, vector<password> &passwords)
{
    ifstream inData;
    inData.open(filename);
    string temp;

    while(getline(inData, temp))
    {
        password tempPass = password(temp);
        passwords.push_back(tempPass);
    }
    cout << passwords.size() << endl;
    inData.close();
}

void getPasswords(vector<password> &passwords)
{
    for(int i = 0; i < passwords.size(); i++)
    {
        cout << "Password at " << i + 1 << " is " << passwords.at(i).getPassword() << endl; 
        cout << " and the hash is: " << passwords.at(i).getHash() << endl;
        cout << " being isused set to: " << passwords.at(i).getIsUsed() << endl;
        cout << " with a final hash of: " << passwords.at(i).getFinalHash() << endl << endl << endl;
    }
}