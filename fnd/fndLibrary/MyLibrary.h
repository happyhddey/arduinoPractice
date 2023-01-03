#pragma once

#ifndef MyLibrary_H
#define MyLibrary_H

#include "Arduino.h"

void Print(String s);
void Print(int i);
void Println(String s);
void Println(int i);

void Wait(int delayTime);

void TurnOnPin(int pinNumber);
void TurnOffPin(int pinNumber);

void FndTurnOnNumber(int num, int* fndPinNumbers);
void FndTurnOff(int* fndPinNumbers);

#endif
