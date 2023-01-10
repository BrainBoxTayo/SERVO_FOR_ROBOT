#ifndef ROBOTHEAD_H
#define ROBOTHEAD_H
#include<Arduino.h>
#include<Servo.h>
#include "ServoHeader.h"

robotArm::robotArm(){
  //Nothing Here For Now
  };
void robotArm::initialize(int servoPin, int ResistorPin) {
  servo.attach(servoPin);
  resistorPin = ResistorPin;
}
void robotArm::moverResist() {
  servo.write(moveServoWithRes(moverServoVariable, resistorPin));
}
int robotArm::moveServoWithRes(int &resistorPinStore, int resistorPin) {
  resistorPinStore = map(analogRead(resistorPin), 0, 1023, 0, 180);
  return resistorPinStore;
}
#endif
