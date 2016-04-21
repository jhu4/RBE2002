#include "Motor.h"
#include "Encoder.h"
#include "MotorController.h"
#include "LCD.h"
#include "DistanceSensor.h"

#include <Arduino.h>

#define enablePin 11

Encoder* eLeft = new Encoder(2,3);
Encoder* eRight = new Encoder(18,19);

Motor* leftMotor = new Motor(10, 7, 8, 1);
Motor* rightMotor = new Motor(6, 4, 5, 0);

MotorController* leftControl = new MotorController(leftMotor, eLeft, 0.2, 0.6, 0.0);
MotorController* rightControl = new MotorController(rightMotor, eRight, 0.2, 0.7, 0.0);

LCD* lcd = new LCD(40,41,42,43,44,45);

DistanceSensor* distA = new DistanceSensor(A2);
DistanceSensor* distB = new DistanceSensor(A1);

void setup() {
	pinMode(enablePin, OUTPUT);
	digitalWrite(enablePin, HIGH);

	leftControl->setSpeed(0);
	rightControl->setSpeed(0);
}

void loop() {
	leftControl->update();
	rightControl->update();

	double d1 = distA->getDistance();
	double d2 = distB->getDistance();
	double space = 165;
	double d3 = abs(d1-d2);
	if (d3 == 0){
		d3 = 0.000001;
	}
	double z = space/d3;
	double dist = (z/sqrt(1+(z*z)))*d2;
	if (dist < 10 || dist != dist){
		dist = 10;
	} else if (dist > 250){
		dist = 250;
	}

	lcd->display(dist);
	//lcd->display(leftControl->getTickDistance()*TICKTOMM);
}
