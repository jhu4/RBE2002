#include "FanController.h"

FanController::FanController(int yaw, int pitch, int _fan,LightSensor& _ls):
  _yaw(yaw)
  , _pitch(pitch)
  ,yawAngle(0),pitchAngle(0)
  ,posPitch(0),posYaw(0)
  ,fan(_fan),ls(_ls){

}

void FanController::initialize() {
  fan.initialize();
  ls.initialize();
  yawServo.attach(_yaw);
  pitchServo.attach(_pitch);
  yawServo.write(posPitch);
  pitchServo.write(posYaw);
}

float FanController::getCandleDistance() {
  return ls.getDistance();
}

void FanController::findCandle() {
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

bool FanController::up() {
  if (posPitch == 180) {
    posPitch=0;
    return false;
  }
  else {
    posPitch+=HALFANGLE;
    pitchServo.write(posPitch);
    return true;
  }
}

bool FanController::down() {
  if (posPitch == 0) {
    posPitch=180;
    return false;
  }
  else {
    posPitch-=HALFANGLE;
    pitchServo.write(posPitch);
    return true;
  }
}

bool FanController::left() {
  if (posYaw == 0) {
    posYaw=180;
    return false;
  }
  else {
    posYaw-=HALFANGLE;
    pitchServo.write(posYaw);
    return true;
  }
}

bool FanController::right() {
  if (posYaw == 180) {
    posYaw=0;
    return false;
  }
  else {
    posYaw+=HALFANGLE;
    pitchServo.write(posYaw);
    return true;
  }
}

int FanController::getPitchAngle() {
  return pitchAngle;
}

int FanController::getYawAngle() {
  return yawAngle;
}

Fan::Fan(int p):pin(p){

}

void Fan::initialize(){
  pinMode(pin,OUTPUT);
}

void Fan::on(){
  digitalWrite(pin,HIGH);
}

void Fan::off(){
  digitalWrite(pin,LOW);
}
