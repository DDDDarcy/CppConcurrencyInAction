/*
*
*   Copyright (c) 2022.5, ddddarcy
*
*   C++ Concurrency in Action 
*
*/
#ifndef __CHAP3_H__
#define __CHAP3_H__

#include <list>
#include <vector>
#include <mutex>
#include <algorithm>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <chrono>
#include <exception>
#include <memory>
#include <stack>




namespace C3{

using namespace std;




class tts{

    std::mutex mutex_;
    
    std::vector<int> lists_;

    std::vector<int>* plist;
public:
    tts(){
        for(int i  = 0; i < 10000000; i++)
            lists_.push_back(i);
        plist = &lists_;
    }

    void readlistfromlists_(){

        std::lock_guard<mutex> guard(mutex_);
        auto start = chrono::system_clock::now();

    
        for(auto x : lists_){
            //if(x % 100000 == 0){
                //cout << "lists_  " << x << endl; 
                //sleep(1);
                int d = x + 1;
                int c = d *2 +1;
            //}
                
            
        }
        chrono::duration<double> diff = chrono::system_clock::now() - start;
        cout << "elapsed : " << diff.count() << " seconds " << endl;
        cout << "finished " << endl;
        cout << "per second ins: " << 10000000.0 / diff.count() << endl;
    }  
    void readlistfromPlist_(){
        int n = 0;
        
       // for(; n < 100000; ++n)
            //cout << "P_list  "<<(*plist)[n]<< endl;
        //for(auto x : lists_){
           // cout << "Plist: " << x << endl;
        //}
    }  

};
class Chap3{
public:
    //3.1
    void test1(){ cout << "nothing " << endl; }
    void test2(){
        tts t;
        thread th1(&tts::readlistfromlists_, &t);
        thread th2(&tts::readlistfromPlist_, &t);
        th1.join();
        th2.join();
    }
    void test3();

};
}
#endif