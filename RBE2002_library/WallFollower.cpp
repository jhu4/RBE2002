#include <WallFollower.h>
#include "WallSensorManager.h"

WallFollower::WallFollower(int pin1, int pin2, MotorController mc1, MotorController mc1, Location l):
wallsensors(new WallSensor(pin1,pin2)), mcOne(mc1), mcTwo(mc2), pid(new PID), loca(l){

}

WallFollower::~WallFollower(){
	wallsensors.~WallSensor();
	mcOne.~MotorController();
	mcTwo.~MotorController();
	location.~Location();
}

void WallFollower::initializing(){
	WallSensorManager.initialize();
	mcOne.initialize();
	mcTwo.initialize();
}


void WallFollower::followTheWall(){

}

void WallFollower::locateCandle(){

}

void WallFollower::stop(){

}