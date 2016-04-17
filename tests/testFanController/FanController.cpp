#include "FanController.h"

FanController::FanController(int yaw, int pitch):
  _yaw(yaw), _pitch(pitch) {

}

void FanController::initialize() {
  yawServo.attach(_yaw);
  pitchServo.attach(_pitch);
  posPitch = 90;
  posYaw = 90;
  pitchServo.write(posPitch);
}

int FanController::reportPitchAngle() {

}

int FanController::reportYawAngle() {

}

float FanController::getCandleDistance() {

}

bool FanController::findCandle() {

}

bool FanController::up() {
  if (posPitch == 180) {
    return false;
  }
  else {
    posPitch++;
    pitchServo.write(posPitch);
    return true;
  }
}


bool FanController::down() {
  if (posPitch == 20) {
    return false;
  }
  else {
    posPitch--;
    pitchServo.write(posPitch);
    return true;
  }
}

bool FanController::left() {
  if (posYaw == 180) {
    return false;
  }
  else {
    posYaw++;
    pitchServo.write(posYaw);
    return true;
  }
}

bool FanController::right() {
  if (posYaw == 180) {
    return false;
  }
  else {
    posYaw++;
    pitchServo.write(posYaw);
    return true;
  }
}


