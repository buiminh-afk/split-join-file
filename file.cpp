#include "file.h"

file::file(string _name)
{
    this->name = _name;
    ifstream fi(_name, ifstream::binary);
    if (fi.is_open())
    {
        found = true;
        // get size of the file
        fi.seekg(0, ifstream::end);
        this->sizeOfFile = fi.tellg();
        // enter size of sub file
        cout << "Enter the size(S) of the subfile in bytes: ";
        cin >> this->sizeOfSubFile;
        while (this->sizeOfSubFile > this->sizeOfFile)
        {
            cout << "Sub file must has size < " << this->sizeOfFile << endl;
            cout << "Enter again: ";
            cin >> this->sizeOfSubFile;
        }
        this->numberOfSubFile = ceil(this->sizeOfFile / this->sizeOfSubFile);
        // cout << this->numberOfSubFile << endl;
    }
    else
    {
        found = false;
        cout << "ERROR : Couldn't find your file";
    }
    fi.close();
}

string post(int index, int len, string name)
{
    string res = "";
    for (int i = 0; i < len - index; i++)
    {
        res += "0";
    }
    return "." + res + name;
}

void file::split()
{
    // create sub file name
    string subFname = "", postName = "", path = "folder/", src = "";
    char memBlock;
    streampos size;
    subfile *sub;
    int len = to_string(this->numberOfSubFile).length();
    ifstream fi(this->name, ios::binary | ios::in);
    for (int i = 0; i < this->numberOfSubFile; i++)
    {
        postName = post(to_string(i + 1).length(), len, to_string(i + 1));
        subFname = this->name + postName;
        sub = new subfile;
        sub->name = subFname;
        sub->size = (i + 1) * this->sizeOfSubFile > this->sizeOfFile ? this->sizeOfFile - i * this->sizeOfSubFile : this->sizeOfSubFile;
        this->subFileName.push_back(sub);
        // create sub file and copy the content from source file
        int countsize = 0;
        src = path + sub->name;
        ofstream fo(src, ios::out | ios::binary);
        while (!fi.eof() && countsize < sub->size)
        {
            fi.read(&memBlock, 1);
            fo << memBlock;
            countsize++;
        }
        fo.close();
    }
    cout << "Successfully split into " << this->numberOfSubFile << " subfiles" << endl;
    fi.close();
}

void file::join()
{
    string folder = "folder/", src = "", path = "";
    char *memBlock;
    cout << "Enter first piece name : ";
    cin >> src;
    while (src != this->subFileName[0]->name)
    {
        cout << "ERROR : Can not find your piece file !!!" << endl;
        cout << "Enter again : ";
        cin >> src;
    }

    // src exist
    stringstream ss(this->subFileName[0]->name);
    string outFname = "", duoiF = "";
    getline(ss, outFname, '.');
    getline(ss, duoiF, '.');
    outFname = outFname + "_copied." + duoiF;
    /////////////////////////////////////////////////
    ofstream fo(outFname, ios::binary | ios::out);
    for (int i = 0; i < this->numberOfSubFile; i++)
    {
        int size = this->subFileName[i]->size;
        memBlock = new char[size];
        path = folder + this->subFileName[i]->name;
        ifstream fi(path, ios::binary | ios::in);
        fi.read(memBlock, size);
        fo.write(memBlock, size);
        fi.close();
    }
    /////////////////////////////////////////////////
    fo.close();
}