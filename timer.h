#ifndef TIMER_FDS34323
#define TIMER_FDS34323 1
#ifdef TIMER_N_SEPARATE
typedef void (*TimerFunctionPointer)(void);
class Timer{
    private: 
        struct FunctionDetail{
            TimerFunctionPointer func;
            int offset;
            int DelayTime;
            int TmpTime;
            int execute_num = 0;
        };
        int storeFunc_num = 0;
        FunctionDetail *storeFunc = (FunctionDetail*)malloc(storeFunc_num*sizeof(FunctionDetail));
        
    public: 
        void add(TimerFunctionPointer f_in, int delayTime = 1000, int offset = 0){
            storeFunc_num++;
            storeFunc = (FunctionDetail*)realloc(storeFunc, storeFunc_num*sizeof(FunctionDetail));
            FunctionDetail added;
            added.func = f_in;
            added.DelayTime = delayTime;
            added.TmpTime = millis();
            added.offset = offset;
            storeFunc[storeFunc_num-1] = added;
        }
        void execute(){
            for(int a=0;a<storeFunc_num;a++){
                int nowtime = millis();
                if(nowtime - storeFunc[a].TmpTime >= storeFunc[a].offset && storeFunc[a].execute_num==0){
                    storeFunc[a].TmpTime = nowtime;
                    storeFunc[a].func();
                    storeFunc[a].execute_num++;
                }
                if((nowtime - storeFunc[a].TmpTime >= storeFunc[a].DelayTime) && storeFunc[a].execute_num){
                    storeFunc[a].TmpTime = nowtime;
                    storeFunc[a].func();
                    storeFunc[a].execute_num++;
                }
            }
        }
        ~Timer(){
            free(storeFunc);
        }
};
#else
typedef void (*TimerFunctionPointer)(void);

unsigned long time_u = 0;

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
        Timer(){}
        Timer(TimerFunctionPointer func_in, unsigned long itv, unsigned long s_d = 0){
            init(func_in, itv, s_d);
        }
        void init(TimerFunctionPointer func_in, unsigned long itv, unsigned long s_d = 0){
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
#endif
#ifdef TIMER_LED_BLINK
class LedBlink{
    protected:
        int pin;
        unsigned long interval;
        bool enabled = false;

        int state = 0;
        unsigned long nowtime = millis();
    public:
        void LedBlinkOnAdd(LedBlink*);
        LedBlink(){}
        LedBlink(const int pin_in, unsigned long itv = 100){
            init(pin_in, itv);
            return;
        }
        void init(const int pin_in, unsigned long itv = 100){
            pinMode(pin_in, OUTPUT);
            pin = pin_in;
            if(itv <= 1){
                itv = 2;
            }
            interval = itv;
            LedBlinkOnAdd(this);
            return;
        }
        void set_interval(unsigned long inp){
            if(inp <= 1){
                inp = 2;
            }
            interval = inp;
        }

        void enable(){
            enabled = true;
        }
        void disable(){
            enabled = false;
        }
        void start_service(){
            if(!enabled){
                return;
            }
            if(millis() - nowtime >= interval/2){
                state = !state;
                nowtime = millis();
            }
            digitalWrite(pin, state);
        }
};
LedBlink **TotalLedBlinks = (LedBlink **)malloc(0);
unsigned long LedBlinksNum = 0;

void LedBlink::LedBlinkOnAdd(LedBlink *inp){
    LedBlinksNum += 1;
    TotalLedBlinks = (LedBlink **)realloc(TotalLedBlinks, LedBlinksNum * sizeof(LedBlink *));
    TotalLedBlinks[LedBlinksNum-1] = inp;
}

void LedBlink_execute(){
    // Make all LedBlink object to be executed
    for(unsigned long a=0;a<LedBlinksNum;a++){
        TotalLedBlinks[a]->start_service();
    }
}
void LedBlink_end(){
    free(TotalLedBlinks);
    return;
}
#endif
#endif