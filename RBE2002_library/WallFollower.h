#ifndef WALLFOLLOWER_H
#define WALLFOLLOWER_H

#include <PID_v1.h>
#include "Location.h"
#include "MotorController.h"
#include "WallSensorManager.h"

class WallFollower{
	private:
		WallSensorManager m;
		MotorController mc1, mc2;
		PID pid;
		Location Loca;
		LCD debugger;
		void turnRight();
		void turnLeft();

	public:
		WallFollower(WallSensorManager& m, MotorController& mc1, MotorController& mc2, Location& Loca, PID& pid, LCD& lcd);
		~WallFollower();
		void initialize();
		void followTheWall();
		void locateCandle();
		void stop();
};

#endif
