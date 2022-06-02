#ifndef __HUMAN_H__
#define __HUMAN_H__

#include<functional>
#include<iostream>
#include<unistd.h>

namespace Hum{
using namespace std;

void HugePower(){
    cout << " i m very power" << endl;
}

void LessPower(){
    cout << " i m so poor power" << endl;
}

void AddKeys(){
    cout << " i have many keys" << endl;
}

void WenShen(){
    cout << " i m wen shen" << endl;
}

void eatshit(){
    cout << " eat shit" << endl;
}
extern void testHum();

//---
class Human{
public:
    void (*p)(void);

    using HandRcb = function<void(void)>;
    using HandLcb = function<void(void)>;
    using LegRcb = function<void(void)>;
    using LegLcb = function<void(void)>;
    using Dothing = function<void(void)>;


    //void testHum();
    Human(){}
    ~Human(){}

    void Run(){

        while(true){
            handRight_();
            handLeft_();
            Func_();
            LegRight_();
            LegLeft_();
            sleep(2);
        }
    }
    void setHandRightcb(HandRcb&& cb){
        handRight_ = cb;
    }
    void setHandLeftcb(HandLcb&& cb){
        handLeft_ = cb;
    } 
    void setLegRightcb(LegRcb&& cb){
        LegRight_ = cb;
    } 
    void setLegLeftcb(LegLcb&& cb){
        LegLeft_ = cb;
    }

    void setFunccb(Dothing && cb){
        Func_ = cb;
    }
private:
    HandRcb handRight_;
    HandLcb handLeft_;
    LegRcb LegRight_;
    LegLcb LegLeft_;
    Dothing Func_;


};


}
//---
#endif