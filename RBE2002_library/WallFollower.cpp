#include <WallFollower.h>
#include "WallSensorManager.h"

WallFollower::WallFollower(int pin1,int pin2,MotorController m1,MotorController m2,Location &l, int setpoint):
	wallsensors(pin1,pin2),mc1(m1),mc2(m2),loca(l),pid_setpoint(setpoint){

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
	pid = PID();
}


void WallFollower::followTheWall(){

}

void WallFollower::locateCandle(){

}

void WallFollower::stop(){
	mcOne.setspeed(0);
	mcTwo.setspeed(0);
}