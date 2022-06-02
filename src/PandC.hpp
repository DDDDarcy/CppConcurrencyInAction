/*
*
*   Copyright (c) 2022.5, ddddarcy
*
*   C++ Concurrency in Action 
*
*/
#ifndef __PANDC_H__
#define __PANDC_H__

#include<vector>
#include<thread>
#include<condition_variable>
#include<mutex>
#include<queue>
#include<iostream>
#include<hashtable.h>

using namespace std;

class PandC{

public:
    PandC() = default;
    void test();

private:
    void Productor();
    void Consumer();

    mutex m_;
    queue<int> msgq_;
    condition_variable con_;



};

#endif
