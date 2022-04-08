#ifndef FILETOOL_H
#define FILETOOL_H

#include <fstream>
#include <string>
#include <atomic>
#include <thread>

extern std::thread th1;

using namespace std;

class fileTool
{
private:
    string finName, foutName;
    ifstream fin;
    ofstream fout;

    auto fnCipher(long code);

public:
    bool done{false};
    atomic<long long> progress{};

    fileTool(string &iName, string oName);
    long long getFinSize();
    void cipher(long code);
    auto quit();
};

#endif