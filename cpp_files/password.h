#include <string>
#include <vector>

#include "md5.h" 
#ifndef PASSWORD
#define PASSWORD

using namespace std;

class password
{
private:
    string data;
    string hash;
    string finalHash;
    bool isUsed = false;
public:
    password(string data);
    password(){};
    // ~password();
    string getPassword();
    string getHash();
    string getFinalHash();
    bool getIsUsed();
    void setPassword(string data);
    void setHash(string hash);
    void setFinalHash(string finalHash);
    void setIsUsed(bool isUsed);
};
#endif 