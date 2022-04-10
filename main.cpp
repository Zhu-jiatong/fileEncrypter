#include <iostream>
#include <iomanip>
#include <string>
#include <Thread>
#include <chrono>
#include <conio.h>
#include "libs\progressBar\progressBar.h"
#include "libs\timer\timer.h"
#include "libs\cursorTool\cursorTool.h"
#include "libs\cipherTool\cipherTool.h"
cipherTool myCipher;
progressBar encrypt;
timer myTimer;

using namespace std;

string rawPath, rawKey;

void fCipher(string file, string code);
void showBar();

int main(int argc, char *argv[])
{
     cout << "-----OPERATION_DETAILS-----\n";
     rawPath = {argv[argc - 1]};
     cout << "INPUT_FILE_PATH: " << rawPath << '\n';
     cout << "KEY: ", getline(cin, rawKey);
     cout << "APPLIED_KEY: [" << rawKey << "]" << '\n';
     thread t1(fCipher, rawPath, rawKey);
     showBar();
     t1.join();
     curVisible(true);
     cout << "\n\n"
          << "OPERATION_COMPLETE...\n"
          << "PRESS_ANY_KEY_TO_EXIT..." << ends;
     getch();
     return 0;
}

void fCipher(string file, string code)
{
     myCipher.set(file);
     encrypt.max = myCipher.fSize;
     cout << "OUTPUT_FILE_PATH: " << myCipher.outPath << '\n'
          << "OPERATION_TYPE: " << ((myCipher.mode == myCipher.ENCR) ? "ENCRYPT_FILE" : "DECRYPT_FILE") << "\n\n";

     cout << "-----OPERATION_PROGRESS-----\n"
          << "STARTING_OPERATION...\n\n";
     myTimer.start();
     myCipher.cipher(code);
}

void showBar()
{
     curVisible(false);
     while (!myCipher.ready)
     {
     }
     while (!myCipher.done)
     {
          curMovY(1);
          encrypt.update(myCipher.progress);
          auto rate = myCipher.progress / myTimer.elapsedSec();
          long tLeft = (encrypt.max - myCipher.progress) / rate;
          long hLeft = tLeft / 3600;
          int mLeft = ((long)tLeft % 3600) / 60;
          int sLeft = ((long)tLeft % 3600) % 60;
          cout << myCipher.progress / 1000 << " / " << encrypt.max / 1000 << "KBs COMPLETED | "
               << "TIME_REMAINING: " << hLeft << "hrs " << mLeft << "mins " << sLeft << "secs"
               << " | SPEED: " << setprecision(1) << fixed << rate / 1000 << "KBps" << ends;

          this_thread::sleep_for(chrono::milliseconds(150));
     }
}
