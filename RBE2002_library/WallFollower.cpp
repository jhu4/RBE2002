#include <WallFollower.h>
#include "WallSensorManager.h"

WallFollower::WallFollower(WallSensorManager& m,MotorController& mc1,MotorController& mc2,
	Location& Loca,LCD& lcd,double setpoint,int kp,int ki,int kd):
	mc1(m1),mc2(m2),
	loca(l),
	debugger(lcd),
	isStop(false),
	pid_in(0),pid_out(0),pid_setpoint(setpoint),
	pid(&pid_in,&pid_out,&pid_setpoint,kp,ki,kd){
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
	pid.SetSampleTime(10000); //need to be calculated
}


void WallFollower::followTheWall(){
	if(!isStop){
		if(m.checkState()){
			switch(m.reportCurrent()){
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
					debugger.display("WF::ftw");
					break;
			}
		}
	}
}

void WallFollower::stop(){
	pid.setMode(MANUAL);
	mc1.setspeed(0);
	mc2.setspeed(0);
	isStop=true;
}

void WallFollower::turnRight(){
	pid.setMode(MANUAL);

}

void WallFollower::turnLeft(){
	pid.setMode(MANUAL);
}