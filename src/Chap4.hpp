/*
*
*   Copyright (c) 2022.5, ddddarcy
*
*   C++ Concurrency in Action 
*
*/
#ifndef __CHAP4_H__
#define __CHAP4_H__
#include <queue>
#include <deque>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <future>
#include <utility>


namespace C4{

using namespace std;

class Chap4{

public:
    void test1();
    //thread safe queue
    void test2();

    //future
    void test3();

    //future async launch method
    void test4();

    //packaged_task 
    void test5();

    //promise
    void test6();

private:


};

}

#endif