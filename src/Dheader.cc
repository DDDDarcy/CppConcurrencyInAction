/*
*
*   Copyright (c) 2022.5, ddddarcy
*
*   C++ Concurrency in Action 
*
*/
#include "Dheader.hpp"

#include <chrono>
#include <iostream>

namespace Dheader{

using namespace std;

extern void test_template();

void TestChrono::test_1(){
   // using mills = std::chrono::duration<double, std::ratio<1, 1000>>;
   // using us = std::chrono::duration<double, std::ratio<1, 1000000>>;

    //  mills s2(10);
    //std::chrono::duration<double, std::ratio<1,50>> s(5);

    //std::chrono::system_clock 类
    //获取时钟时间
    // std::chrono::system_clock::now();  获取当前时钟时间
    //chrono::system_clock::to_time_t(const time_point &__t);
    test_template();
}

void test0(){
    cout << " void " << endl;
}
int test1(){
    cout << "test1 " << endl;
    return 1;
}

int test2(int x){
    cout << " test 2" << endl;
    return x;
}

string test3(string s1, string s2){
    cout << s1 << "test3" << s2 << endl;
    return s1 + s2;
}



template<class Function, class... Args>
inline auto FuncWrapper(Function && f, Args && ... args) ->
decltype(f(std::forward<Args>(args)...))
{
    return f(std::forward<Args>(args)...);
}

void test_template(){
    FuncWrapper(test0);//

    FuncWrapper(test1);

    cout << FuncWrapper(test2, 2) << endl;

    cout << FuncWrapper(test3, "xxxx", "ddddd") << endl;
}

}