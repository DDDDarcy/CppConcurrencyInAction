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

//保护共享数据



}