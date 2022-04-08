#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <iostream>
#include <iomanip>
#include <Windows.h>

using namespace std;

class progressBar
{
public:
	void update(long float val);

	int charNo{};
	unsigned long long max{};
};

#endif