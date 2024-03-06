#define TIMER_LED_BLINK
#include "timer.h"
#include "button.h"
// LedBlink led1(13, 300);
LedBlink led1;
Button button1(A3, true);
void setup(){
    led1.init(13, 300);
    led1.enable();
}
void loop(){
    static int button1_state_change = 0;
    static unsigned long led_b_interval = 300;
    button1.start_service();
    if(button1.is_pushed()){
        if(led_b_interval == 300){
            led_b_interval = 500;
        }else{
            led_b_interval = 300;
        }
        led1.set_interval(led_b_interval);
    }
    LedBlink_execute();
}