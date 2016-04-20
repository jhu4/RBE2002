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
LCD lcd(40,41,42,43,44,45);
MotorController leftControl(leftMotor, eLeft, 0.2, 0.6, 0.0);
MotorController rightControl(rightMotor, eRight, 0.3, 0.7, 0.0);
WallSensorManager ms(0,1,2,lcd);
WallFollower wf(ms,leftControl,rightControl,loca,lcd,kp,kd);

void setup() {
	pinMode(enablePin, OUTPUT);
	digitalWrite(enablePin, HIGH);
	wf.initialize();
}


void loop() {
	wf.followTheWall();
}
