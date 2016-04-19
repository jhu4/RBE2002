#include "Motor.h"
#include "Encoder.h"
#include "Interrupt.h"
#include "MotorController.h"
#include <Arduino.h>

#define enablePin 11

Encoder* eLeft = new Encoder(2,3);
Encoder* eRight = new Encoder(18,19);

Motor* leftMotor = new Motor(10, 8, 7, 0);
Motor* rightMotor = new Motor(6, 5, 4, 1);

MotorController* leftControl = new MotorController(leftMotor, eLeft, 0.2, 0.6, 0.0);
MotorController* rightControl = new MotorController(rightMotor, eRight, 0.3, 0.7, 0.0);

void setup() {
	pinMode(enablePin, OUTPUT);
	digitalWrite(enablePin, HIGH);

	leftControl->setSpeed(220);
	rightControl->setSpeed(220);
}


void loop() {

	leftControl->update();
	rightControl->update();
}
