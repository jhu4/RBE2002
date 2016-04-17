#include <Robot.h>



Robot::Robot(Location& l, FanController f, Displayer d, WallFollower w,
	LightSensor ls):
	fancontroller(f)
	,location(l)
	,displayer(d)
	,wallfollower(w)
	,lightsensor(ls)
	,isfindCandle(false)
	,deltaX(0),deltaY(0),Z(0)
	,yawAngle(0),pitchAngle(0){

}

Robot::~Robot(){
	this->FanController.~FanController();
	this->Displayer.~Displayer();
	this->WallFollower.~WallFollower();
}

void Robot::initializing(){



}

void Robot::robotGO(){
	wallfollower.followTheWall();
	LightSensor.sense();
	if(lightsensor.isDetectLight() && !isfindCandle){
		isfindCandle=true;
		locateCandle();
		fancontroller.blowoff();
		displayer.display(location.getX()+deltaX,location.getY()+getY,Z);
	}
	if(isfindCandle && location.isOrigin()){
		wallfollower.stop();
	}
}




void Robot::locateCandle(){
	locateInYaw();
	locateInPitch();
}

void Robot::locateInYaw(){

}

void Robot::locateInPitch(){

}

void Robot::returnToOrigin(){

}
