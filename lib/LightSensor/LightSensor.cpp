#include "LightSensor.h"
#include <Arduino.h>

LightSensor::LightSensor(int Ap,unsigned int thr):
Apin(Ap)
,threshold(thr)
,isCandle(false),averageReading(0)
,index(0),size(0){
}

void LightSensor::initialize(){
	pinMode(Apin, INPUT);
}

/** Sense the flame
 * @return if something unusual happened
 */
bool LightSensor::sense(){
	indexIncrement();
	size++;
	readinglst[index] = analogRead(Apin);
	(size>=capacity? size=capacity: size=size);

	averageReading=0;
	for(int i=0;i<size;i++){
		averageReading+=readinglst[i];
	}
	averageReading/=size;;


	if(size==capacity && abs(averageReading-readinglst[index])>threshold){
		isCandle = true;
		return true;
	}
	return false;
}

/**Get the reading from a flame sensor
 *@return The current analogy reading of the flame sensor
**/
int LightSensor::getReading(){
	return readinglst[index];
}

/**Asking the flame sensor if it detects the light
 *@return true if the flame sensor has detected the candle
**/
bool LightSensor::isDetectLight(){
	return isCandle;
}


/**Get the distance from the flame sensor to the candle
 *@return The distance from FlameSensor to the point of the lowest reading
**/
float LightSensor::getDistance(){
  if(readinglst[index]>400){
    return -999;
  }
  if(readinglst[index]<=400 && readinglst[index]>45){
    return (5*(float)(readinglst[index])/206+5555/103);
  }
	return (log((float)readinglst[index])-2.57)/0.022;
}

/**
 *Increment the index of the array
**/
void LightSensor::indexIncrement(){
	index++;
	if(index>=capacity){
		index=0;
	}
}

/**
 *@return The last index of the array
**/
int LightSensor::lastIndex(){
	return (index-1<0? capacity-1: index-1);
}

/**
 *@return The average analog reading of the flame sensor
**/
int LightSensor::getAverageReading(){
	return averageReading;
}

/**
 *Reset the state of the flame sensor
**/
void LightSensor::reset(){
	index=0;
	size=0;
	isCandle=false;
}
