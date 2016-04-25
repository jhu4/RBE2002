#include "TurretController.h"
TurretController::TurretController(int yaw, int pitch, Fan& _fan,LightSensor& _ls):
  _yaw(yaw)
  , _pitch(pitch)
  ,yawAngle(0),pitchAngle(0)
  ,posPitch(120),posYaw(0)
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

bool TurretController::updownScan(){
  if(millis()>=time){
    if(pitchDirection==UP){
        up();
        if(ls.sense()){
          return true;
        }
    }
    if(pitchDirection==DOWN){
        down();
        if(ls.sense()){
          return true;
        }
    }
    time = millis()+TICKTIME;
  }
  return false;
}


bool TurretController::up() {
    if (posPitch >= 180) {
      pitchDirection=DOWN;
      return false;
    }
    posPitch+=HALFANGLE;
    pitchServo.write(posPitch);
    return true;
}

bool TurretController::down() {
    if (posPitch <= 0) {
      pitchDirection=UP;
      return false;
    }
    posPitch-=HALFANGLE;
    pitchServo.write(posPitch);
    return true;
}

bool TurretController::left() {
    if (posYaw <= 0) {
      yawDirection=RIGHT;
      return false;
    }
    posYaw-=HALFANGLE;
    yawServo.write(posYaw);
    return true;
}

bool TurretController::right() {
    if (posYaw >= 180) {
      yawDirection=LEFT;
      return false;
    }
    posYaw+=HALFANGLE;
    yawServo.write(posYaw);
    return true;
}

int TurretController::getPitchAngle() {
  return posPitch;
}

int TurretController::getYawAngle() {
  return posYaw;
}
