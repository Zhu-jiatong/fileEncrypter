#include <iostream>
#include <iomanip>
#include "ProgressBar.h"
using namespace std;

char loadIco[]{"|/-\\"};

void progressBar::update(long float val)
{
	++charNo;
	charNo = charNo >= 4 ? 0 : charNo;
	cout << "\r";

	float perc = (val / max) * 100;
	int intPerc = perc;
	cout << loadIco[charNo] << "[" << setw(intPerc) << setfill('#') << " " << setprecision(1) << fixed << perc << "%";
	cout << setw(100 - intPerc - 1) << setfill('-') << " ] \n";
}