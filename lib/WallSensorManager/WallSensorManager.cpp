#include "WallSensorManager.h"
#include <Arduino.h>

WallSensorManager::WallSensorManager(int p, int p1, int p2, LCD& lcd):
  head(p),side1(p1),side2(p2)
  ,distance1(0),distance2(0)
  ,debugger(lcd){

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
  // Serial.print(data2);
  // Serial.print("\t");

	if(shouldLeftTurn() && currentCommand!=TURN_LEFT){
    lastCommand=currentCommand;
    currentCommand=TURN_LEFT;
    return true;
	}
  if(shouldFirstTurn() && currentCommand!=TURN_RIGHT && currentCommand!=SECOND_RIGHT_TURN){
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
            && side2.isGap()))&&(side1.isSame() && side2.isSame())&&(!head.isWall());
}

//need math calculation
void WallSensorManager::mapDistance(){
  float one = side1.getReading();
  float two = side2.getReading();

  if(one<=576 && one>394){
    distance1=(940-one)/91; 
  }
  if(one<=394 && one>293){
    distance1=(1394-2*one)/101;
  }
  if(one<=293 && one>100){
//    distance1=(6.51-log(one))/0.1;
      distance1=(6.51-log(one))/0.1-1;
  }
  if(one<=100 && one>70){
    distance1=100/3-2*one/15;
  }
  if(one<=70 && one>=40){
    distance1=38-one/5;
  }
  if(one<40){
    distance1=0;
    debugger.display("WM:mD:one");
  }
  /////
  if(two<=542 && two>378){
    distance2=435/41-two/82;
  }
  if(two<=378 && two>294){
    distance2=15-two/42;
  }
  if(two<=294 && two>134){
//    distance2=(6.2-log(two))/0.066;
      distance2=(6.2-log(two))/0.066-1;
  }
  if(two<=134 && two>118){
    distance2=107/2-two/4;
  }
  if(two<=118 && two>=100){
    distance2=190/3-two/3;
  }
  if(two<100){
    distance2=0;
    debugger.display("WM:mD:two");
  }
}

float WallSensorManager::getDistance1(){
  return distance1;
}

float WallSensorManager::getDistance2(){
  return distance2;
}
