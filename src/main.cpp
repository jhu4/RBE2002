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

MotorController* leftControl = new MotorController(leftMotor, eLeft);
MotorController* rightControl = new MotorController(rightMotor, eRight);

void setup() {
	pinMode(enablePin, OUTPUT);
	digitalWrite(enablePin, HIGH);

	//leftMotor->setSpeed(0);
	//rightMotor->setSpeed(0);

	leftControl->setSpeed(70);

	Serial.begin(9600);
}


void loop() {

	leftControl->update();
	//Serial.print(leftControl->getSpeed());
	//Serial.print("\t\t");
	//Serial.println(rightControl->getSpeed());
}
