#include "Motor.h"
#include <Arduino.h>


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

bool Motor::isInvert(){
	return invert;
}

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

void Motor::setSpeed(int speed){
	//Serial.println("call");
	this->speed = speed;

	bool backward = false;
	if (speed < 0){
		backward = true;
		speed = -speed;
	};

	if(backward && dir){
		//Serial.println("change!");
		//speed = -speed;
		this->dir = 0;
		setDir(0);
	} else if (!backward && !dir){
		//Serial.println("change!");
		this->dir = 1;
		setDir(1);
	}

	if (speed > 255){
		speed = 255;
	}

	analogWrite(speedPin, speed);
	return;
}

Motor::~Motor(){}
