#ifndef CURSORTOOL_H
#define CURSORTOOL_H

#include <Windows.h>

using namespace std;

class cursorTool
{
private:
    const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cVisib;
    CONSOLE_SCREEN_BUFFER_INFO cBufInfo;

    void getNow();

public:
    void yAxisMov(int unit);
    void setVisibility(bool isVisib);
};

#endif