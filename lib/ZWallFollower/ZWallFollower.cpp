#include "ZWallFollower.h"
#include "LCD.h"

//LCD* lcd = new LCD(40,41,42,43,44,45);

ZWallFollower::ZWallFollower(DistanceSensor* distSenseA, DistanceSensor* distSenseB, DistanceSensor* distSenseC,
  MotorController* motorControllerA, MotorController* motorControllerB,
  double distance, double biasSpeed, double kp, double ki, double kd):
  distSenseA(distSenseA),
  distSenseB(distSenseB),
  distSenseC(distSenseC),
  motorControllerA(motorControllerA),
  motorControllerB(motorControllerB),
  distance(distance),
  biasSpeed(biasSpeed),
  output(0),
  input(0),
  pid(&input,&output,&(this->distance),kp,ki,kd,DIRECT),
  enabled(1),
  lastTime(millis()),
  ADone(1),
  BDone(1),
  leftTurn(1){
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

    distSenseC->getDistance();
    if((distSenseC->getAverage() < 11) && (ADone && BDone)){

      ADone = false;
      BDone = false;

      leftTurn = true;
    }

    if((distSenseB->getDistance() > 240) && (ADone && BDone)){

      ADone = false;
      BDone = false;

      leftTurn = false;
    }

    if (!ADone){
      if (leftTurn){
        ADone = motorControllerA->moveTicks(-1600, -200);
      } else {
        ADone = motorControllerA->moveTicks(3200, 200);
      }
		}
		if (!BDone){
      if (leftTurn){
        BDone = motorControllerB->moveTicks(1600, 100);
      } else{
        BDone = motorControllerB->moveTicks(1600, 100);
      }
		}

    if((ADone && BDone) && pid.Compute()){

      input = getDistance();

      motorControllerA->setSpeed(biasSpeed - output);
      motorControllerB->setSpeed(biasSpeed + output);
    }
  }
  motorControllerA->update();
  motorControllerB->update();
}

void ZWallFollower::disable(){
  enabled = 0;
  pid.SetMode(MANUAL);
}

void ZWallFollower::enable(){
  enabled = 1;
  pid.SetMode(AUTOMATIC);
}
