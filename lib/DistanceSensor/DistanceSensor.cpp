/*
Sharp IR Distance Sensor Wrapper
DistanceSensor.cpp
distance sensor class to handle input from the shard ir distance sensors

author: Zachary Armsby
*/

#include "DistanceSensor.h"

// initialize distance sensor, setup pin
DistanceSensor::DistanceSensor(int pin):
pin(pin),
distance(0),
averageArray{0},
averageVal(0),
index(0){
  pinMode(pin, INPUT);
  getDistance();
}

// get the distance from sensor reading
// linearized output for wall range and boundry checking
double DistanceSensor::getDistance(){
  // calculate distance
  int reading = analogRead(pin);
  distance = (-0.846*reading)+283.257;
  if (distance < 10){
    distance = 10;
  } else if (distance > 250){
    distance = 250;
  }

  // add to averageing array
  averageArray[index] = distance;
  index++;
  if (index >= NUM_AVG){
    index = 0;
  }
  return distance;
}

// calculate an average of the the last few readings to stabilize data 
double DistanceSensor::getAverage(){
  double sum = 0;
  for (int index = 0; index < NUM_AVG; index++){
    sum = sum + averageArray[index];
  }
  return sum/NUM_AVG;
}
