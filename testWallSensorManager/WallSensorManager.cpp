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

bool WallSensorManager::checkState(){
//  Serial.print(head.sense());
//  Serial.print(" ");
//	Serial.print(side1.sense());
//  Serial.print(" ");
//	Serial.println(side2.sense());
  head.sense();
  data1=side1.sense();
  data2=side2.sense();

	if(shouldLeftTurn() && currentCommand!=TURN_LEFT){
    lastCommand=currentCommand;
    currentCommand=TURN_LEFT;
    return true;
	}
  if(shouldFirstTurn() && currentCommand!=TURN_RIGHT){
    lastCommand=currentCommand;
    currentCommand=TURN_RIGHT;
    return true;
  }
  if(shouldSencondTurn() && currentCommand==TURN_RIGHT){
    lastCommand=currentCommand;
    currentCommand=SECOND_RIGHT_TURN;
    return true;
  }
	if(shouldGoStraight() && currentCommand!=GO_STRAIGHT){
    lastCommand=currentCommand;
    currentCommand=GO_STRAIGHT;
    return true;
	}
  return false;
}

enum MotionState WallSensorManager::reportCurrent(){
  return currentCommand;
}

int WallSensorManager::reportDifference(){
  return (data1-data2);
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
  return ((side1.isWall() && side2.isWall())||(side1.isWall() 
            && side2.isGap()))&&(side1.isSame() && side2.isSame());
}

