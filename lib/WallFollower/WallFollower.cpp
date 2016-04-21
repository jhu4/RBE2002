#include "WallFollower.h"

WallFollower::WallFollower(WallSensorManager& m_in, MotorController& m1, MotorController& m2, Location& l, LCD& lcd,double kp,double ki, double kd, int s):
	m(m_in)
	,mc1(m1),mc2(m2)
	,loca(l)
	,debugger(lcd),speed(s)
	,pid_in(0),pid_out(0),pid_setpoint(0)
  ,pid(&pid_in,&pid_out,&pid_setpoint,kp,ki,kd,DIRECT){
}

WallFollower::~WallFollower(){
	m.~WallSensorManager();
	mc1.~MotorController();
	mc2.~MotorController();
	loca.~Location();
}

void WallFollower::initialize(){
	m.initialize();
	mc1.initialize();
	mc2.initialize();
  debugger.initialize();
  pid.SetOutputLimits(-100, 100);
  pid.SetSampleTime(100); //10Hz
  forward();
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
	// m.checkState();
  if(pid.Compute()){;
    pid_in = m.getDistance1()-m.getDistance2();
    debugger.display(m.getDistance1()-m.getDistance2(),pid_out);
		if(m.getState()==TURN_RIGHT){
			debugger.display("RIGHT");
		}
		if(m.getState()==TURN_LEFT){
			debugger.display("LEFT");
		}
		if(m.getState()==GO_STRAIGHT){
			debugger.display("STRAIGHT");
		}
		if(m.getState()==SECOND_RIGHT_TURN){
			debugger.display("2ND R");
		}
    mc1.setSpeed(speed-pid_out/2);
    mc2.setSpeed(speed+pid_out/2);
  }
  mc1.update();
  mc2.update();
}

void WallFollower::stop(){
	pid.SetMode(MANUAL);
	mc1.setSpeed(0);
	mc2.setSpeed(0);
}

void WallFollower::turnRight(){
	pid.SetMode(MANUAL);
  mc1.setSpeed(speed*2);
  mc2.setSpeed(-speed*2);
}

void WallFollower::turnLeft(){
	pid.SetMode(MANUAL);
  mc1.setSpeed(-speed*2);
  mc2.setSpeed(speed*2);
}

void WallFollower::forward(){
	pid.SetMode(AUTOMATIC);
	mc1.setSpeed(speed);
  mc2.setSpeed(speed);
}


void WallFollower::backward(){
	pid.SetMode(AUTOMATIC);
	mc1.setSpeed(-speed);
	mc2.setSpeed(speed);
}
