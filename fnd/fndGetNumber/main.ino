#include <stdlib.h>
#include <time.h>
#include "MyLibrary.h"


int digitPins[] = {10, 11, 12, 13};
int segmentPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
int number = 0;


void setup() {
    for (int i=0; i<4; i++){
        pinMode(digitPins[i], OUTPUT);
    }
    for (int i=0; i<8; i++){
        pinMode(segmentPins[i], OUTPUT);
    }
    Serial.begin(9600);
}


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


int IntegerProcess(int i){
    /*
    - 4자리 수
    - 음수일 경우 절대값
    */
    int number = i;
    if (number < 0) {
        number = -i;    
    }
    number %= 10000;
    return number;
}


void loop() {

    /*
    숫자 입력 받아서 fnd에 출력
    */

    if (Serial.available()) {
        String s = Serial.readString();
        s.trim();
        Println(s);
        number = s.toInt();
        number = IntegerProcess(number);
        Println(number);
    }

    int num = number;
    bool isDigitExist = (number >= 0);
    for (int i=3; i>=0; i--){
        if (isDigitExist){
            FndTurnOnNumberAn(num % 10, segmentPins);
            SetOnDigit(i, digitPins);
        }
        Wait(3);
        FndTurnOffAn(segmentPins);
        SetOffDigit(digitPins);
        isDigitExist = (num/10 > 0);
        num /= 10;
    }

}
