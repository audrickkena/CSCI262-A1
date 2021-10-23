#include <String>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) //argc stores number of command line arguments while argv[] is an array of char pointers of the arguments
{
    for (int i = 0; i < argc; ++i)
    {
        cout << argv[i] << "\n";
    }
    //argv[1] is the first argument passed when running .\Rainbow {arg1,...} as argv[0] is reserved for the name of the executable
    return 0;
}