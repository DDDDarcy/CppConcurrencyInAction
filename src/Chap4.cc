/*
*
*   Copyright (c) 2022.5, ddddarcy
*
*   C++ Concurrency in Action 
*
*/
#include "Chap4.hpp"


namespace C4{

/*
    test1
    code 4.1
*/
//std::condition_variable   只能结合 mutex 使用    一般首选
//std::condition_variable_any  可以和合适的 互斥量一起使用 需要更多开销  
std::mutex mut_test1;
std::queue<int> data_queue_test1;
std::condition_variable data_cond_test1;

void data_preparation_thread_test1(){
    int n = 0;
    while(n < 11000){
        int const data = n++;
        std::lock_guard<mutex> lock(mut_test1);
        data_queue_test1.push(data);
        data_cond_test1.notify_one();
    }
}
void data_processing_thread_test1(){
    while(true){
        std::unique_lock<mutex> lock(mut_test1);
        data_cond_test1.wait(
            lock,[]{return !data_queue_test1.empty(); }
        );
        int data = data_queue_test1.front(); 
        data_queue_test1.pop();
        lock.unlock();
        cout << "pop element : " << data_queue_test1.front() << endl;
        if(data > 10000)
            break;
    }
}

void Chap4::test1(){
    thread th1(data_preparation_thread_test1);
    thread th2(data_processing_thread_test1);

    th1.join();
    th2.join();
}



}