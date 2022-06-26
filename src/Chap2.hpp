/*
*
*   Copyright (c) 2022.5, ddddarcy
*
*   C++ Concurrency in Action 
*
*/
// Chapter 2
#ifndef __CHAP2_H__
#define __CHAP2_H__

#include <iostream>
#include <vector>
#include <thread>
#include <memory>
#include <unistd.h>
#include <numeric>

namespace C2{
using namespace std;
class background_task{
public:
    int &_i;
    background_task(int &i):_i(i){
        cout << "_i : " << _i << endl;
    }
    void operator()() const{
        cout << "_i : " << _i << endl;
        do_thing();
        add_i();
    }
    void do_thing() const { cout << __FUNCTION__ << endl; }
    void add_i() const { 
        cout << __FUNCTION__ << endl;
        //sleep(1);
        for(int c = 0; c < 100000; ++c)_i++;
        
        cout << "FINISHED   i : " << _i << endl;
        
    }
};


class thread_guard{

    thread &_t;
public:

explicit thread_guard(thread& t) : _t(t)
    {};

    ~thread_guard(){
        if(_t.joinable()){
            _t.join();
            cout << "thread_guard success" << endl;
        }else{

            cout << "thread_guard faile" << endl;
        }
    }

    thread_guard(thread_guard const &) = delete;
    thread_guard& operator=(thread_guard const &) = delete;




};

class Chap2{

public:
    void test1();
    void test2();
    void test3();
    void test4();
    void test5();
    void test6();
    void test7(){}
    void test8();
    void test9();
   // void test10();


};



}



#endif