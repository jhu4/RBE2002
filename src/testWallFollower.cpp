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

Motor* leftMotor = new Motor(10, 7, 8, 1);
Motor* rightMotor = new Motor(6, 4, 5, 0);

MotorController leftControl(leftMotor, eLeft, 0.2, 0.6, 0.0);
MotorController rightControl(rightMotor, eRight, 0.2, 0.7, 0.0);

Location loca;

LCD lcd(40,41,42,43,44,45);
WallSensorManager ms(0,1,2,lcd,3500);
WallFollower wf(ms,leftControl,rightControl,loca,lcd,40,0,0,100);
//works really well in (10,0,0)
//overshoot a little (15,0,0),(20,0,0)
void setup() {
  Serial.begin(9600);
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, HIGH);
  wf.initialize();
}


void loop() {
  wf.followTheWall();
}
