#ifndef ZWALLFOLLOWER_H
#define ZWALLFOLLOWER_H

#include "DistanceSensor.h"
#include "MotorController.h"
#include "PID_v1.h"

class ZWallFollower{
private:
  DistanceSensor* distSenseA;
  DistanceSensor* distSenseB;
  DistanceSensor* distSenseC;
  MotorController* motorControllerA;
  MotorController* motorControllerB;
  double distance;
  double biasSpeed;
  double output;
  double input;
  PID pid;
  bool enabled;

public:
  ZWallFollower(DistanceSensor* distSenseA, DistanceSensor* distSenseB,
    MotorController* motorControllerA, MotorController* motorControllerB,
    double distance, double biasSpeed, double kp, double ki, double kd);
  void update();
  double getDistance();
  void disable();
  void enable();
};

#endif
