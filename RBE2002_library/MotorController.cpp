#include <MotorController.h>

MotorController::MotorController(int motorpin, int motordirectionpin, int encoderpin1, int encoderpin2):
motor(motorpin, motordirectionpin),encoder(encoderpin1,encoderpin2){

}

MotorController::~MotorController(){

}



float MotorController::reportDeltaX(){

}

float MotorController::reportDeltaY(){

}


void setSpeed(float speed){

}


