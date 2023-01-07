#include <Arduino.h>
#include <Servo.h>


/*
led, 모터, 서보모터, X키패드 제어
*/

/*
    Digital pin: D 제외하고 숫자만 ex) 1, 2
        - D0 = OUTPUT, low 눌렀을 때 high
    Ax pin: A 포함 ex) A1, A2
*/

/*
    X키패드: 전압 레벨 수준에 따라 번호 입력 -> analogRead(), pinMode 설정 필요 X
    - 1: 1000 이상
    - 2: 700 이상
    - 3: 500 이상
    - 4: 300 이상
    - 5: 200 이상

*/

int ledPins[] = {2, 3, 4};      // D2, D3, D4
int inPin = A6;                 // A6
int motor1Pins[] = {8, A5};              // D8, A5
int motor2Pins[] = {A3, A4};              // A3, A4
int servoPin = 5;               // D5
Servo servo;


int ConvertAnalogValueToNumber(int analogValue) {
    int result = 0;
    int boundaryValues[] = {1000, 700, 500, 300, 100};
    for (int i=0; i<5; i++) {
        if (analogValue >= boundaryValues[i]) {
            result = i+1;
            break;
        }
    }
    return result;
}


void SetMotorSpeed(int speed, int delayMicroSec, int* motorPins) {

    // overflow 처리
    if (speed > 20) {
        speed = 20;
    } else if (speed < -20) {
        speed = -20;
    }

    // pulse 설정
    int pulse = abs(speed);
    int isForward = (speed > 0 ? true : false);

    // implementation
    for (int i=1; i<=20; i++) {
        if (i <= pulse) {
            digitalWrite(motorPins[0], (isForward ? HIGH : LOW));
            digitalWrite(motorPins[1], (isForward ? LOW : HIGH));            
        } else {
            digitalWrite(motorPins[0], HIGH);
            digitalWrite(motorPins[1], HIGH);
        }
        delayMicroseconds(delayMicroSec);
    }
}

void MotorSpeed(int speed1, int speed2) {
    SetMotorSpeed(speed1, 200, motor1Pins);
    SetMotorSpeed(speed2, 200, motor2Pins);
}


void setup() {
    Serial.begin(9600);
    for (int i=0; i<3; i++){
        pinMode(ledPins[i], OUTPUT);
    }
    servo.attach(servoPin);
}


int speed = 5;
int microSeconds = 200;
int servoAngle = 0;

void loop() {

    // int inPinValue = analogRead(inPin);
    // int inNumber = ConvertAnalogValueToNumber(inPinValue);

    // int ledValues[] = {4&inNumber, 2&inNumber, 1&inNumber};

    // for (int i=0; i<3; i++){
    //     digitalWrite(ledPins[i], ledValues[i]);
    // }
    
    int inPinValue = analogRead(inPin);
    int inNumber = ConvertAnalogValueToNumber(inPinValue);
    
    if (inNumber != 0) {
        servoAngle = 45*(inNumber - 1);
        Serial.println(servoAngle);
    }

    servo.write(servoAngle);
    delay(100);

    // MotorSpeed(speed, speed);
}
