/*
Sharp IR Distance Sensor Wrapper
DistanceSensor.hpp
distance sensor class to handle input from the shard ir distance sensors

author: Zachary Armsby
*/

#ifndef DISTANCESENSOR_H
#define DISTANCESENSOR_H

#include <Arduino.h>

// number of data points to average
#define NUM_AVG 30

class DistanceSensor{
private:
  int pin;
  double distance;
  double averageArray[NUM_AVG];
  double averageVal;
  int index;
public:
  DistanceSensor(int pin);
  double getDistance();
  double getAverage();
};

#endif
