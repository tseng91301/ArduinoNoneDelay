int now_time = 0;
int max_time = 10;
class EventListener {
private:
    struct stored_function {
        bool (*trigger)();
        void (*dofunc)();
        unsigned long last_execution_time;
        int timedelay;
    };

public:
    void add(bool (*tri)(), void (*do_f)(), int td = 1000) {
        stored_function t1;
        t1.trigger = tri;
        t1.dofunc = do_f;
        t1.last_execution_time = millis();
        t1.timedelay = td;
    }

    void update() {
        
    }
};

bool trigger() {
    // Your trigger logic here
    return now_time < max_time;
}

void action() {
    // Your action logic here
    Serial.println("Function executed");
}



EventListener eventlistener;

void setup() {
    Serial.begin(9600);
    eventlistener.add(trigger, action);
}

void loop() {
    eventlistener.update();
    // Add other loop logic as needed
}
