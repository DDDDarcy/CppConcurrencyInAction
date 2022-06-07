/*
*
*   Copyright (c) 2022.5, ddddarcy
*
*   C++ Concurrency in Action 
*
*/
#include <iostream>
#include <string>
#include <cstring>
#include <deque>
#include <memory>
#include <vector>
#include <functional>
#include <unistd.h>
//#include "Dheader.hpp"
#include "Chap2.hpp"
#include "Chap3.hpp"
#include "PandC.hpp"
#include "Chap4.hpp"

using namespace std;


template<typename T,typename... Args>
class SPointer
{
    SPointer(){

    }
    
};

class AA{
public:
    AA(int n) : _t(new int[n]), _n(n) { cout << "constructor " << endl; }

    AA(const AA& a) : _t(new int[a._n]), _n(a._n) { cout << "copy constructor" << endl; }

    AA(AA && a) : _t(a._t), _n(a._n) { a._t = nullptr; cout << "move constructor" << endl; }
    
    
    void operator ()(){
        cout << "wochi" << endl; 
        _func();
        _func1(_n);
    }

    void GetME(){ cout << _n << endl; }
    
    int * _t;
    int _n;
    void (*_func)();
    void (*_func1)(int a);

};



void test(){
    cout << "dasdgfdgfg" << endl;
}

void test(int a){
    cout << a << endl;
}


int testChap2(){
    using namespace C2;
    Chap2 test;
    test.test8();

    return 0;
}

int testChap3(){
    using namespace C3;

    Chap3 test;
    test.test3();
    return 0;
}

int testPandC(){
    PandC test;
    test.test();

    return 0;
}

int testChap4(){
    using namespace C4;
    Chap4 test;
    test.test1();
    return 0;
}

int main(){
    //SPointer<int , double , char, string> s;
   // using namespace Dheader;
    cout << "Hello world!" << endl;
    //TestChrono tes;
    //tes.test_1();
    /*
        test chapter 2
    */    
    //testChap2();

    //sleep(3);
    testChap3();
    //testPandC();
    //testChap4();
   


    //cout << "Hello" << endl;
   // AA t1(4);
    //AA t2(5);
    //AA t3(t2);
    //AA t4(std::move(t1));
    //AA t5(6);
   // AA t6(7);

    //int AA::*obj_ptr = &AA::_n;



    //业务程序员 修改的代码
   // t1._func = test;
   // t1._func1 = test;
    

    //vector<AA> arrays;
  //  cout << "FFFFFF-------------------------FFFFF" << endl;


    //cout << "t4 : " << &t4 << "    " << &(t4._n) << "    "<<(t4._t)<<endl;
    //cout << "t1 : " << &t1 << "    " << &(t1._n) << "    "<<(t1._t)<<endl;
    /*
        t4 : 0x7ffe466704f0    0x7ffe466704f8    0x18f5420
        t1 : 0x7ffe46670550    0x7ffe46670558    0
    */

    //arrays.push_back();
   // arrays.push_back(t1);
    //arrays.push_back(t2);
   // arrays.push_back(forward<AA>(t3));
    //arrays.emplace_back(t5);
   // arrays.emplace_back(forward<AA>(t6));

   // cout << "RRR----------------------RRR" << endl;
    
    /* deque<int> de;
    de.push_front(1);
    de.push_front(2);
    auto it = de.begin();
    de.push_front(3);
    cout << *it << "woote" <<endl;*/



    /*string s("Hello World");

    auto it = s.begin();

    //int i = 0; 
    while(it != s.end()){
        //cout << "wote   " <<*it << endl;
        if(*it == ' '){
            s.replace(it,it+1,"%20");
        }
        cout << "wote   " <<*it << endl;
        it++;
       // i++;
        //if(i > 12) break;
    }

    cout << s << endl;
    */

    return 0;
}