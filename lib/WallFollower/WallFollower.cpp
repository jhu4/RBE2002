#include "WallFollower.h"

WallFollower::WallFollower(WallSensorManager& m_in, MotorController& m1, MotorController& m2, Location& l, LCD& lcd,double& pid_i, double& pid_o):
	m(m_in)
	,mc1(m1),mc2(m2)
	,loca(l)
	,debugger(lcd)
	,pid_in(pid_i),pid_out(pid_o),pid_setpoint(0)
  ,pid(&pid_in,&pid_out,&pid_setpoint,5,0,0,DIRECT){
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
  pid.SetOutputLimits(-30, 30);
  pid.SetSampleTime(100); //10Hz
  forward();
}


void WallFollower::followTheWall(){
	if(m.checkState()){
   Serial.println("CheckState");
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
				break;
		}
	}
  if(pid.Compute()){;
    pid_in = m.getDistance1()-m.getDistance2();
    debugger.display(m.getDistance1()-m.getDistance2(),0.0);
    debugger.display(pid_out);
    mc1.setSpeed(120-pid_out);
    mc2.setSpeed(120);
  }
  mc1.update();
  mc2.update();
}

void WallFollower::stop(){
	mc1.setSpeed(0);
	mc2.setSpeed(0);
}

void WallFollower::turnRight(){
	pid.SetMode(MANUAL);
  mc1.setSpeed(120);
  mc2.setSpeed(0);
}

void WallFollower::turnLeft(){
	pid.SetMode(MANUAL);
  mc1.setSpeed(0);
  mc2.setSpeed(120);
}

void WallFollower::forward(){
	pid.SetMode(AUTOMATIC);
	mc1.setSpeed(120);
  mc2.setSpeed(120);
}


void WallFollower::backward(){
	pid.SetMode(AUTOMATIC);
}
