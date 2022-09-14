/*
*
*   Copyright (c) 2022.7, ddddarcy
*
*   C++ Concurrency in Action 
*
*/
#include "Chap5.hpp"

namespace C5{
/*
    test 1
    atomic_flag
*/
//
void test_atomic_flag(){
    //只可以这样 初始化 不可以 atomic_flag f = true; 
    //atomic_flag 是最简单的 原子类型 此类对象 必须 用 ATOMIC_FLAG_INIT 进行初始化
    //而且 只可以 做 2件事 （2种状态） 设置 跟 清除 
    // ATOMIC_FLAG_INIT 初始化 对象 为 清除 状态
    atomic_flag f = ATOMIC_FLAG_INIT;
    cout <<"f 1 :" <<f.test_and_set() << endl;
    cout <<"f 2 :" <<f.test_and_set() << endl;
    f.clear();
    cout <<"f 3 :" <<f.test_and_set() << endl;
    cout <<"f 4 :" <<f.test_and_set() << endl;





}

void Chap5::test1(){
    test_atomic_flag();
}


// git pp
}