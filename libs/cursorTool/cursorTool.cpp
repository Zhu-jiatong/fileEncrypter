#include "cursorTool.h"
#include <Windows.h>
    const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cVisib;
    CONSOLE_SCREEN_BUFFER_INFO cBufInfo;


void getNow() // get current cursor status
{
    GetConsoleScreenBufferInfo(hOut, &cBufInfo);
    GetConsoleCursorInfo(hOut, &cVisib);
}

void curMovY(int unit) // unit +(ve) to go up, vice versa
{
    getNow();
    cBufInfo.dwCursorPosition.Y -= unit;
    SetConsoleCursorPosition(hOut, cBufInfo.dwCursorPosition);
}

void curVisible(bool isVisib) // isVisib (true) to show, vice versa
{
    getNow();
    cVisib.bVisible = isVisib;
    SetConsoleCursorInfo(hOut, &cVisib);
}