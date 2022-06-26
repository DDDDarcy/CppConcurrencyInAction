/*
*
*   Copyright (c) 2022.5, ddddarcy
*
*   C++ Concurrency in Action 
*
*/
#include"Chap2.hpp"

namespace C2{
/*
    test1
*/
void do_some_work(){
    cout << __FUNCTION__ << endl;
}
void Chap2::test1(){
    thread mythread(do_some_work);

    int a = 0;
    background_task f(a);
    thread thread2(f);

    /*错误用法
        ||
        \/
    thread thread1(background_task(m));

    典型 错误用法 首先 background_task 是一个类 background_task() 是调用他的构造函数 生成一个
    临时对象
    这种 方式 相当于 声明了一个名为 thread1的函数 参数是 一个函数指针 
    这个函数指针 返回值为background_task 参数为空的 函数指针
    thread1 函数返回值为 thread
    相当于 
    thread thread1( 函数指针 ); 声明 
    */
    // 避免该问题 可以用以下操作
    // thread thread1( (background_task(m)) );  再加一个括号
    // thread thread1{ background_task(m) }; 用大括号
    // thread thread1( [](){ do_thing(); } ) 或者用lambda
    // 此处 可以面试 答 lambda 解决了什么问题  解决了线程 创建 需要临时变量的传参问题

    //thread 启动后 终止的话 std::thread的析构函数 会调用 std::terminate() 
   // int m = 0;
    //thread thread1((background_task(m)));
    mythread.join();
    thread2.join();
    cout << " a ::::: " << a << endl;
}


/*
    test2
*/
//P8
//
void Chap2::test2(){
    int n = 0;
    background_task f(n);
    thread t(f);

    thread_guard g(t);
    cout << __FUNCTION__ << " n : " << n << endl;
}

//分离线程 通常 称为守护线程
//这种线程特点 生命周期可能从应用程序 启动 到 结束
// 可能会在后台 监视 文件系统 也可能会缓存进行清理，亦或者 对数据结构进行优化
// detach 之后 分离的线程 说明 与 主线程 无任何关系了 并且 也无法汇入无法join

//并且 joinable() 返回 true 才可以 使用detach()

// 问题代码
/*
    void f(int i, string const & s);
    void oops(int some_param)
    {
        char buffer[1024];
        sprintf(buffer, "%i", some_param);
        thread(f,some_param, buffer);
        t.detach();
    }
    //这样写 buffer 这个指针变量 指向局部变量 传递到新线程中  但是 buffer 还没来得及转换成string  oops函数可能结束了
    // 导致buffer 悬空指针 未定义行为 无法保证隐式转化

    解决方案 thread(f, some_param, buffer); -----> thread(f, some_param, string(buffer));
*/



/*
    test3

*/
// 传递 非常量 引用
void update_data_fw(int id, int &data){
    data++;
    cout << "id : " << id << " data : " << data << " " << __FUNCTION__ << endl;
}
void Chap2::test3(){
    int id = 4;
    int data = 7;
    //thread t(update_data_fw, id, data); // 报错 编译
    //错误 提示 error: static assertion failed: std::thread arguments must be invocable after conversion to rvalues
    thread t(update_data_fw, id, std::ref(data));
    t.join();
    cout << "id : " << id << " data : " << data << " " << __FUNCTION__ << endl;
}
/*
    class X{
    public:
        void do_work();
        void do_int_work(int a);
    };
    int num = 0;
    X my_x;
    thread t(&X::do_work, &my_x); 第二个 参数 用 ref(my_x) 也可以
    thread t1(&X::do_int_work, &my_x, num);
*/



/*
    test4
*/
class X4{
public:
    void do_work(){cout << "X4" << __FUNCTION__ << endl;}
};

void Chap2::test4(){
    X4 my_x;
    thread t(&X4::do_work, ref(my_x));
    t.join();
    cout << " success " << __FUNCTION__ << endl;
}




/*
    test5
*/
class big_obj{
public:
    int * _p = nullptr;
    big_obj(){ _p = new int(3); }

    void prtf(){ cout << __FUNCTION__ <<"   P :::::  " << _p  << endl;}

