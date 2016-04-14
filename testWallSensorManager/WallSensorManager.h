#ifndef WALLSENSORMANAGER_H
#define WALLSENSORMANAGER_H

#include "WallSensor.h"
#include "SpecialWallSensor.h"
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
		enum MotionState lastState;
		enum MotionState currentState;
    enum MotionState lastCommand;
    enum MotionState currentCommand;
		bool shouldSencondTurn();
		bool shouldFirstTurn();
		bool shouldRightTurn();
		bool shouldLeftTurn();
    bool shouldGoStraight();

	public:	
		WallSensorManager(int headpin, int side1pin, int side2pin);
		void initialize();
		bool checkState();
    bool isBalance();
    enum MotionState reportCurrent();
};

#endif
