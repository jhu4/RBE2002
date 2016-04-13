#include "WallSensorManager.h"
#include <Arduino.h>

WallSensorManager::WallSensorManager(int p, int p1, int p2):
head(p),side1(p1),side2(p2){

}

void WallSensorManager::initialize(){
	head.initialize();
	side1.initialize();
	side2.initialize();
}

enum MotionStatus WallSensorManager::reportNextState(){
  Serial.print(head.sense());
  Serial.print(" ");
//	Serial.print(side1.sense());
//  Serial.print(" ");
//	Serial.println(side2.sense());
//  head.sense();
  side1.sense();
  side2.sense();
  
	if(shouldLeftTurn()){
    lastState=currentState;
    currentState=TURN_LEFT;
		return TURN_LEFT;
	}
  else if(shouldRightTurn()){
    lastState=currentState;
    currentState=TURN_RIGHT;
    return TURN_RIGHT;
  }
	else if(shouldGoStraight()){
    lastState=currentState;
    currentState=GO_STRAIGHT;
		return GO_STRAIGHT;
	}
  else{
    lastState=currentState;
    currentState=TRANSITION;
    return TRANSITION;
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
	return (side1.isFindGap() && side2.isSame())||(side1.isGap() && side2.isSame());
}

bool WallSensorManager::shouldSencondTurn(){
	return side1.isGap() && side2.isGap();
}

bool WallSensorManager::shouldGoStraight(){
  return (side1.isWall() && side2.isWall())||(side1.isWall() && side2.isGap());
}