    void prepare_data(int n){ if(_p) *_p = n; cout << __FUNCTION__ << " set *p : " << *_p << endl; }
};
void process_test5(std::unique_ptr<big_obj> obj){
    cout << __FUNCTION__ << "My test5 *p :::: " << *(obj->_p) << endl;
    cout << "LOG " << (obj->_p) << endl;
}

void Chap2::test5(){
    std::unique_ptr<big_obj> p(new big_obj);
    //p->prepare_data(6);
    cout << "LOG " << (p->_p) << endl;
    thread t(process_test5,std::move(p));
    //cout << "LOG " << (p->_p) << endl;
    t.join();
    cout << __FUNCTION__ << " finished " << endl;

    // obj 的所有权 先转给 thread 中的内部存储中 之后 再传递给 process_big_obj 函数

    //thread 的实例只能关联一个执行线程 具有 移动性 跟 不可复制性 可移动性 由开发者决定
}

/*
    test6 
*/
//std::ifstream std::unique_ptr std::thread 都是可移动的 但不可复制
void some_func(){
    while(1){
        cout << "invoke : " << __FUNCTION__ <<"  thread ID: " << this_thread::get_id() << endl;
        sleep(1);
    }
}

void some_other_func(){
    while(1){
        cout << "invoke : " << __FUNCTION__ <<"  thread ID: " << this_thread::get_id() << endl;
        sleep(1);
        
    }
}

void Chap2::test6(){
    thread t1(some_func);
    cout << " t1 t1 " << endl;
    sleep(3);

    thread t2(move(t1));
    cout << "move t1 ==> t2" << endl;
    sleep(4);

    t1 = thread(some_other_func);
    cout << "create other t1" << endl;
    sleep(4);

    thread t3;
    t3 = move(t2);
    cout << "t2 move ==> t3" << endl;
    sleep(3);

    //t1 = move(t3);//崩溃 t1 正在跑的线程 系统调用了 terminate()终止了 不抛出异常 （terminate 是 noexecept函数）
    //不能通过赋值形式 丢弃 线程  要么 显式的 等待线程结束 join 要么分离他 再 赋值形式的move  如下
    t1.detach();
    t1 = move(t3);
    cout << " t3 move ==> t1" << endl;

    sleep(5);

}

/*
    test7
*/
/*
//
thread fthread(){
    void fff();
    return thread(fff);
}

thread gf(){
    void some_f(int );
    thread t(some_f,42);
    return t;
}

void fthread( thread t);
//这里 可以传 析构函数 带join的 thread_guard 安全类
void gft(){
    void some_f();
    fthread(thread(some_f));
    thread t(some_f);
    fthread(move(t));

}
*/
/*
    test8
*/
//scoped_thread
class scoped_thread{
    thread _t;
public:
    explicit scoped_thread(thread t) : _t(move(t))
    {   
        //sleep(1);
        cout << " enter ---------" << t.joinable() << endl;
        if(!_t.joinable()){
            throw logic_error("No thread");
        }
    }

    ~scoped_thread()
    {
        _t.join();
    }
    scoped_thread(scoped_thread const &) = delete;
    scoped_thread& operator=(scoped_thread const &) = delete;
};

void Chap2::test8(){
    int m = 0;
    cout << "invoke " << __FUNCTION__ << endl;
    
    scoped_thread t((thread(background_task(m))));
    
    //sleep(3);
}

/*
    test9
*/
//joining_thread 实现
class joining_thread{
    thread _t;
public:
    joining_thread() noexcept = default;
    template<typename Callable, typename... Args>
    explicit joining_thread(Callable&& func, Args&& ... args):
        _t(std::forward<Callable>(func), forward<Args>(args)...)
    {}
    explicit joining_thread(std::thread t_) noexcept :
        _t(move(t_))
    {}
    joining_thread(joining_thread&& other) noexcept : 
        _t(move(other._t))
    {}
    joining_thread& operator=(joining_thread && other) noexcept 
    {
        if(joinable()){
            join();
        }
        _t = std::move(other._t);
        return *this;
    }
    joining_thread& operator=(std::thread && other) noexcept
    {
        if(joinable()){
            join();
        }
        _t = std::move(other);
        return *this;
    }

    ~joining_thread() noexcept{
        if(joinable())
            join();
    }

    //-----
    void swap(joining_thread& other) noexcept
    {
        _t.swap(other._t);
    }

    std::thread::id get_id() const noexcept{
        return _t.get_id();
    }

    bool joinable() const noexcept{
        return _t.joinable();
    }
    void join(){
        _t.join();
    }

    void detach(){
        _t.detach();
    }
    std::thread& as_thread() noexcept{
        return _t;
    }

    const std::thread & as_thread() const noexcept {
        return _t;
    }


};

void do_work_t9(unsigned id){
    cout << "ID : " <<id << __FUNCTION__ << endl;
}

void Chap2::test9(){
    std::vector<thread> threads;

    for(unsigned i = 0; i < 20; ++i){
        threads.emplace_back(do_work_t9,i);
    }

    for(auto& entry : threads )
        entry.join();
}

/*
    test10
*/

//确定线程数量
// 获取线程数量 在新版C++ 中 很重要
//在多核系统中 返回值 可以是 CPU 核心数量 返回值 也仅仅是个标识 无法获取时 函数返回0

//并行版 std::accumulate

template<typename Iterator, typename T>
struct accumulate_block
{
    void operator()(Iterator first, Iterator last, T &result){
        result = std::accumulate(first, last, result);
        
    }
};

template<class Iterator, class T>
T parallel_accumulate(Iterator first, Iterator last, T init){
    unsigned long const length = std::distance(first, last);

    if(!length) //1
        return init;
    unsigned long const min_per_thread = 25;
    unsigned long const max_threads = 
        (length + min_per_thread - 1)/min_per_thread;
    unsigned long const hardware_threads =
        std::thread::hardware_concurrency();

    unsigned long const num_threads = 
        std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
    
    unsigned long const block_size = length / num_threads;

    std::vector<T> results(num_threads);
    std::vector<std::thread> threads(num_threads - 1);

    Iterator block_start = first;
    for(unsigned long i = 0; i < (num_threads - 1); ++i){
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
        threads[i] = std::thread(
            accumulate_block<Iterator, T>(),
            block_start,std::ref(results[i])
        );
        block_start = block_end;
    }

    accumulate_block<Iterator, T>()(block_start, last, results[num_threads - 1]);

    for(auto & entry : threads)
        entry.join();

    return std::accumulate(results.begin(), results.end(), init);


}




}