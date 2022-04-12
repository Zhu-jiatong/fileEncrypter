#include <iostream>
#include <iomanip>
#include "progressBar.h"
using namespace std;

char loadIco[]{"|/-\\"};

void progressBar::update(long float &val, long long time)
{
	++charNo;
	charNo = charNo >= 4 ? 0 : charNo;
	cout << "\r";

	float perc = (val / max) * 100;
	int intPerc = perc;
	cout << loadIco[charNo] << "[" << setw(intPerc) << setfill('#') << " " << setprecision(1) << fixed << perc << "%";
	cout << setw(100 - intPerc - 1) << setfill('-') << " ] \n";

	auto rate = val / time;
	long tLeft = (max - val) / rate;
	long hLeft = tLeft / 3600;
	int mLeft = ((long)tLeft % 3600) / 60;
	int sLeft = ((long)tLeft % 3600) % 60;
	cout << val / 1000 << " / " << max / 1000 << "KBs COMPLETED | "
		 << "TIME_REMAINING: " << hLeft << "hrs " << mLeft << "mins " << sLeft << "secs"
		 << " | SPEED: " << setprecision(1) << fixed << rate / 1000 << "KBps" << ends;
}