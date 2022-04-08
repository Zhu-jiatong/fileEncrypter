#include <chrono>
#include "timer.h"

using namespace std;

void timer::start()
{
    startT = chrono::steady_clock::now();
}

void timer::calc()
{
    nowT = chrono::steady_clock::now();
    beginT = startT;
    timeSpan = nowT - beginT;
}

long long timer::elapsedSec(){
    calc();
    return chrono::duration_cast<chrono::seconds>(timeSpan).count();
}