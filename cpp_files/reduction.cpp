#include <cmath>
#include <cctype>
#include <string>

using namespace std;

long hashToLong(const string &hash);
long alphaToNum(const char &chr);

long reduceHash(const string &hash)
{
    unsigned long reduced;
    for(int i = 0; i < 4; i++)
    {
        reduced += hashToLong(hash.substr((i*8), 8));
    }
    return reduced;
}

long hashToLong(const string &hash)
{
    unsigned long result;
    for(int i = 0; i < hash.length(); i++)
    {
        long tempVal;
        if(isalpha(hash[i]))
        {
            tempVal = alphaToNum(hash[i]);
        }
        else
        {
            tempVal = hash[i] - '0';
        }
        tempVal *= pow(16, 7);
        result += tempVal;
    }
    return result;
}

long alphaToNum(const char &chr)
{
    return (chr - 'a') + 10;
} 