#include <stdlib.h>
#include <time.h>
#include "MyLibrary.h"


int digitPins[] = {10, 11, 12, 13};
int segmentPins[] = {2, 3, 4, 5, 6, 7, 8, 9};

void SetOnDigit(int digit, int* digitPins){
    /*
    FND: 0 0 0 0
    dig: 0 1 2 3
    */
    for (int i=0; i<4; i++){
        if (i == digit){
            TurnOnPin(digitPins[i]);
        } else{
            TurnOffPin(digitPins[i]);
        }
    }
}

void SetOffDigit(int* digitPins){
    for (int i=0; i<4; i++){
        TurnOffPin(digitPins[i]);
    }
}


struct Time{
    /*
    [int] format
    - 시간 표시 형식
        - 0: (s:ms)
        - 1: (m:s)
        - 2: (h:m)
    */
    int format;
    int left;
    int right;
    int roundValue;
};

struct Time TimeProcess(unsigned long mil){
    /*
    60,000ms(=60s) 미만: format=0 (s:ms)
        - 24,123ms(=24.123s): 24, 12
    60,000ms(=60s) 이상: format=1 (m:s)
        - 73,123ms(=1m 13s 123ms): 1, 13
    */
    Time t;
    if (mil < 60000){
        t.format = 0;
        t.left = (mil / 1000);
        t.right = (mil % 1000) / 10;
        t.roundValue = (mil % 1000) % 10;
    } else if (mil < 60000*60){
        t.format = 1;
        t.left = ((mil / 60000) % 100);
        t.right = ((mil % 60000) / 1000);
        t.roundValue = ((mil % 1000) / 100);
    } else {
        // h:m 형식 추가 바람
        t.format = 2;
        t.roundValue = ((mil % 1000) / 100);
    }
    return t;
}




void setup() {
    for (int i=0; i<4; i++){
        pinMode(digitPins[i], OUTPUT);
    }
    for (int i=0; i<8; i++){
        pinMode(segmentPins[i], OUTPUT);
    }
    Serial.begin(9600);
}


void loop() {

    unsigned long t = millis();
    Time time = TimeProcess(t);
    
    if (time.format == 0){
        // format 0: (s:ms) 형식
        for (int i=0; i<4; i++){
            int left = time.left;
            int right = time.right;
            if (i == 0){
                if (left / 10 == 0){
                    FndTurnOff(segmentPins, false);
                } else {
                    FndTurnOnNumber(left / 10, segmentPins, false);
                }
            } else if (i == 1){
                FndTurnOnNumberWdp(left % 10, segmentPins, false);
            } else if (i == 2){
                FndTurnOnNumber(right / 10, segmentPins, false);
            } else if (i == 3){
                FndTurnOnNumber(right % 10, segmentPins, false);
            }
            SetOnDigit(i, digitPins);
            Wait(3);
            FndTurnOff(segmentPins, false);
            SetOffDigit(digitPins);
        }
    } else if (time.format == 1) {
        // format 1: (m:s) 형식
        for (int i=0; i<4; i++){
            int left = time.left;
            int right = time.right;
            if (i == 0){
                if (left / 10 == 0){
                    FndTurnOff(segmentPins, false);
                } else {
                    FndTurnOnNumber(left / 10, segmentPins, false);
                }
            } else if (i == 1){
                if (time.roundValue < 5) {
                    FndTurnOnNumberWdp(left % 10, segmentPins, false);
                } else {
                    FndTurnOnNumber(left % 10, segmentPins, false);
                }
            } else if (i == 2){
                FndTurnOnNumber(right / 10, segmentPins, false);
            } else if (i == 3){
                FndTurnOnNumber(right % 10, segmentPins, false);
            }
            SetOnDigit(i, digitPins);
            Wait(3);
            FndTurnOff(segmentPins, false);
            SetOffDigit(digitPins);
        }
    }

}
