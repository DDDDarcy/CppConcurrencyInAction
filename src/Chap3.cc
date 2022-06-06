/*
*
*   Copyright (c) 2022.5, ddddarcy
*
*   C++ Concurrency in Action 
*
*/
#include "Chap3.hpp"

namespace C3{

/*
    test1
*/
std::list<int> some_list_test1;
std::mutex some_mutex_test1;

void add_to_list(int new_value)
{
    std::lock_guard<std::mutex> guard(some_mutex_test1);
    some_list_test1.push_back(new_value);
}

bool list_contains(int value_to_find)
{
    std::lock_guard<std::mutex> guard(some_mutex_test1);
    return std::find(some_list_test1.begin(), 
        some_list_test1.end(),
        value_to_find) != some_list_test1.end();
}
// C++17中模板 类型自动推导 std::lock_guard guard  <std::mutex> 可以不写
// C++17 还推出了一种加强版数据保护机制  std::scoped_lock
// 所以 std::lock_guard guard(some_mutex) ===> std::scoped_lock guard(some_mutex)



/*
    test3
*/
//线程安全堆栈
//保护共享数据    切勿将 受保护的数据引用或指针传递到互斥锁作用外部
struct empyt_stack : std::exception
{
    const char* what() const throw(){
        return "empty stack!";
    };
};

template<class T>
class threadsafe_stack
{
private:
    std::stack<T> data;
    mutable std::mutex m;
public:
    threadsafe_stack()
        :data(stack<T>()){}
    threadsafe_stack(const threadsafe_stack & other){
        std::lock_guard<mutex> lock(m);
        data = other.data;
    }

    threadsafe_stack& operator= (const threadsafe_stack&) = delete;

    void push(T newValue){
        std::lock_guard<mutex> lock(m);
        data.push(newValue);
    }

    std::shared_ptr<T> pop(){
        std::lock_guard<mutex> lock(m);
        if(!data.empty()) throw empyt_stack(); // check stack empty before stack pop

        std::shared_ptr<T> value = std::make_shared<T>(data.top());
        data.pop();
        return value;

    }

    void pop(T & value){
        std::lock_guard<mutex> lock(m);
        if(!data.empty()) throw empyt_stack();

        value = data.top();
        data.pop();
    }

    bool empty() const {
        std::lock_guard<mutex> lock(m);
        return data.empty();
    }



};

void test3(){

}




}