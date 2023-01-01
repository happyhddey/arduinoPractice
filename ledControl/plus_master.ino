#include <stdlib.h>
#include <time.h>

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

class Counter{
private:
    int count;

public:
    Counter(){
        count = 0;
    }
    void add(){
        count++;
        if (count >= 10) {
            count = 0;
        }
    }
    void substract(){
        count--;
        if (count < 0) {
            count = 9;
        }
    }
    int getCount(){
        return count;
    }
    void resetCounter(){
        count = 0;
    }
};

class PlusMaster{
private:
    int level;
    int answer;
    int showTime;
    int sizeOfSeries;
    int numberSeries[7];

public:
    PlusMaster(){
        level = 1;
        showTime = 500;
        answer = 0;
        sizeOfSeries = 3;
        for (int i=0; i<7; i++){
            numberSeries[7] = 0;
        }
    }

    void levelUp(){
        showTime -= 30;
    }

    void setGame(int size){
        sizeOfSeries = size;
        int sum = 0;
        srand(millis());
        for (int i=0; i<sizeOfSeries; i++){
            int random = rand() % 10;
            numberSeries[i] = random;
            sum += random;
        }
        answer = sum % 10;
        print(answer);
    }

    int getShowTime() {
        return showTime;
    }

    int getSizeOfSeries(){
        return sizeOfSeries;
    }

    int getNthNumber(int n){
        if ((0<=n) && (n<sizeOfSeries)){
            return numberSeries[n];
        } else{
            return -1;
        }
    }

    bool isRightAnswer(int sum){
        return sum == answer;
    }

    int getAnswer(){
        return answer;
    }
};


int upSwitch = 12;
int downSwitch = 11;
Switch us = Switch();
Switch ds = Switch();

Counter counter = Counter();
PlusMaster pm = PlusMaster();

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

void setup() {
    for (int i=0; i<7; i++){
        pinMode(pins[i], OUTPUT);
    }
    pinMode(upSwitch, INPUT_PULLUP);
    pinMode(downSwitch, INPUT_PULLUP);
    Serial.begin(9600);
}

String phase = "show";
unsigned long answerTime;
int answer;

void loop() {

    if (phase == "show"){
        print("Start");
        pm.setGame(3);
        int sizeOfSeries = pm.getSizeOfSeries();
        int showTime = pm.getShowTime();
        for (int i=0; i<sizeOfSeries; i++) {
            int num = pm.getNthNumber(i);
            for (int i=0; i<7; i++){
                if (blueprints[num][i]) {
                    on(pins[i]);
                } else{
                    off(pins[i]);
                }
            }
            wait(showTime);
            for (int i=0; i<7; i++){
                off(pins[i]);
            }
            wait(100);
        }

        
        phase = "quiz";
        answerTime = millis();
        counter.resetCounter();
        int count = counter.getCount();
        for (int i=0; i<7; i++){
            if (blueprints[count][i]) {
                on(pins[i]);
            } else{
                off(pins[i]);
            }
        }

    } else if (phase == "quiz") {
        // upSwitch나 downSwitch가 눌려진(선이 연결된) 상태일 때
        int upSwitchState = digitalRead(upSwitch);
        int downSwitchState = digitalRead(downSwitch);

        if ((upSwitchState == LOW && !us.isSwitchUp()) || (downSwitchState == LOW && !ds.isSwitchUp())) {
            if (upSwitchState == LOW) {
                us.up();
                counter.add();
            } else if (downSwitchState == LOW) {
                ds.up();
                counter.substract();
            }
            int count = counter.getCount();
            for (int i=0; i<7; i++){
                if (blueprints[count][i]) {
                    on(pins[i]);
                } else{
                    off(pins[i]);
                }
            }
            delay(100);
        } else if (upSwitchState == HIGH && us.isSwitchUp()){
            us.down();
        } else if (downSwitchState == HIGH && ds.isSwitchUp()){
            ds.down();
        }
        answer = counter.getCount();
        
        unsigned long currentTime = millis();
        if (currentTime - answerTime >= 5000) {
            phase = "check";
        }

    } else if (phase == "check") {
        // 선택한 정답 깜빡깜빡
        for (int i=0; i<7; i++){
            off(pins[i]);
        }
        wait(100);
        for (int i=0; i<3; i++) {
            for (int i=0; i<7; i++){
                if (blueprints[answer][i]) {
                    on(pins[i]);
                } else{
                    off(pins[i]);
                }
            }
            wait(200);
            for (int i=0; i<7; i++){
                off(pins[i]);
            }
            wait(200);
        }
        wait(1000);
        if (pm.isRightAnswer(answer)) {
            for (int i=0; i<7; i++){
                if (blueprints[0][i]) {
                    on(pins[i]);
                } else {
                    off(pins[i]);
                }
            }
            pm.levelUp();
            print("RIGHT");
        } else {
            bool ex[7] = {0, 1, 1, 0, 1, 1, 1};
            for (int i=0; i<7; i++){
                if (ex[i]) {
                    on(pins[i]);
                } else {
                    off(pins[i]);
                }
            }
            print("WRONG");
        }
        wait(2000);
        for (int i=0; i<7; i++){
            off(pins[i]);
        }
        wait(2000);
        phase = "show";
    }
}
