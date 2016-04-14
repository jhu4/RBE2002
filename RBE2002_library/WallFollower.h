#ifndef WALLFOLLOWER_H
#define WALLFOLLOWER_H

#include <PID_v1.h>
#include <Location>
#include <MotorController>

class WallFollower{
	private:
		WallSensors wallsensors;
		MotorController mc1, mc2;
		PID pid;
		Location Loca;
		int pid_in;
		int pid_out;
		int pid_setpoint


	public:
		WallFollower(int pin1, int pin2, MotorController mc1, MotorController mc2, Location Loca);
		~WallFollower();
		void initialize();
		void followTheWall();
		void locateCandle();
		void stop();
};

#endif
