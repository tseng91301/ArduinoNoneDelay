#include <stdlib.h>
typedef void (*TimerFunctionPointer)(void);

unsigned long time_u = 0;
unsigned long millis(){
    return time_u;
}

class Timer{
    protected:
        unsigned long nowtime;
        unsigned long interval;
        TimerFunctionPointer func;

        bool with_delay = false;
        unsigned long start_delay = 0;

        bool enabled = true;
    public:
        void TimerOnAdd(Timer *);
        Timer(TimerFunctionPointer func_in, unsigned long itv, unsigned long s_d = 0){
            func = func_in;
            interval = itv;
            start_delay = s_d;
            if(s_d > 0){
                with_delay = true;
            }
            TimerOnAdd(this); // Add this Timer object into the Timer pointer database
            return;
        }
        
        void enable(){
            enabled = true;
        }
        void disable(){
            enabled = false;
        }
        void set_interval(unsigned long inp){
            interval = inp;
            return;
        }
        void set_start_delay(unsigned long inp){
            start_delay = inp;
            return;
        }
        void start_service(){
            if(!enabled){
                return;
            }
            if(millis() < start_delay){
                return;
            }else if(millis() >= start_delay && with_delay == true){
                with_delay = false;
                nowtime = millis();
                func();
            }
            if(millis() - nowtime >= interval){
                nowtime = millis();
                func();
            }
        }
};


Timer **TotalTimers = (Timer **)malloc(0);
unsigned long TimersNum = 0;

void Timer::TimerOnAdd(Timer* inp){
    TimersNum += 1;
    TotalTimers = (Timer **)realloc(TotalTimers, TimersNum * sizeof(Timer *));
    TotalTimers[TimersNum-1] = inp;
}

void Timer_execute(){
    // Make all Timer object to be executed
    for(unsigned long a=0;a<TimersNum;a++){
        TotalTimers[a]->start_service();
    }
}

// For some Cpp program usage
void Timer_end(){
    free(TotalTimers);
    return;
}