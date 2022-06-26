/*
*
*   Copyright (c) 2022.5, ddddarcy
*
*   C++ Concurrency in Action 
*
*/
#include "PandC.hpp"





void PandC::Productor (){

    for(int i = 0; i < 10000; ++ i)
    {
        unique_lock<mutex> lock(m_);
        msgq_.push(i);
        cout  <<"线程 " << std::this_thread::get_id() << "  发送消息 " << i << endl;
        con_.notify_all();
    }
}

void PandC::Consumer (){
    while(true){
        unique_lock<mutex> lock(m_);

        con_.wait(lock,[&](){
            if(!msgq_.empty()){
                cout <<"线程 " << std::this_thread::get_id() <<"  处理消息: "<<msgq_.front() << endl;
                msgq_.pop();
                return true;
            }
            
            return false;
        }); 
    }
}


void PandC::test(){
    thread mainThread(&PandC::Productor,this);
    thread subThread1(&PandC::Consumer,this);
    thread subThread2(&PandC::Consumer,this);
    
    mainThread.join();
    subThread1.join();
    subThread2.join();
}