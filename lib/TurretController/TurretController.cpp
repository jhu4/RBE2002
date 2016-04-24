#include "TurretController.h"
TurretController::TurretController(int yaw, int pitch, Fan& _fan,LightSensor& _ls):
  _yaw(yaw)
  , _pitch(pitch)
  ,yawAngle(0),pitchAngle(0)
  ,posPitch(0),posYaw(0)
  ,time(0)
  ,yawDirection(RIGHT),pitchDirection(UP)
  ,fan(_fan),ls(_ls){

}

void TurretController::initialize() {
  fan.initialize();
  ls.initialize();
  yawServo.attach(_yaw);
  pitchServo.attach(_pitch);
  yawServo.write(posYaw);
  pitchServo.write(posPitch);
}

float TurretController::getCandleDistance() {
  return ls.getDistance();
}

void TurretController::findCandle() {
  int yawMax = 0;
  int pitchMax = 0;

  for(int i=0;i<INDEX;i++){
    if(right()){
      ls.sense();
      if(ls.getReading()>yawMax){
        yawMax=ls.getReading();
      }
    }
  }

  for(int i=0;i<INDEX;i++){
    if(up()){
      ls.sense();
      if(ls.getReading()>pitchMax){
        pitchMax=ls.getReading();
      }
    }
  }

  yawAngle=yawMax;
  pitchAngle=pitchMax;
}

bool TurretController::scan(){
  if(millis()>=time){
    if(yawDirection==RIGHT){
        right();
        if(ls.sense()){
          return true;
        }
    }
    if(yawDirection==LEFT){
        left();
        if(ls.sense()){
          return true;
        }
    }
    time = millis()+TICKTIME;
  }
  return false;
}

bool TurretController::up() {
    posPitch+=HALFANGLE;
    pitchServo.write(posPitch);
    if (posPitch == 180) {
      posPitch=0;
      pitchDirection=DOWN;
      return false;
    }
    return true;
}

bool TurretController::down() {
    posPitch-=HALFANGLE;
    pitchServo.write(posPitch);
    if (posPitch == 0) {
      posPitch=180;
      pitchDirection=UP;
      return false;
    }
    return true;
}

bool TurretController::left() {
    posYaw-=HALFANGLE;
    yawServo.write(posYaw);
    if (posYaw == 0) {
      yawDirection=RIGHT;
      return false;
    }
    return true;
}

bool TurretController::right() {
    posYaw+=HALFANGLE;
    yawServo.write(posYaw);
    if (posYaw == 180) {
      yawDirection=LEFT;
      return false;
    }
    return true;
}

int TurretController::getPitchAngle() {
  return pitchAngle;
}

int TurretController::getYawAngle() {
  return yawAngle;
}
