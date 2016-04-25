#ifndef LOCATOR_H
#define LOCATOR_H

#include "MotorController.h"
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
};


#endif
