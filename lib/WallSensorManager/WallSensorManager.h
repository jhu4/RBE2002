#ifndef WALLSENSORMANAGER_H
#define WALLSENSORMANAGER_H

#include "WallSensor.h"
#include "SpecialWallSensor.h"
#include "LCD.h"

enum MotionState{
	TURN_RIGHT,
	SECOND_RIGHT_TURN,
	TURN_LEFT,
	GO_STRAIGHT,
  TRANSITION
};

class WallSensorManager{
	private:
		WallSensor side1,side2;
    SpecialWallSensor head;
    LCD& debugger;
    enum MotionState lastCommand;
    enum MotionState currentCommand;
    int data1, data2;
    float distance1,distance2;
		bool shouldSencondTurn();
		bool shouldFirstTurn();
		bool shouldRightTurn();
		bool shouldLeftTurn();
    bool shouldGoStraight();

	public:
		WallSensorManager(int headpin, int side1pin, int side2pin,LCD& lcd);
		void initialize();
		bool checkState();
    enum MotionState getState();
    void mapDistance();
    float getDistance1();
    float getDistance2();
};

#endif
