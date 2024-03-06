#ifndef BUTTON_TR2374
#define BUTTON_TR2374 1
class Button{
    protected:
        int pin;
        int state = 0;
        int state_change = 0;

        bool pushed = false;
    public:
        Button(){}
        Button(const int p, bool pull_up){
            init(p, pull_up);
        }
        void init(const int p, bool pull_up){
            if(pull_up){
                pinMode(p, INPUT_PULLUP);
            }else{
                pinMode(p, INPUT);
            }
            pin = p;
        }
        bool is_pushed(){
            if(pushed){
                pushed = false;
                return true;
            }else{
                return false;
            }
        }
        void start_service(){
            if(digitalRead(pin) != state){
                state = digitalRead(pin);
                state_change += 1;
                if(state_change % 2 == 0){
                    state_change = 0;
                    pushed = true;
                }
            }
        }
};
#endif