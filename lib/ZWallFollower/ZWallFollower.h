/*
WallFollower class to handle wallowing arround the maze
Wallfollower.h
controlls the motors to follow a wall

author: Zachary Armsby
*/

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
  unsigned long lastTime;
  bool ADone;
  bool BDone;
  bool leftTurn;

public:
  ZWallFollower(DistanceSensor* distSenseA, DistanceSensor* distSenseB, DistanceSensor* distSenseC,
    MotorController* motorControllerA, MotorController* motorControllerB,
    double distance, double biasSpeed, double kp, double ki, double kd);
  void update();
  double getDistance();
  void disable();
  void enable();
};

#endif
