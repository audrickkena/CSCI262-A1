#include "password.h"

using namespace std;

password::password(string data)
{
    this->data = data;
    this->hash = md5(data);
}

// password::~password()
// {
// }