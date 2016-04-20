#include "MotorController.h"
#include <Arduino.h>
#include "WallSensorManager.h"
#include "Location.h"
#include "WallFollower.h"
#define enablePin 11

double kd=0;
double kp=0;

Encoder* eLeft = new Encoder(2,3);
Encoder* eRight = new Encoder(18,19);
Location loca;
Motor* leftMotor = new Motor(10, 8, 7, 0);
Motor* rightMotor = new Motor(6, 5, 4, 1);
MotorController leftControl(leftMotor, eLeft, 0.2, 0.6, 0.0);
MotorController rightControl(rightMotor, eRight, 0.3, 0.7, 0.0);
LCD lcd(40,41,42,43,44,45);
WallSensorManager ms(0,1,2,lcd);
WallFollower wf(ms,leftControl,rightControl,loca,lcd,kp,kd);

void setup() {
  // Serial.begin(9600);
  // pinMode(enablePin, OUTPUT);
  // digitalWrite(enablePin, HIGH);
  // rightControl.setSpeed(0);
  // leftControl.setSpeed(0);
  // wf.initialize();
}


void loop() {
 // rightControl.update();
  // wf.followTheWall();
}
