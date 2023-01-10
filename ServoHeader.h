#ifndef SERVOHEADER_H
#define SERVOHEADER_H
#include<Servo.h>

class robotArm {
  public:
    robotArm();
    //use this to attach robot arm to servo pin and declare the storage unit and also the pin of its controller i.e each arm has a unique servo
    void initialize(int servoPin, int ResistorPin);
    void moverResist();
    int moveServoWithRes(int &resistorPinStore, int resistorPin);
 
  private:
    Servo servo;
    int moverServoVariable;
    int resistorPin;
  };



#endif
