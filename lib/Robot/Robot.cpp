#include <Robot.h>



Robot::Robot(Location& _loca, ZWallFollower& _wf, TurretController& _tc, Displayer& _dp):
	tc(_tc)
	,wf(_wf)
	,dp(_dp)
	,loca(_loca){

	}

Robot::~Robot(){

}

void Robot::initializing(){



}

void Robot::robotGO(){

}






void Robot::returnToOrigin(){

}
