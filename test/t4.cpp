#include<bits/stdc++.h>
using namespace std;
typedef void (*FunctionPointer)();
typedef bool (*FunctionPointer2)();

class EventListener{
    private:
        struct stored_function{
            FunctionPointer2 trigger;
            FunctionPointer dofunc;
            int timedelay;
        };
        stored_function *store=nullptr;
        int func_num=0;
    public:
        void add(FunctionPointer2 tri,FunctionPointer do_f,int td=1){
            stored_function t1;
            t1.trigger=tri;
            t1.dofunc=do_f;
            t1.timedelay=td;
            stored_function *t2=new stored_function[func_num+1];
            for(int a=0;a<func_num;a++){
                t2[a]=store[a];
            }
            t2[func_num]=t1;
            func_num++;
            delete[] store;
            store=new stored_function[func_num];
            for(int a=0;a<func_num;a++){
                store[a]=t2[a];
            }
            delete[] t2;
        }
        ~EventListener(){
            delete[] store;
        }
};
void f1(){
    cout<<"Function 1"<<endl;
}
void f2(){
    cout<<"Function 2"<<endl;
}
bool trigger(){
    return(now_time<max_time);
}
int now_time=0;
int max_time=10;
int main(){
    EventListener eventlistener;
    eventlistener.add(trigger,f1);
    eventlistener.add(trigger,f2);
}