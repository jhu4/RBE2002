#include "ZWallFollower.h"

ZWallFollower::ZWallFollower(DistanceSensor* distSenseA, DistanceSensor* distSenseB,
  MotorController* motorControllerA, MotorController* motorControllerB,
  double distance, double biasSpeed, double kp, double ki, double kd):
  distSenseA(distSenseA),
  distSenseB(distSenseB),
  motorControllerA(motorControllerA),
  motorControllerB(motorControllerB),
  distance(distance),
  biasSpeed(biasSpeed),
  output(0),
  input(0),
  pid(&input,&output,&(this->distance),kp,ki,kd,DIRECT),
  enabled(1){
    pid.SetOutputLimits(-100,
      100);
  	pid.SetMode(AUTOMATIC);
}

double ZWallFollower::getDistance(){
  double d1 = distSenseA->getDistance();
  double d2 = distSenseB->getDistance();
  double space = 165;
  double d3 = abs(d1-d2);
  if (d3 == 0){
    d3 = 0.000001;
  }
  double z = space/d3;
  double dist = (z/sqrt(1+(z*z)))*d2;
  if (dist < 10 || dist != dist){
    dist = 10;
  } else if (dist > 250){
    dist = 250;
  }
  return dist;
}

void ZWallFollower::update(){
  if (enabled){
    if(pid.Compute()){

      input = getDistance();

      motorControllerA->setSpeed(biasSpeed - output);
      motorControllerB->setSpeed(biasSpeed + output);
    }

    motorControllerA->update();
    motorControllerB->update();
  }
}

void ZWallFollower::disable(){
  enabled = 0;
  pid.SetMode(MANUAL);
}

void ZWallFollower::enable(){
  enabled = 1;
  pid.SetMode(AUTOMATIC);
}
