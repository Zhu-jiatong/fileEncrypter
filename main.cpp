#include <iostream>
#include <string>
#include <fstream>
#include <Thread>
#include <chrono>
#include <conio.h>
#include "libs\progressBar\progressBar.h"
#include "libs\timer\timer.h"
#include "libs\cursorTool\cursorTool.h"
progressBar encrypt;
timer myTimer;

using namespace std;

int key;
string rawPath, rawKey;
bool ready(false);
long float progress(0);
enum modes
{
    ENCR,
    DECR
} mode;

void fCipher(string file, int code);
void showBar();

int main(int argc, char *argv[])
{
    cout << "-----OPERATION_DETAILS-----" << "\n";
    rawPath = {argv[argc - 1]};
    cout << "INPUT_FILE_PATH: " << rawPath << endl;
    cout << "KEY: ", cin >> rawKey;
    key = stoi(rawKey);
    cout << "APPLIED_KEY: " << key << endl;
    thread t1(fCipher, rawPath, key);
    showBar();
    t1.join();
    curVisible(true);
    cout << "\n"
         << "\n"
         << "OPERATION_COMPLETE..."
         << "\n"
         << "PRESS_ANY_KEY_TO_EXIT..." << ends;
    getch();
    return 0;
}

void fCipher(string file, int code)
{
    char rawTemp;
    string outPath;
    if (file.substr(file.find_last_of("\\") + 1, file.length()).find("encrypted_") != file.npos)
    {
        mode = DECR;
        outPath = file.substr(0, file.find_last_of("\\") + 1) + file.substr(file.find_last_of("\\") + 1, file.length()).replace(file.substr(file.find_last_of("\\") + 1, file.length()).find("encrypted_"), 10, "");
    }
    else
    {
        mode = ENCR;
        outPath = file.substr(0, file.find_last_of("\\") + 1) + "encrypted_" + file.substr(file.find_last_of("\\") + 1, file.length());
    }
    cout << "OUTPUT_FILE_PATH: " << outPath << endl
         << "OPERATION_TYPE: " << ((mode == ENCR) ? "ENCRYPT_FILE" : "DECRYPT_FILE") << "\n"
         << endl;

    cout << "-----OPERATION_PROGRESS-----"
         << "\n";
    cout << "STARTING_OPERATION..."
         << "\n"
         << endl; // extra blank line reserved for progress bar complex

    ifstream fin(file, ios::binary);
    fin.seekg(0, fin.end);
    encrypt.max = fin.tellg();
    fin.seekg(0, fin.beg);

    ofstream fout(outPath, ios::binary);
    curVisible(false);
    myTimer.start();
    ready = true;
    while (fin.get(rawTemp))
    {
        int intTemp = (mode == ENCR) ? (int(rawTemp) - code) : (int(rawTemp) + code);
        fout.put((char)intTemp);
        progress = progress + 1;
    }
    fout.close();
    fin.close();
}

void showBar()
{
    while (!ready)
    {
    }
    while (progress < encrypt.max)
    {
        curMovY(1);
        encrypt.update(progress);
        cout << endl;
        auto rate = progress / myTimer.elapsedSec();
        auto tLeft = (encrypt.max - progress) / rate;
        int hLeft = tLeft / 3600;
        auto mLeft = ((long)tLeft % 3600) / 60;
        auto sLeft = ((long)tLeft % 3600) % 60;
        cout << progress << " / " << encrypt.max << "KB COMPLETED | "
             << "TIME_REMAINING: " << hLeft << "hrs " << mLeft << "mins " << sLeft << "secs"
             << " | SPEED: " << setprecision(1) << fixed << rate / 1000 << "KBps" << setw(1);
        this_thread::sleep_for(chrono::milliseconds(125));
    }
}
