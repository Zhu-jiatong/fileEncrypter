#include "cursorTool.h"
#include <Windows.h>

void cursorTool::getNow() // get current cursor status
{
    GetConsoleScreenBufferInfo(hOut, &cBufInfo);
    GetConsoleCursorInfo(hOut, &cVisib);
}

void cursorTool::yAxisMov(int unit) // unit +(ve) to go up, vice versa
{
    getNow();
    cBufInfo.dwCursorPosition.Y -= unit;
    SetConsoleCursorPosition(hOut, cBufInfo.dwCursorPosition);
}

void cursorTool::setVisibility(bool isVisib) // isVisib (true) to show, vice versa
{
    getNow();
    cVisib.bVisible = isVisib;
    SetConsoleCursorInfo(hOut, &cVisib);
}