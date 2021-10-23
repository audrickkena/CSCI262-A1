#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

void readfile(string filename, vector<string> &passwords)
{
    ifstream inData;
    inData.open(filename);
    string temp;

    while(getline(inData, temp))
    {
        passwords.push_back(temp);
    }
    cout << passwords.size() << endl;
    inData.close();
}

void getPasswords(vector<string> &passwords)
{
    for(int i = 0; i < passwords.size(); i++)
    {
        cout << "Password at " << i + 1 << " is " << passwords.at(i) << endl;
    }
}