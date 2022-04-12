#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <iostream>
#include <iomanip>

using namespace std;

class progressBar
{
public:
	void update(long float &val, long long time);

	int charNo{};
	long long max{};
};

#endif