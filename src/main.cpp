#include "Motor.h"
#include "Encoder.h"
//#include "Interrupt.h"
#include "MotorController.h"



#include <Arduino.h>

#define enablePin 11

Encoder* eLeft = new Encoder(2,3);
Encoder* eRight = new Encoder(18,19);

Motor* leftMotor = new Motor(10, 7, 8, 0);
Motor* rightMotor = new Motor(6, 4, 5, 1);

//MotorController* leftControl = new MotorController(leftMotor, eLeft, 0.2, 0.6, 0.0);
//MotorController* rightControl = new MotorController(rightMotor, eRight, 0.2, 0.7, 0.0);


MotorController* leftControl = new MotorController(leftMotor, eLeft, 0, 0.1, 0.0);
MotorController* rightControl = new MotorController(rightMotor, eRight, 0, 0.1, 0.0);

void setup() {
	pinMode(enablePin, OUTPUT);
	digitalWrite(enablePin, HIGH);

	//leftMotor->setSpeed(70);
	//rightMotor->setSpeed(70);

	leftControl->setSpeed(-220);
	rightControl->setSpeed(-220);

	//Serial.begin(9600);
}


void loop() {
	// delay(1000);
	// Serial.println(eLeft->read());
	// eLeft->write(0);
	// Serial.println(eRight->read());
	// eRight->write(0);
	leftControl->update();
	rightControl->update();
}
