/*
Locator, handles odometry calulations
Locator.cpp
odometry calculations and candle location

author: Zachary Armsby
*/

#include "Locator.h"

// initialize locator
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

// update the odometry calculations by
// updating the heading and x-y cooridinates based on the arc lengths from encoders
void Locator::update(){
  // get encoder distance in ticks
  double leftDist = motorControllerA->getTickDistance();
  double rightDist = motorControllerB->getTickDistance();

  // calculate distance traveled since last update in mm
  double leftDistDiff = (leftDist-leftDistOld)*TICKTOMM;
  double rightDistDiff = (rightDist-rightDistOld)*TICKTOMM;

  leftDistOld = leftDist;
  rightDistOld = rightDist;

  // update heading
  double theta = (-leftDistDiff+rightDistDiff)/(wheelSpace);
  heading = theta + heading;

  // update x-y coordinates and handle the special case to prevent zero division
  if (theta != 0){
    double radius = (rightDistDiff/theta)-(wheelSpace/2);
    x = x + (radius*(sin(theta+heading)-sin(heading)));
    y = y + (radius*(cos(heading)-cos(theta+heading)));
  } else {
    x = x + leftDistDiff*cos(heading);
    y = y + leftDistDiff*sin(heading);
  }
}

// get the candle x based on odometry data
double Locator::getCandleX(double mm){
  return (x + (mm*cos(heading)))*MMTOIN;
}

// get the candle y based on odometry data
double Locator::getCandleY(double mm){
  return (y + (mm*sin(heading)))*MMTOIN;
}

// detect if robot is within a radius to the origin
bool Locator::atOrigin(double radius){
  double dist = sqrt((x*x)+(y*y));
  if (dist < radius){
    return true;
  } else {
    return false;
  }
}
