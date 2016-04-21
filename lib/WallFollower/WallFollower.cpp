#include "WallFollower.h"

WallFollower::WallFollower(WallSensorManager& m_in, MotorController& m1, MotorController& m2, Location& l, LCD& lcd,double kp,double ki, double kd, int s):
	m(m_in)
	,mc1(m1),mc2(m2)
	,loca(l)
	,debugger(lcd)
	,speed(s)
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
				debugger.display("RIGHT");
				break;
			case SECOND_RIGHT_TURN:
				turnRight();
				debugger.display("2ND RIGHT");
				break;
			case TURN_LEFT:
       	turnLeft();
				debugger.display("LEFT");
				break;
			case GO_STRAIGHT:
       	forward();
				debugger.display("STRAIGHT");
				break;
			default:
				stop();
				break;
		}

	}
	if(pid.GetMode()==AUTOMATIC){
		debugger.display(999);
	}
	if(pid.GetMode()==MANUAL){
		debugger.display(-11);
	}
	// m.checkState();
	if(pid.Compute()){;
    pid_in = m.getDistance1()-m.getDistance2();
    debugger.display(m.getDistance1()-m.getDistance2(),pid_out);
    mc1.setSpeed(speed-pid_out/2);
    mc2.setSpeed(speed+pid_out/2);
  }
  mc1.update();
  mc2.update();
}

void WallFollower::stop(){
	mc1.setSpeed(0);
	mc2.setSpeed(0);
	pid.SetMode(MANUAL);
}

void WallFollower::turnRight(){
  mc1.setSpeed(speed*1.5);
  mc2.setSpeed(speed*0.5);
	pid.SetMode(MANUAL);
}

void WallFollower::turnLeft(){
  mc1.setSpeed(-speed);
  mc2.setSpeed(speed);
	pid.SetMode(MANUAL);
}

void WallFollower::forward(){
	mc1.setSpeed(speed);
	mc2.setSpeed(speed);
	pid.SetMode(AUTOMATIC);
}


void WallFollower::backward(){
	mc1.setSpeed(-speed);
	mc2.setSpeed(speed);
	pid.SetMode(AUTOMATIC);
}
