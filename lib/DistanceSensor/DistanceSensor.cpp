#include "DistanceSensor.h"

DistanceSensor::DistanceSensor(int pin):
pin(pin),
distance(0){
  pinMode(pin, INPUT);
  getDistance();
}

double DistanceSensor::getDistance(){
  int reading = analogRead(pin);
  distance = (-0.846*reading)+283.257;
  if (distance < 10){
    distance = 10;
  } else if (distance > 250){
    distance = 250;
  }
  return distance;
}
