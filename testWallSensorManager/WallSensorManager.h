#ifndef WALLSENSORMANAGER_H
#define WALLSENSORMANAGER_H

#include "WallSensor.h"

enum MotionStatus{
	TURN_RIGHT,
	TURN_LEFT,
	GO_STRAIGHT
};

class WallSensorManager{
	private:
		WallSensor head,side1,side2;
		enum MotionStatus lastState;
		enum MotionStatus currentState;
		bool shouldSencondTurn();
		bool shouldFirstTurn();
		bool shouldRightTurn();
		bool shouldLeftTurn();

	public:	
		WallSensorManager(int headpin, int side1pin, int side2pin);
		void initialize();
		enum MotionStatus reportNextState();
};

#endif
