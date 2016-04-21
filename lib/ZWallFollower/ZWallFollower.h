#ifndef ZWALLFOLLOWER_H
#define ZWALLFOLLOWER_H

#include "DistanceSensor.h"
#include "MotorController.h"

class ZWallFollower{
private:
  DistanceSensor* sensorA;
  DistanceSensor* sensorB;
  MotorController* motorControllerA;
  MotorController* motorControllerB;
  double distance;
  double biasSpeed;

public:
  ZWallFollower(DistanceSensor* distSenseA, DistanceSensor* distSenseB,
    MotorController* motorControllerA, MotorController* motorControllerB,
    double distance, double biasSpeed);
};

#endif
