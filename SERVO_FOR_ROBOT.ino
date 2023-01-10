#include <Servo.h>
#include <IRremote.hpp>
#include <Arduino.h>


#define useDebug 0

#if useDebug == 1
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#else
#define debug(x)
#define debugln(x)
#endif
#define IrReceiverPin 12

int resistor1Pin = A0;
int resistor2Pin = A1;
int resistor3Pin = A2;
int moverResistorServo1;
int moverResistorServo2;
int moverResistorServo3;
int moverRemoteServo1 = 0;
int moverRemoteServo2 = 0;
int moverRemoteServo3 = 0;

int increaseFactor = 10;
int stateVariable = 1;
Servo servo1;
Servo servo2;
Servo servo3;

void setup()
{

    // define resistorPin as Input
    pinMode(resistor1Pin, INPUT);
    pinMode(resistor2Pin, INPUT);
    // define IrReceiverpin as input
    pinMode(IrReceiverPin, INPUT);
    // attach first servo to pin 9
    servo1.attach(9);
    servo2.attach(6);
    servo3.attach(5);
    // initialisation of IrReceiverPin with led 13 blinking on(for feedback)
    IrReceiver.begin(IrReceiverPin, 1);
    // Serial Communication initialization
    Serial.begin(9600);
}

void loop()
{

    debugln(moverRemoteServo);

    // State Machine
    switch (stateVariable)
    {
    case 1:
        servo1.write(moveServoWithRes(moverResistorServo1, resistor1Pin));
        servo2.write(moveServoWithRes(moverResistorServo2, resistor2Pin));
        servo3.write(moveServoWithRes(moverResistorServo3, resistor3Pin));
        IrReceiverStateSwitcher(stateVariable);
        break;
    case 2:
        servo1.write(moveServoWithIr(moverRemoteServo1, stateVariable, increaseFactor));
        servo2.write(moveServoWithIr(moverRemoteServo2, stateVariable, increaseFactor));
        servo3.write(moveServoWithIr(moverRemoteServo3, stateVariable, increaseFactor));
        break;
    default:
        debug("Error!!!");
        exit(1);
        break;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void moverIr() { servo.write(moveServoWithIr(moverServoVariable, stateVariable, increaseFactor)); }
int moveServoWithIr(int &moverVariable, int &stateVariable, int &increaser)
{

    if (IrReceiver.decode())
    {
        if (IrReceiver.decodedIRData.command == 67)
        {
            moverVariable += increaser;
        }
        if (IrReceiver.decodedIRData.command == 64)
        {
            moverVariable -= increaser;
        }
        if (IrReceiver.decodedIRData.command == 9)
        {
            increaser += 1;
        }
        if (IrReceiver.decodedIRData.command == 21)
        {
            increaser -= 1;
        }
        if (IrReceiver.decodedIRData.command == 7)
        {
            stateVariable = 1;
        }
        if (IrReceiver.decodedIRData.command == 68)
        {
            stateVariable = 2;
        }

        IrReceiver.resume();
    }
    if (moverVariable > 180)
    {
        moverVariable = 180;
    }
    if (moverVariable < 0)
    {
        moverVariable = 0;
    }
    return moverVariable;
}
void StateSwitcher()
{
    if (IrReceiver.decode())
    {
        if (IrReceiver.decodedIRData.command == 7)
        {
            stateVariable = 1;
        }
        if (IrReceiver.decodedIRData.command == 68)
        {
            stateVariable = 2;
        }
        IrReceiver.resume();
    }
}
