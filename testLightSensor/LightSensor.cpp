#include "LightSensor.h"
#include <Arduino.h>

LightSensor::LightSensor(int p, int ofs):
pin(p),offset(ofs),
averageReading(0),counter(0),accumulator(0),lastReading(0){

}

void LightSensor::initializing(){
	pinMode(pin, INPUT);
}

bool LightSensor::watch(){
	lastReading = currentReading;
	currentReading = analogRead(pin);
	accumulator+=currentReading;
	counter++;
	averageReading=accumulator/counter;
	if(averageReading!=0 && abs(averageReading-currentReading)>offset){
		return true;
	}

	return false;
}

bool LightSensor::isDetectLight(){
	return currentReading<300;
}

bool LightSensor::isGetCloser(){
	return (lastReading-currentReading)>20;
}

