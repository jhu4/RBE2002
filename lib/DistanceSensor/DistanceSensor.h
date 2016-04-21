#ifndef DISTANCESENSOR_H
#define DISTANCESENSOR_H

#include <Arduino.h>

class DistanceSensor{
private:
  int pin;
  double distance;
public:
  DistanceSensor(int pin);
  double getDistance();
};

#endif
