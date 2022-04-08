#pragma once
#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <atomic>

using namespace std;

class timer
{
private:
    atomic<chrono::steady_clock::time_point> startT;
    chrono::steady_clock::time_point nowT, beginT;
    chrono::steady_clock::duration timeSpan;

    void calc();

public:
    void start();
    long long elapsedSec();
};

#endif