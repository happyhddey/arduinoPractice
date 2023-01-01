void on(int pin){
    digitalWrite(pin, HIGH);
}

void off(int pin){
    digitalWrite(pin, LOW);
}

void wait(int delayTime) {
    delay(delayTime);
}

void print(String s) {
    Serial.println(s);
}

void print(int i) {
    Serial.println(i);
}

class Counter{
private:
    int count;

public:
    Counter(){
        count = 0;
    }
    void add(){
        count++;
    }
    int getCount(){
        return count;
    }
    void resetCounter(){
        count = 0;
    }
};

class Switch{
private:
    bool sw;

public:
    Switch(){
        sw = false;
    }
    bool isSwitchUp(){
        return sw;
    }
    void up(){
        sw = true;
    }
    void down(){
        sw = false;
    }
};


int sw = 12;
int pins[] = {3, 4, 5, 6, 7, 8, 9};
bool blueprints[10][7] = {
    {1, 1, 1, 1, 1, 1, 0},  // 0
    {0, 1, 1, 0, 0, 0, 0},  // 1
    {1, 1, 0, 1, 1, 0, 1},  // 2
    {1, 1, 1, 1, 0, 0, 1},  // 3
    {0, 1, 1, 0, 0, 1, 1},  // 4
    {1, 0, 1, 1, 0, 1, 1},  // 5
    {1, 0, 1, 1, 1, 1, 1},  // 6
    {1, 1, 1, 0, 0, 0, 0},  // 7
    {1, 1, 1, 1, 1, 1, 1},  // 8
    {1, 1, 1, 1, 0, 1, 1},  // 9
};
Counter counter = Counter();
Switch swit = Switch();


void setup() {
    for (int i=0; i<7; i++){
        pinMode(pins[i], OUTPUT);
    }
    pinMode(sw, INPUT_PULLUP);
    Serial.begin(9600);
}

void loop() {

    // 선이 연결된 상태일 때
    if (digitalRead(sw) == LOW) {
        if (!swit.isSwitchUp()){
            swit.up();
            counter.add();
            print(counter.getCount());
        }
        int count = counter.getCount() % 10;
        for (int i=0; i<7; i++){
            if (blueprints[count][i]) {
                on(pins[i]);
            }
        }
        delay(100);
    } else {
        if (swit.isSwitchUp()) {
            swit.down();
            for(int i=0; i<7; i++){
                off(pins[i]);
            }
        }
    }

}
