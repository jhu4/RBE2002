#include "WallSensorManager.h"

WallSensorManager::WallSensorManager(int p, int p1, int p2):
head(p),side1(p1),side2(p2){

}

void WallSensorManager::initializing(){
	head.initializing();
	side1.initializing();
	side2.initializing();
}

enum MotionStatus WallSensorManager::reportStatus(){
	head.sense();
	side1.sense();
	side2.sense();

	if(shouldRightTurn()){
		return TURN_RIGHT;
	}
	else if(shouldLeftTurn()){
		return TURN_LEFT;
	}
	else{
		return GO_STRAIGHT;
	}
}

/* Private */
bool WallSensorManager::shouldRightTurn(){
	return (shouldFirstTurn()||shouldSencondTurn());
}

bool WallSensorManager::shouldLeftTurn(){
	return (head.isWall() && side1.isWall() && side2.isWall());
}

bool WallSensorManager::shouldFirstTurn(){
	return side1.isFindGap() && side2.isSame();
}

bool WallSensorManager::shouldSencondTurn(){
	return side1.isGap() && side2.isGap();
}
