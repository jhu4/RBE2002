#include <Robot.h>



Robot::Robot(FanController f, Displayer d, WallFollower w):
fancontroller(f),displayer(d),wallfollower(w),loca(new Locaiton()){

}

Robot::~Robot(){
	this->FanController.~FanController();
	this->Displayer.~Displayer();
	this->WallFollower.~WallFollower();
}

void Robot::initializing(){



}


void Robot::robotGO(){

}

