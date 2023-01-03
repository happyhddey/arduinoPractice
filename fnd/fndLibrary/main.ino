#include <stdlib.h>
#include <time.h>
#include "MyLibrary.h"


int pins[] = {3, 4, 5, 6, 7, 8, 9};


void setup() {
    for (int i=0; i<7; i++){
        pinMode(pins[i], OUTPUT);
    }
    Serial.begin(9600);
}


void loop() {

    for (int i=0; i<10; i++){
        FndTurnOnNumber(i, pins);
        Wait(500);
        FndTurnOff(pins);
    }

}
