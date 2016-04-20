#include <WallFollower.h>
#include "WallSensorManager.h"

WallFollower::WallFollower(WallSensorManager& m,MotorController& m1,MotorController& m2,Location& l,PID& pid_in,LCD& lcd)
	mc1(m1),mc2(m2),
	loca(l),
	debugger(lcd),
	pid(pid_in){

}

WallFollower::~WallFollower(){
	wallsensors.~WallSensor();
	mc1.~MotorController();
	mc2.~MotorController();

	location.~Location();
}

void WallFollower::initializing(){
	m.initialize();
	mc1.initialize();
	mc2.initialize();
	pid.SetOutputLimits(0,80);
	pid.SetSampleTime(10000);
}


void WallFollower::followTheWall(){
	if(m.checkState()){
		switch(m.getState()){
			case TURN_RIGHT:
				turnRight();
				break;
			case SECOND_RIGHT_TURN:
				turnRight();
				break;
			case TURN_LEFT:
				turnLeft();
				break;
			case GO_STRAIGHT:
				forward();
				break;
			default:
				break;
		}
	}
	m1.update();
	m2.update();
}


void WallFollower::stop(){
	mc1.setspeed(0);
	mc2.setspeed(0);
}

void WallFollower::turnRight(){
	pid.setMode(MANUAL);
	m1.setspeed(-110);
	m2.setspeed(110);
}

void WallFollower::turnLeft(){
	pid.setMode(MANUAL);
	m2.setspeed(-110);
	m1.setspeed(110);
}

void forward(){
	pid.setMode(AUTOMATIC);
	m1.setspeed(110);
	m2.setspeed(110);
}


void backward(){
	pid.setMode(AUTOMATIC);
}
