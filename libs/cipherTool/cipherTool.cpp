#include "cipherTool.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

void cipherTool::set(string file) // constructor
{
    // determine whether to ENcrypt or DEcrypt
    if (file.substr(file.find_last_of("\\") + 1, file.length()).find("encrypted_") != file.npos)
    {
        mode = DECR; // decrypt
        outPath = file.substr(0, file.find_last_of("\\") + 1) + file.substr(file.find_last_of("\\") + 1, file.length()).replace(file.substr(file.find_last_of("\\") + 1, file.length()).find("encrypted_"), 10, "");
    }
    else
    {
        mode = ENCR; // encrypt
        outPath = file.substr(0, file.find_last_of("\\") + 1) + "encrypted_" + file.substr(file.find_last_of("\\") + 1, file.length());
    }

    // open both files
    fin.open(file, ios::in | ios::binary);
    fout.open(outPath, ios::out | ios::binary);

    // get file size
    fin.seekg(0, fin.end);
    fSize = fin.tellg();
    fin.seekg(0, fin.beg);
}

void cipherTool::encrypt(string key)
{
    char charTemp;
    for (long long i(0); fin.get(charTemp); ++i)
    {
        charTemp += int(key[i % key.length()]);                      // caesar
        charTemp = charTemp ^ key[i % (sizeof(key) / sizeof(char))]; // XOR
        fout.put(charTemp);
        progress = i;
    }
}

void cipherTool::decrypt(string key)
{
    char charTemp;
    for (long long i(0); fin.get(charTemp); ++i)
    {
        charTemp = charTemp ^ key[i % (sizeof(key) / sizeof(char))]; // XOR
        charTemp -= int(key[i % key.length()]);                      // reverse caesar
        fout.put(charTemp);
        progress = i;
    }
}

void cipherTool::cipher(string key)
{
    ready = true;
    switch (mode)
    {
    case ENCR:
        encrypt(key);
        break;

    case DECR:
        decrypt(key);
        break;

    default:
        break;
    }
    fin.close();
    fout.close();
    done = true;
}