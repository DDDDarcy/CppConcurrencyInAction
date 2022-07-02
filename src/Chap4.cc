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
/*
    async launch method
*/
int asyn_test1(int a, int b){

    return a + b;
}

int asyn_test2(const int & a){

    return a;
}

void Chap4::test4(){
    auto f1 = std::async(std::launch::async,asyn_test1,1,2);//在新的线程上执行
    auto f2 = std::async(std::launch::deferred,asyn_test1,3,4);// 在 f2.wait()  or f2.get() 的时候执行

    auto f3 = std::async(std::launch::async | std::launch::deferred, asyn_test2, 4); //实现 选择执行方式

}
/*
    test4();

    packaged_task<> 
    这里用书中 译者 总结的话 记录
    template<> 
    class packaged_task<std::string(std::vector<char>*,int)> 
    {
    public: 
        template<typename Callable> 
        explicit packaged_task(Callable&& f); 
        std::future<std::string> get_future(); 
        void operator()(std::vector<char>*,int); 
    };
    
    std::packaged_task 是个可调用对象，可以封装在 std::function 对象中，从而作为线程函数传递到 std::thread 对象中，或作为可调
    用对象传递到另一个函数中或直接调用。当 std::packaged_task 作为函数调用时，实参将由函数调用操作符传递至底层函数，并且返回值
    作为异步结果存储在 std::future 中，并且可通过get_future()获取。因此可以用 std::packaged_task 对任务进行打包，并适时的取回
    future。当异步任务需要返回值时，可以等待future状态变为“就绪”。
*/
std::mutex mut5;
std::deque<std::packaged_task<void()>> tasks;

bool gui_shutdown_msg_recv(){
    cout << "shutdown" << endl;
    return true;
}

void get_and_process_gui_msg(){
    cout << " get msg" << endl;
}

void gui_thread(){
    while(!gui_shutdown_msg_recv()){
        get_and_process_gui_msg();
        std::packaged_task<void()> task;

        {
            std::lock_guard<mutex> lk(mut5);
            if(tasks.empty())
                continue;
            task = std::move(tasks.front());
            tasks.pop_front();
        }

        task();
    }
}

template<typename Func>
std::future<void> post_task_for_gui_thread(Func f){
    std::packaged_task<void()> task(f);
    std::future<void> res = task.get_future();
    lock_guard<mutex> lk(mut5);
    tasks.push_back(move(task));
    return res;
}

void Chap4::test5(){

    thread th1(gui_thread);
}

/*
    test6 
    promise
*/
using ull = unsigned long long;
void findOdd(std::promise<ull> && OddSumPromise, ull start, ull end){
    ull OddSum = 0;
    for(ull i = start; i <= end; ++i){
        if (i & 1){
            OddSum += i;
        }
    }
    OddSumPromise.set_value(OddSum);
}


void Chap4::test6(){
    ull start = 0, end = 1900000000;
    
    std::promise<ull> OddSum;
    std::future<ull> OddFuture = OddSum.get_future();

    cout << "Thread Created !" << endl;
    std::thread t1(findOdd, std::move(OddSum), start, end);
    
    cout << "Waiting For Result !" << endl;

    cout << "OddSum : " << OddFuture.get() << endl;

    cout <<  "Completed !" << endl;

    t1.join();

}


}