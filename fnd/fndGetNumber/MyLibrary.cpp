#include "Arduino.h"
#include "string.h"
#include "MyLibrary.h"

/*
- 자주 사용하는 함수 분리
- fnd 번호 출력
*/

void Print(String s){
    Serial.print(s);
}

void Print(int i){
    Serial.print(i);
}

void Println(String s) {
    Serial.println(s);
}

void Println(int i){
    Serial.println(i);
}

void Wait(int delayTime) {
    delay(delayTime);
}

void TurnOnPin(int pinNumber){
    digitalWrite(pinNumber, HIGH);
}

void TurnOffPin(int pinNumber){
    digitalWrite(pinNumber, LOW);
}

bool fndNumberReps[10][8] = {
    // FND Number Representations w dp
    // Based on Cathod
    {1, 1, 1, 1, 1, 1, 0, 0},   // 0
    {0, 1, 1, 0, 0, 0, 0, 0},   // 1
    {1, 1, 0, 1, 1, 0, 1, 0},   // 2
    {1, 1, 1, 1, 0, 0, 1, 0},   // 3
    {0, 1, 1, 0, 0, 1, 1, 0},   // 4
    {1, 0, 1, 1, 0, 1, 1, 0},   // 5
    {1, 0, 1, 1, 1, 1, 1, 0},   // 6
    {1, 1, 1, 0, 0, 0, 0, 0},   // 7
    {1, 1, 1, 1, 1, 1, 1, 0},   // 8
    {1, 1, 1, 1, 0, 1, 1, 0},   // 9
};

void FndTurnOnNumber(int num, int* fndPinNumbers, bool isCathod){
    for (int i=0; i<8; i++) {
        bool numRep = fndNumberReps[num][i];
        int pinNum = fndPinNumbers[i];
        if ((isCathod && numRep) || (!isCathod) && (!numRep)) {
            TurnOnPin(pinNum);
        } else{
            TurnOffPin(pinNum);
        }
    }
}

void FndTurnOff(int* fndPinNumbers, bool isCathod){
    for (int i=0; i<8; i++) {
        if (isCathod){
            TurnOffPin(fndPinNumbers[i]);
        } else{
            TurnOnPin(fndPinNumbers[i]);
        }
    }
}

void FndTurnOnNumberCath(int num, int* fndPinNumbers){
    FndTurnOnNumber(num, fndPinNumbers, true);
}

void FndTurnOnNumberAn(int num, int* fndPinNumbers){
    FndTurnOnNumber(num, fndPinNumbers, false);
}

void FndTurnOffCath(int* fndPinNumbers) {
    FndTurnOff(fndPinNumbers, true);
}

void FndTurnOffAn(int* fndPinNumbers) {
    FndTurnOff(fndPinNumbers, false);
}
