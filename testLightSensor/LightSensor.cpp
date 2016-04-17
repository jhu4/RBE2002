#include "LightSensor.h"
#include <Arduino.h>

LightSensor::LightSensor(int Ap, int Dp, int ofs):
Apin(Ap), Dpin(Dp)
,offset(ofs)
,isCandle(false)
,averageReading(0),counter(0),accumulator(0),lastReading(0){

}

void LightSensor::initialize(){
	pinMode(Apin, INPUT);
	pinMode(Dpin, INPUT);
}

/** Sense the flame
 * @return if something unusual happened
 */
bool LightSensor::sense(){
	lastReading = currentReading;
	currentReading = analogRead(Apin);
	isCandle = digitalRead(Dpin);
	accumulator+=currentReading;
	counter++;
	averageReading=accumulator/counter;
	if(averageReading!= 0 && (averageReading-currentReading)>offset){
		return true;
	}
	return false;
}

int LightSensor::getReading(){
	return currentReading;
}

bool LightSensor::isDetectLight(){
	// return currentReading>50 && currentReading<700;
	return isCandle;
}

bool LightSensor::isGetCloser(){
	return lastReading!=0 &&((lastReading-currentReading)>60);
}

