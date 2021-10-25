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
    string finalHash="";
    bool isUsed = false;
    int pos;
public:
    password(string data, int pos);
    password(){};
    // ~password();
    string getPassword();
    string getHash();
    string getFinalHash();
    bool getIsUsed();
    int getPos();
    void setPassword(string data);
    void setHash(string hash);
    void setFinalHash(string finalHash);
    void setIsUsed(bool isUsed);
    void setPos(int pos);
};
#endif 