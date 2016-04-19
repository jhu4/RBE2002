#include "MotorController.h"

MotorController::MotorController(Motor motor, Encoder encoder):
motor(motor),
encoder(encoder){
}

void MotorController::update(){

}

float MotorController::getSpeed(){
	return encoder->getTicks();
}

MotorController::~MotorController(){}
