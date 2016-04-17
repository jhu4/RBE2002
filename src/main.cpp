#include "Motor.h"
#include <Arduino.h>

#define enablePin 11

void setup() {
	pinMode(enablePin, OUTPUT);
	digitalWrite(enablePin, HIGH);

	Motor* leftMotor = new Motor(10, 8, 7, 0);
	Motor* rightMotor = new Motor(6, 5, 4, 1);

	leftMotor->setSpeed(0);
	rightMotor->setSpeed(0);
}

void loop() {
}
