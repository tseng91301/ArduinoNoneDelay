#include<bits/stdc++.h>
#include "timer.h"
using namespace std;
void f1();
void f2();
Timer f1_start(f1, 100);
Timer f2_start(f2, 1000);
int main(){
    cout<<"There are two functions in this program,\n \
     f1 have the interval of 100 miliseconds,\n \
     f2 have the interval of 1000 miliseconds\n \
You can input time to contorl them (since real timer in CPP is very troublesome :( )"<<endl;
    while(1){
        cout<<"Input time (The input time must bigger than previous input time ! or type -1 to exit): ";
        long long time_u2;
        cin>>time_u2;
        if(time_u2 < 0){
            cout<<"Exit program <>"<<endl;
            Timer_end();
            break;
        }
        time_u = (unsigned long)time_u2;
        cout<<"Now time: "<<time_u<<endl;
        Timer_execute();
    }
    return 0;
}
void f1(){
    cout<<"'f1' is executed"<<endl;
}
void f2(){
    cout<<"'f2' is executed"<<endl;
}