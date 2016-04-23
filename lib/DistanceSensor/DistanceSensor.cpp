#include "DistanceSensor.h"

DistanceSensor::DistanceSensor(int pin):
pin(pin),
distance(0),
averageArray{0},
averageVal(0),
index(0){
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

  averageArray[index] = distance;

  index++;
  if (index >= NUM_AVG){
    index = 0;
  }

  return distance;
}

double DistanceSensor::getAverage(){
  double sum = 0;
  for (int index = 0; index < NUM_AVG; index++){
    sum = sum + averageArray[index];
  }
  return sum/NUM_AVG;
}
