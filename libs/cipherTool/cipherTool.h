#ifndef CIPHERTOOL_H
#define CIPHERTOOL_H

#include <fstream>
#include <string>

using namespace std;

class cipherTool
{
private:
    fstream fin, fout;
    string code;

public:
    string outPath;
    bool ready{false}, done{false};
    long long fSize{};
    long float progress{};
    enum modes
    {
        ENCR,
        DECR
    } mode;

    void set(string file);
    void cipher(string key);
    void encrypt(string key);
    void decrypt(string key);
};

#endif