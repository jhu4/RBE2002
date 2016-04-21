#include "WallSensor.h"
#include <Arduino.h>

WallSensor::WallSensor(int p):
pin(p),
reading(0),lastreading(0){
}

void WallSensor::initialize(){
	pinMode(pin, INPUT);
}

int WallSensor::sense(){
	lastreading = reading;
	reading = analogRead(pin);
	return reading;
}

int WallSensor::getReading(){
  return reading;
}

bool WallSensor::isWall(){
	return reading>140;
}

bool WallSensor::isFindGap(){
	return ((lastreading-reading)>70)&&(reading<30);
}

bool WallSensor::isGap(){
	return reading<80;
}

bool WallSensor::isSame(){
	return abs(lastreading-reading)<20;
}
