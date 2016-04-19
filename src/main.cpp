#include "Motor.h"
#include "Encoder.h"
#include "Interrupt.h"
#include <Arduino.h>

#define enablePin 11


void isrL();
Encoder* eLeft = new Encoder(2,3);
void isrL(){
	eLeft->tickISR();
}

void setup() {
	pinMode(enablePin, OUTPUT);
	digitalWrite(enablePin, HIGH);

	Motor* leftMotor = new Motor(10, 8, 7, 0);
	Motor* rightMotor = new Motor(6, 5, 4, 1);

	leftMotor->setSpeed(0);
	rightMotor->setSpeed(0);

	pinMode(2, INPUT);
	pinMode(3, INPUT);

	//Interrupt* inter = new Interrupt();

	attachInterrupt(digitalPinToInterrupt(2), Interrupt::Interrupt_0, CHANGE);
	attachInterrupt(digitalPinToInterrupt(3), isrL, CHANGE);

	Serial.begin(9600);
}

void loop() {
	delay(1000);
	Serial.println(eLeft->getTicks());
}
