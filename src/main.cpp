#include "Motor.h"
#include "Encoder.h"
#include "MotorController.h"



#include <Arduino.h>

#define enablePin 11

Encoder* eLeft = new Encoder(2,3);
Encoder* eRight = new Encoder(18,19);

Motor* leftMotor = new Motor(10, 7, 8, 1);
Motor* rightMotor = new Motor(6, 4, 5, 0);

MotorController* leftControl = new MotorController(leftMotor, eLeft, 0.2, 0.6, 0.0);
MotorController* rightControl = new MotorController(rightMotor, eRight, 0.2, 0.7, 0.0);

void setup() {
	pinMode(enablePin, OUTPUT);
	digitalWrite(enablePin, HIGH);

	leftControl->setSpeed(220);
	rightControl->setSpeed(220);
}

int x = -220;
void loop() {
	leftControl->update();
	rightControl->update();
}
