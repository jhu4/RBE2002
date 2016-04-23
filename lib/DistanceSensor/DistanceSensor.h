#ifndef DISTANCESENSOR_H
#define DISTANCESENSOR_H

#include <Arduino.h>

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
