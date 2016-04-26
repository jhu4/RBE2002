#include "Locator.h"

#include "LCD.h"
//LCD* lcd = new LCD(40,41,42,43,44,45);

Locator::Locator(MotorController* motorControllerA, MotorController* motorControllerB):
motorControllerA(motorControllerA),
motorControllerB(motorControllerB),
leftDistOld(0),
rightDistOld(0),
heading(0),
x(0),
y(0),
wheelSpace(177){

}

void Locator::update(){
  double leftDist = motorControllerA->getTickDistance();
  double rightDist = motorControllerB->getTickDistance();

  double leftDistDiff = (leftDist-leftDistOld)*TICKTOMM;
  double rightDistDiff = (rightDist-rightDistOld)*TICKTOMM;

  leftDistOld = leftDist;
  rightDistOld = rightDist;

  double theta = (-leftDistDiff+rightDistDiff)/(wheelSpace);
  heading = theta + heading;

  if (theta != 0){
    double radius = (rightDistDiff/theta)-(wheelSpace/2);
    x = x + (radius*(sin(theta+heading)-sin(heading)));
    y = y + (radius*(cos(heading)-cos(theta+heading)));
  } else {
    x = x + leftDistDiff*cos(heading);
    y = y + leftDistDiff*sin(heading);
  }

  //lcd->display(x*MMTOIN,y*MMTOIN);
}

bool Locator::atOrigin(double radius){
  double dist = sqrt((x*x)+(y*y));
  if (dist < radius){
    return true;
  } else {
    return false;
  }
}
