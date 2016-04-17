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
		void forward();
		void backward();
		void turnRight();
		void turnLeft();

	public:
		WallFollower(WallSensorManager& m, MotorController& mc1, MotorController& mc2, Location& Loca, LCD& lcd,int& pid_in, int& pid_out);
		~WallFollower();
		void initialize();
		void followTheWall();
		void stop();
};

#endif
