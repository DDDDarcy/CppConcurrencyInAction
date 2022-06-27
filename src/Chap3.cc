/*
*
*   Copyright (c) 2022.5, ddddarcy
*
*   C++ Concurrency in Action 
*
*/
#include "Chap3.hpp"
#include<string>



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
        if(data.empty()) throw empyt_stack(); // check stack empty before stack pop

        std::shared_ptr<T> value = std::make_shared<T>(data.top());
        data.pop();
        return value;

    }

    void pop(T & value){
        std::lock_guard<mutex> lock(m);
        if(data.empty()) throw empyt_stack();

        value = data.top();
        data.pop();
    }

    bool empty() const {
        std::lock_guard<mutex> lock(m);
        return data.empty();
    }



};

#define LOOPN 10000
//test thread safe stack
void Chap3::test3(){

    threadsafe_stack<int> stack;
    std::vector<int> ves;

    mutex m;
    condition_variable con;

    int checkArray[LOOPN] = {0};
    vector<thread> pool;
    bool is_true = true;
    bool is_break = false;

    thread prd1([&](){
        for(int i = 0; i < LOOPN; ++ i)
            if(i % 2) {
                stack.push(i);
                //this_thread::sleep_for(std::chrono::duration<int, ratio<1,1>>(2));
                con.notify_all();
            }
    });
    pool.push_back(move(prd1));

    thread prd2([&](){
        for(int i = 0; i < LOOPN; ++ i)
            if( (i % 2) == 0 ) {
                stack.push(i);
                con.notify_all();
            }
    });
    pool.push_back(move(prd2));

    thread com1([&](){
        while(1){
            std::unique_lock<mutex> lock(m);
            con.wait(lock,[&]{ return (!stack.empty() || is_break);});
            
            //this_thread::sleep_for(std::chrono::duration<int, ratio<1,1>>(3));
            if(is_break) break;
            shared_ptr<int> value = stack.pop(); 
            cout << *value << endl;
            ves.push_back(*value);
        }        
    });
    pool.push_back(move(com1));

    thread com2([&](){
        while(1){
            std::unique_lock<mutex> lock(m);
            con.wait(lock,[&]{ return (!stack.empty() || is_break);});
            if(is_break) break;

            shared_ptr<int> value = stack.pop();
            cout << *value << endl;
            ves.push_back(*value);
        }        
    });
    pool.push_back(move(com2));

    for(auto &x : pool){
        x.detach();
    }

    cout << " t" << endl;
    sleep(2);
    

    for(auto &x : ves){
        checkArray[x] = 1;
    }

    //check 
    for(int i = 0; i < LOOPN; ++ i){
        if(checkArray[i] == 0) is_true = false;
    }

    if(is_true) {
        cout << "test success" << endl;
        is_break = true;
        //shut down com1/com2 thread
        con.notify_all();

    }
    else cout << "test false" << endl;


}
/*
------test 4 
    shared_lock shared_mutex;
*/
class dns_entry{
public:
    dns_entry():_data(4){};
    ~dns_entry(){cout << "destory " << endl;}
private:
    int _data;
};

class dns_cache{
    std::map<string, dns_entry> entries;
    mutable std::shared_mutex entry_mutex; // shared_mutex  read write mutex
public:
    dns_entry find_entry(string const& domain){
        std::shared_lock<shared_mutex> lk(entry_mutex);
        auto const it = entries.find(domain);

        return (it == entries.end()) ? dns_entry() : it->second;
        
    }
    void insert_entry(string const& domain, dns_entry&& entry){
        std::lock_guard<shared_mutex> lk(entry_mutex);
        entries.emplace(domain, forward<dns_entry>(entry));
    }
};

void test4dns(){
    dns_cache cache;
    cache.insert_entry("110", dns_entry());
    cache.insert_entry("120", dns_entry());
    cout << __FUNCTION__ << "   Hello " << endl;
}

static atomic<int> rwi = 0;
shared_mutex test4RWmutex;

void Writer(){
    for(int i = 0; i < 10; ++i){
        std::lock_guard<shared_mutex> lk(test4RWmutex);
        cout << "stop " << i << endl;
        chrono::milliseconds ms(1000);
        this_thread::sleep_for(ms);
    }

}
//无用示例  测试得 lock_guard 会阻塞  
//shared_lock  的两个 Read线程 会出现 诸如此类的以下情况  显然是 两个 Read线程 没有相互阻塞出现的情况
/*
999067   |   140162347513408
999068   |      |   140162347513408   这个地方
999069   |   140162347513408
........
999258   |   140162347513408
140162339120704                       这个地方
999260   |   140162347513408
*/
void Reader(){
    auto start = chrono::system_clock::now();

    while(rwi < 1000000){
        std::shared_lock<shared_mutex> lk(test4RWmutex);
        cout << rwi << "   |   " << this_thread::get_id() << endl;
        ++rwi;
    }

    auto end = chrono::system_clock::now() - start;
    cout << this_thread::get_id() << "  end time :  " << end.count() / 1000000000.0 << " second " << endl;
}

void Chap3::test4(){
    cout.sync_with_stdio(true);
    cout << __FUNCTION__ << " start " << endl;
    thread R1(Reader);
    thread R2(Reader);
    thread W(Writer);
    R1.join();
    R2.join();
    W.join();
    

}





}