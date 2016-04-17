#include "Motor.h"
#include <Arduino.h>


Motor::Motor(int speedPin, int dirAPin, int dirBPin):
speedPin(speedPin),
dirAPin(dirAPin),
dirBPin(dirBpin),
dir(1),
speed(0){
	setDir(FORWARD);
}

Motor::setDir(bool forwardDir){
	if (forwardDir){
		digitalWrite(dirAPin, HIGH);
		digitalWrite(dirBPin, LOW);
	} else {
		digitalWrite(dirAPin, LOW);
		digitalWrite(dirBPin, HIGH);
	}
}

Motor::setSpeed(int speed){
	this.speed = speed;

	bool backward = (speed < 0);

	if(backward && dir){
		this.dir = 0;
		setDir(0);
	} else if (!backward && !dir){
		this.dir = 1;
		setDir(1);
	}

	analogWrite(speedPin, speed);
}

Motor::~Motor(){}
