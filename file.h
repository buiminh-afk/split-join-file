#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

struct subfile
{
    string name = "";
    double size;
};

class file
{
private:
    string name;
    double sizeOfSubFile, sizeOfFile;
    int numberOfSubFile;
    vector<subfile *> subFileName;

public:
    bool found;
    file() = default;
    ~file() = default;
    file(string _name);
    void split();
    void join();
    friend string post(int, int, string);
};