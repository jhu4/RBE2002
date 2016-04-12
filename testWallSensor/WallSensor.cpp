#include "WallSensor.h"
#include <Arduino.h>

WallSensor::WallSensor(int p):
pin(p),
reading(0),lastreading(0){
}

void WallSensor::initializing(){
	pinMode(pin, INPUT);
}

int WallSensor::sense(){
	lastreading = reading;
	reading = analogRead(pin);
	return reading;
}

bool WallSensor::isWall(){
	return reading>100;
}

bool WallSensor::isFindGap(){
	return ((lastreading-reading)>50)&&(reading<20);
}
