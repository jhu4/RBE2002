#include "TurretController.h"
TurretController::TurretController(int yaw, int pitch, Fan& _fan,LightSensor& _ls):
  index(0)
  ,_yaw(yaw), _pitch(pitch)
  ,yawMinReading(2000),pitchMinReading(2000)
  ,yawAngle(0),pitchAngle(0)
  ,posPitch(139),posYaw(0)
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

bool TurretController::findCandleScan() {
  if(millis()>=time){
    if(yawDirection==RIGHT){
        right();
    }
    else{
      left();
    }
    ls.sense();
    if(index==0){
      yawMinReading = ls.getReading();
      yawAngle = posYaw;
    }
    if(ls.getReading()<yawMinReading){
      yawMinReading = ls.getReading();
      yawAngle = posYaw;
    }
    index++;
    time = millis()+TICKTIME;
  }

  if(index==INDEX){
    return true;
  }
  return false;
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
    Serial.println(posPitch);
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
    Serial.println(posPitch);
    time = millis()+TICKTIME;
  }
  return false;
}


bool TurretController::up() {
    if (posPitch >= 167) {
      pitchDirection=DOWN;
      return false;
    }
    posPitch+=HALFANGLE;
    pitchServo.write(posPitch);
    return true;
}

bool TurretController::down() {
    if (posPitch <= 139) {
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
