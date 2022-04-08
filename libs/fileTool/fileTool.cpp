#include <string>
#include <fstream>
#include <thread>
#include "fileTool.h"

using namespace std;

fileTool::fileTool(string &iName, string oName)
{
    fin.open(iName, ios::binary);
    fout.open(oName, ios::binary);
}

long long fileTool::getFinSize()
{
    fin.seekg(0, fin.end);
    long long temp = fin.tellg();
    fin.seekg(0, fin.beg);
    return temp;
}

auto fileTool::quit()
{
    fin.close();
    fout.close();
    th1.join();
}

auto fileTool::fnCipher(long code)
{
    char rawTemp;
    int intTemp;
    while (fin.get(rawTemp))
    {
        intTemp = rawTemp;
        intTemp -= code;
        fout.put((char)intTemp);
        progress++;
    }
    quit();
    done = true;
}

void fileTool::cipher(long code)
{
    th1 = thread(&fnCipher, this, code);
}
