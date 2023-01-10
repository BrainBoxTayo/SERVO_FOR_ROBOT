#include <Servo.h>
#include<Arduino.h>
#include"ServoHeader.h"

//Debugging Turn on and Off
#define useDebug 0

#if useDebug == 1
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#else
#define debug(x)
#define debugln(x)
#endif
//end of Debugging quirk

#define IrReceiverPin  12

int stateVariable = 1;

robotArm robotArm1;


void setup() {
  robotArm1.initialize(9, A0);
  //Serial Communication initialization
  Serial.begin(9600);
}

void loop() {

  debugln(moverRemoteServo);

  //State Machine
  switch (stateVariable) {
    case 1:
      robotArm1.moverResist();
      break;
    case 2:
      break;
    default:
      debug("Error!!!");
      exit(1);
      break;

  }

}
