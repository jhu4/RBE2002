/*
Locator, handles odometry calulations
Locator.h
odometry calculations and candle location

author: Zachary Armsby
*/

#ifndef LOCATOR_H
#define LOCATOR_H

#include "MotorController.h"

// conversion factor
#define MMTOIN 0.0393701

class Locator{
private:
  MotorController* motorControllerA;
  MotorController* motorControllerB;
  double leftDistOld;
  double rightDistOld;
  double heading;
  double x;
  double y;
  double wheelSpace;

public:
  Locator(MotorController* motorControllerA, MotorController* motorControllerB);
  void update();
  bool atOrigin(double radius);
  double getCandleX(double mm);
  double getCandleY(double mm);
};


#endif
