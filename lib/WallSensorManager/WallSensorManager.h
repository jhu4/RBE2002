#ifndef WALLSENSORMANAGER_H
#define WALLSENSORMANAGER_H

#include "WallSensor.h"
#include "LCD.h"
#include <Arduino.h>

enum MotionState{
	TURN_RIGHT,
	SECOND_RIGHT_TURN,
	TURN_LEFT,
	GO_STRAIGHT,
  TRANSITION
};

class WallSensorManager{
	private:
		WallSensor& side1,side2,head;
    LCD& debugger;
    enum MotionState lastCommand;
    enum MotionState currentCommand;
    int data1, data2;
		int delay;
		unsigned long endtime;
    float distance1,distance2;
		bool shouldSencondTurn();
		bool shouldFirstTurn();
		bool shouldRightTurn();
		bool shouldLeftTurn();
    bool shouldGoStraight();
		bool isTransition();

	public:
		WallSensorManager(WallSensor& head,WallSensor& side1,WallSensor& side2,LCD& lcd,int delay);
		void initialize();
		bool checkState();
    enum MotionState getState();
    void mapDistance();
    float getDistance1();
    float getDistance2();
};

#endif
