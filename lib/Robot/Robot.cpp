#include <Robot.h>



Robot::Robot(Location& _loca, ZWallFollower& _wf, TurretController& _tc, Displayer& _dp):
	isFindCandle(false),isYawScanEnded(false),isPitchScanEnded(false)
	,tc(_tc)
	,wf(_wf)
	,displayer(_dp)
	,loca(_loca){

	}

void Robot::initializing(){
	tc.initialize();
	displayer.initialize();
}

void Robot::robotGO(){
	wf.update();
	if(tc.updownScan()){

	}
}


void Robot::returnToOrigin(){
	wf.update();
	displayer.LEDon();
}

Robot::~Robot(){

}
