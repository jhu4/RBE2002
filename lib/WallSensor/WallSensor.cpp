#include "WallSensor.h"
#include <Arduino.h>

WallSensor::WallSensor(int p, int w):
	pin(p)
	,reading(0),lastreading(0)
	,wallValue(w){
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
	return reading>wallValue;
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

bool WallSensor::notWall(){
	return reading<130;
}
