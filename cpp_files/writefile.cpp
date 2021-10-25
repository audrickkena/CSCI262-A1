#include <iostream>
#include <fstream>

#include "password.h"

using namespace std;

void writefile(const vector<password*> &rainbow)
{
    ofstream outData;
    outData.open("Rainbow.txt");
    for(int i = 0; i < rainbow.size(); i++)
    {
        outData << (*rainbow.at(i)).getPassword() << "," << (*rainbow.at(i)).getFinalHash() << endl;
    }
    outData.close();
}