class EventListener {
private:
    struct stored_function {
        std::function<bool()> trigger;
        std::function<void()> dofunc;
        unsigned long last_execution_time;
        int timedelay;
    };
    std::vector<stored_function> store;

public:
    template<typename TriggerFunc, typename ActionFunc>
    void add(TriggerFunc tri, ActionFunc do_f, int td = 1000) {
        stored_function t1;
        t1.trigger = tri;
        t1.dofunc = do_f;
        t1.last_execution_time = millis();  // Arduino millis() function for time tracking
        t1.timedelay = td;
        store.push_back(t1);
    }

    void update() {
        for (auto& stored_func : store) {
            if (millis() - stored_func.last_execution_time >= stored_func.timedelay) {
                if (stored_func.trigger()) {
                    stored_func.dofunc();
                    stored_func.last_execution_time = millis();
                }
            }
        }
    }
};

void f1() {
    Serial.println("Function 1");
}

void f2() {
    Serial.println("Function 2");
}

bool trigger() {
    return now_time < max_time;
}

int now_time = 0;
int max_time = 10;

EventListener eventlistener;

void setup() {
    Serial.begin(9600);
    eventlistener.add(trigger, f1);
    eventlistener.add(trigger, f2);
}

void loop() {
    // Main event loop
    eventlistener.update();
    // Add other loop logic as needed
}
