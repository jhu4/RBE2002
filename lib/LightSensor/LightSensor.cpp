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

int LightSensor::getReading(){
	return readinglst[index];
}

bool LightSensor::isDetectLight(){
	return isCandle;
}

// bool LightSensor::isGetCloser(){
// 	return readinglst[lastIndex()]!=0 &&((readinglst[lastIndex()]-readinglst[index])>60);
// }

float LightSensor::getDistance(){
  if(readinglst[index]>400){
    return -999;
  }
  if(readinglst[index]<=400 && readinglst[index]>45){
    return (5*(float)(readinglst[index])/206+5555/103);
  }
	return (log((float)readinglst[index])-2.57)/0.022;
}

void LightSensor::indexIncrement(){
	index++;
	if(index>=capacity){
		index=0;
	}
}

int LightSensor::lastIndex(){
	return (index-1<0? capacity-1: index-1);
}

int LightSensor::getAverageReading(){
	return averageReading;
}
