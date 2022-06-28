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

/*
*   test2
*   thread safe queue    
*   
*/

// code 4.4  
template<class T>
class threadsafe_queue_1{
private:
    std::mutex mut;
    queue<T> data_queue;
    condition_variable data_cond;
public:
    void push(T new_value){
        lock_guard<mutex> lk(mut);
        data_queue.push(new_value);
        data_cond.notify_one();
    }

    void wait_and_pop(T & value){
        unique_lock<mutex> lk(mut);
        data_cond.wait(lk,[this]{ return !data_queue.empty(); });
        value = data_queue.front();
        data_queue.pop();
    }

};

//  code 4.5
template<class T>
class threadsafe_queue_2{
private:
    mutable std::mutex mut;
    std::queue<T> data_queue;
    std::condition_variable data_cond;
public:
    threadsafe_queue_2(){}
    threadsafe_queue_2(threadsafe_queue_2 const & other){
        std::lock_guard<mutex> lk(mut);
        data_queue = other.data_queue;
    }
    void push(T new_value){
        std::lock_guard<mutex> lk(mut);
        data_queue.push(new_value);
        data_cond.notify_one();
    }
    void wait_and_pop(T & value){
        std::unique_lock<mutex> lk(mut);
        data_cond.wait(lk,[this]{ return !data_queue.empty(); });
        value = data_queue.front();
        data_queue.pop();
    }

    std::shared_ptr<T> wait_and_pop(){
        std::unique_lock<mutex> lk(mut);
        data_cond.wait(lk, [this]{ return !data_queue.empty(); });
        std::shared_ptr<T> res = make_shared<T>(data_queue.front());
        data_queue.pop();
        return res;
    }

    bool try_pop(T& value){
        lock_guard<mutex> lk(mut);
        if(data_queue.empty())
            return false;
        value = data_queue.front();
        data_queue.pop();
        return true;
    }

    shared_ptr<T> try_pop(){
        lock_guard<mutex> lk(mut);
        if(data_queue.empty())
            return shared_ptr<T>();
        shared_ptr<T> res = make_shared<T>(data_queue.front());
        data_queue.pop();
        return res;
    }

    bool empty() const {
        std::lock_guard<mutex> lk(mut);
        return data_queue.empty();
    }
};

void Chap4::test2(){

}

/*
    test3
    future
*/
int calculate_answer(){
    chrono::milliseconds ms(5000);
    this_thread::sleep_for(ms);
    return 10;
}

void do_anything(){
    chrono::milliseconds ms(500);
    while(1){
        this_thread::sleep_for(ms);
        cout << "i m do anything" << endl;
    }
}
void Chap4::test3(){ 
    future<int> answer = std::async(calculate_answer);
    thread t1(do_anything);
    //t1.detach();  函数 结尾加join 此处加join 后边打印无法得到执行
    cout << "ccc" << endl;
    cout << "my answer is : " << answer.get() << endl;
    t1.join();
}


}