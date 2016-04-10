#include <WallFollower.h>


WallFollower::WallFollower(int pin1, int pin2, MotorController mc1, MotorController mc1, Location l):
wallsensors(new WallSensor(pin1,pin2)), mcOne(mc1), mcTwo(mc2), pid(new PID), loca(l){

}

WallFollower::~WallFollower(){
	this->wallsensors.~WallSensor();
	this->mcOne.~MotorController();
	this->mcTwo.~MotorController();
	this->location.~Location();
}

void WallFollower::initializing(){
	WallSensor->initializing();
	MotorController->initializing();
}


void WallFollower::followTheWall(){

}

void WallFollower::locateCandle(){

}

void WallFollower::stop(){

}