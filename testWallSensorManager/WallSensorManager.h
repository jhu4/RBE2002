#ifndef WALLSENSORMANAGER_H
#define WALLSENSORMANAGER_H

#include "WallSensor.h"
#include "SpecialWallSensor.h"
enum MotionStatus{
	TURN_RIGHT,
	TURN_LEFT,
	GO_STRAIGHT,
  TRANSITION
};

class WallSensorManager{
	private:
		WallSensor side1,side2;
   SpecialWallSensor head;
		enum MotionStatus lastState;
		enum MotionStatus currentState;
		bool shouldSencondTurn();
		bool shouldFirstTurn();
		bool shouldRightTurn();
		bool shouldLeftTurn();
    bool shouldGoStraight();

	public:	
		WallSensorManager(int headpin, int side1pin, int side2pin);
		void initialize();
		enum MotionStatus reportNextState();
};

#endif
