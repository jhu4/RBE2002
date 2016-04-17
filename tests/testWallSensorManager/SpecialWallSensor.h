#ifndef SPECIALWALLSENSOR_H
#define SPECIALWALLSENSOR_H

#include "WallSensor.h"

class SpecialWallSensor: public WallSensor{
	private:

	public:
		SpecialWallSensor(int pin);
		bool isWall();
};
#endif
