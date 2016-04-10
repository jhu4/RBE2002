#ifndef WALLFOLLOWER_H
#define WALLFOLLOWER_H

#include <PID_v1.h>
#include <Location>
#include <MotorController>

class WallFollower{
	private:
		WallSensors wallsensors;
		MotorController mcOne, mcTwo;
		PID pid;
		Location Loca;

		void turnRight();
		void turnLeft();

	public:
		WallFollower(int pin1, int pin2, MotorController mc1, MotorController mc2, Location Loca);
		~WallFollower();
		void initializing();
		void followTheWall();
		void locateCandle();
		void stop();
};

#endif
