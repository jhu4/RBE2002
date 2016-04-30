/*
Motor class to handle low level motor operations and H-bridge
Motor.cpp
basic motor operations

author: Zachary Armsby
*/

#include "Motor.h"
#include <Arduino.h>

// initialize the motor, setup pins and set inital direction and speed
Motor::Motor(int speedPin, int dirAPin, int dirBPin, bool invert):
speedPin(speedPin),
dirAPin(dirAPin),
dirBPin(dirBPin),
dir(1),
speed(0),
invert(invert){
	pinMode(speedPin, OUTPUT);
	pinMode(dirAPin, OUTPUT);
	pinMode(dirBPin, OUTPUT);

	setDir(FORWARD);
	setSpeed(0);
}

// detect if motor is inverted
bool Motor::isInvert(){
	return invert;
}

// set the motor direction
void Motor::setDir(bool forwardDir){

	if (this->invert){
		forwardDir = !forwardDir;
	}

	if (forwardDir){
		digitalWrite(dirAPin, HIGH);
		digitalWrite(dirBPin, LOW);
	} else {
		digitalWrite(dirAPin, LOW);
		digitalWrite(dirBPin, HIGH);
	}
	return;
}

// set the motor speed
void Motor::setSpeed(int speed){
	this->speed = speed;

	// detect going backward
	bool backward = false;
	if (speed < 0){
		backward = true;
		speed = -speed;
	};

	// set the dirrection if nessary
	if(backward && dir){
		this->dir = 0;
		setDir(0);
	} else if (!backward && !dir){
		this->dir = 1;
		setDir(1);
	}

	// limit the max speed
	if (speed > 255){
		speed = 255;
	}

	// write the speed
	analogWrite(speedPin, speed);
	return;
}

Motor::~Motor(){}
