#include "password.h"

using namespace std;

password::password(string data)
{
    this->data = data;
    this->hash = md5(data);
}

string password::getPassword()
{
    return this->data;
}

string password::getHash()
{
    return this->hash;
}

string password::getFinalHash()
{
    return this->finalHash;
}

bool password::getIsUsed()
{
    return this->isUsed;
}

void password::setPassword(string data)
{
    this->data = data;
}

void password::setHash(string hash)
{
    this->hash = hash;
}

void password::setFinalHash(string finalHash)
{
    this->finalHash = finalHash;
}

void password::setIsUsed(bool isUsed)
{
    this->isUsed = isUsed;
}

// password::~password()
// {
// }