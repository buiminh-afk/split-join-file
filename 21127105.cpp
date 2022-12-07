#include "file.h"
using namespace std;

int main()
{
    string inputFile;
    cout << "Enter name of the file you want to split : ";
    getline(cin, inputFile);
    file test(inputFile);
    test.split();
    test.join();
    return 0;
}