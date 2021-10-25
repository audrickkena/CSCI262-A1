#include <string>
#include <vector>

#include "md5.h" 

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
};
