# C++ future wait 、get 源码解析

今天 测试async 时 

有一段这样的代码：

```C++
int asyn_test1(int a, int b){
    chrono::milliseconds ms(4000);
    cout << "start sleeping " << endl;
    this_thread::sleep_for(ms);  //4 seconds
    cout << "end slept" << endl;
    return a + b;
}

int asyn_test2(const int & a){

    return a;
}

//------------------
void test(){
    auto f1 = std::async(std::launch::async,asyn_test1,1,2);
    // 在新的线程上执行
    auto f2 = std::async(std::launch::deferred,asyn_test1,3,4);
    // 在 f2.wait()  or f2.get() 的时候执行
    auto f3 = std::async(std::launch::async | std::launch::deferred, asyn_test2, 4); 
    // 实现 默认执行方式
    chrono::milliseconds ms(200);
    auto start = chrono::system_clock::now();
    
    int c = f3.get();
    
    this_thread::sleep_for(ms); //200ms
    
    { //情况1
        cout << "f2 value : " << f2.get() << endl;
    	cout << "f1 value :" << f1.get() << endl;
    }
    { //情况2
        //cout << "f1 value :" << f1.get() << endl;
        //cout << "f2 value : " << f2.get() << endl;
    }
    
    
    cout << "f3 value : " << c <<endl;
    auto end = chrono::system_clock::now() - start;
    cout << "time cost : " << end.count() / 1000000000 << endl;
}
// 下面是 情况1 与 情况2 结果 
//情况1
/*
start sleeping              // 这里f1会休眠4秒  f1 对应的 线程打印的
f1 value :end slept
3
f2 value : start sleeping   // 这里f2也会休眠4秒 f2 对应的 线程打印的
end slept
7
f3 value : 4
time cost : 8               //花费 8 秒  变成了串行
*/
//--------------------------------------------------
// 情况2
/*
start sleeping 				// f1 线程
f2 value : start sleeping   // f2 线程 此时界面停留在这 4秒
end slept
end slept
7
f1 value :3
f3 value : 4
time cost : 4				//花费 4 秒 并发执行
*/

```

出于好奇，大概也能猜到是调用的join，所以便去追溯了一下源码确认。

###  1.首先是future 的get()

get() 在 future 头文件下 future类里，源码如下：

```c++
/// Retrieving the value
      _Res
      get()
      {
        typename _Base_type::_Reset __reset(*this);
        return std::move(this->_M_get_result()._M_value());
      }
```

这里并未能看出什么 ，但是仅有的函数调用 `_M_get_result()` 值得关注，`_M_value()` 应该是只获取数值，如果`_M_value()` 能够 调用我们的回调的话，那`_M_get_result()` 又去负责什么呢，所以大胆猜测关键 调用回调 还在`_M_get_result()`里。

### 2.追溯`_M_get_result()`

首先`_M_get_result()` 在 `__basic_future`类里，源码如下：

注释开头也表明了 `__basic_future`是 `future` 跟 `shared_future` 的公共部分实现

```c++
/// Common implementation for future and shared_future.
  template<typename _Res>
    class __basic_future : public __future_base
    {
    protected:
      typedef shared_ptr<_State_base>		__state_type;
      typedef __future_base::_Result<_Res>&	__result_type;

    private:
      __state_type 		_M_state;

    public: 
       	...
        ... //省略好多函数
        ...
        ...
	protected:
      /// Wait for the state to be ready and rethrow any stored exception
      __result_type
      _M_get_result() const
      {
        _State_base::_S_check(_M_state);
        _Result_base& __res = _M_state->wait(); // 找到了这个
        if (!(__res._M_error == 0))
          rethrow_exception(__res._M_error);
        return static_cast<__result_type>(__res);
      }
    }
```

### 3.追溯`wait()`以及`_M_state`成员变量的类型

从源码中一眼就锁定了`wait()`,这里肯定是跟线程`join`有关系了，但是我们还要关注调用`wait()`的`_M_state`是个什么东西，往下边看定义 改了几次命名：

```c++
//__basic_future 类定义里
protected:
      typedef shared_ptr<_State_base>		__state_type;
private:
      __state_type 		_M_state;
```

可以确定`_M_state` 是个`_State_base`的智能指针，那么 `_State_base`又是什么呢，接着往下看：

```c++
//在 future 头文件里 又有这么一行代码
using _State_base = _State_baseV2;
//我们继续查看_State_baseV2
 class _State_baseV2
    {
      ...
      ... //省略
      ...
_Result_base&
      wait()
      {
	// Run any deferred function or join any asynchronous thread:
	_M_complete_async();
	// Acquire MO makes sure this synchronizes with the thread that made
	// the future ready.
	_M_status._M_load_when_equal(_Status::__ready, memory_order_acquire);
	return *_M_result;
      }
 };
```

到这里 可以关注到 有`wait()`函数，可以确定 `_M_state->wait()` 就是调用的这个函数，`wait()` 函数 里`_M_complete_async()`值得关注，而且英文注释里也表明了，运行回调或者`join`的入口了

### 4.追溯`_M_complete_async()`

去看一下`_M_complete_async()`的实现：

```c++
  // Wait for completion of async function.
      virtual void _M_complete_async() { }
```

然后就发现是个虚函数，那就是用了多态机制了，我们就需要找到其派生类的实现了，`future`头文件找到如下：

```c++
// Shared state created by std::async().
  // Holds a deferred function and storage for its result.
  template<typename _BoundFn, typename _Res>
    class __future_base::_Deferred_state final
    : public __future_base::_State_base
    {
        // Run the deferred function.
      virtual void
      _M_complete_async()
      {
	// Multiple threads can call a waiting function on the future and
	// reach this point at the same time. The call_once in _M_set_result
	// ensures only the first one run the deferred function, stores the
	// result in _M_result, swaps that with the base _M_result and makes
	// the state ready. Tell _M_set_result to ignore failure so all later
	// calls do nothing.
        _M_set_result(_S_task_setter(_M_result, _M_fn), true);
      }
    }
```

上边这个 是 `deferred` 模式的`_M_complete_async()`实现，然而我们碰到的是`async`模式的,所以继续往下找：

```c++
 // Common functionality hoisted out of the _Async_state_impl template.
  class __future_base::_Async_state_commonV2
    : public __future_base::_State_base
  {
  protected:
  	// Make waiting functions block until the thread completes, as if joined.
    //
    // This function is used by wait() to satisfy the first requirement below
    // and by wait_for() / wait_until() to satisfy the second.
    //
    // [futures.async]:
    //
    // - a call to a waiting function on an asynchronous return object that
    // shares the shared state created by this async call shall block until
    // the associated thread has completed, as if joined, or else time out.
    //
    // - the associated thread completion synchronizes with the return from
    // the first function that successfully detects the ready status of the
    // shared state or with the return from the last function that releases
    // the shared state, whichever happens first.
    virtual void _M_complete_async() { _M_join(); }

    void _M_join() { std::call_once(_M_once, &thread::join, &_M_thread); }

    thread _M_thread;
    once_flag _M_once; 
  }
```

通过以上代码我们可以看出，`async`模式下的`_M_complete_async()`实现 只有`_M_join();`这一行代码

`_M_join()`的实现也在代码中，去调用的了标准库`thread`的`join`操作，同时我们也可以看到，`thread`类型的成员变量`_M_thread`，到此我们才真正搞到了`get()`的`join`操作。

以上源码均可在`future`头文件中找到。





