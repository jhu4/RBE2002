#ifndef WALLFOLLOWER_H
#define WALLFOLLOWER_H

#include <PID_v1.h>
#include "Location.h"
#include "MotorController.h"
#include "WallSensorManager.h"
#include "LightSensor.h"

class WallFollower{
	private:
		WallSensorManager m;
		MotorController mc1, mc2;
		PID pid;
		Location Loca;
		LCD debugger;
		bool isStop;
		double pid_in;
		double pid_out;
		double pid_setpoint;
		void forward();
		void backward();
		void turnRight();
		void turnLeft();

	public:
		WallFollower(WallSensorManager& m,MotorController& mc1,MotorController& mc2,
			Location& Loca,LCD& lcd,double setpoint,int kp,int ki,int kd);
		~WallFollower();
		void initialize();
		void followTheWall();
		void stop();
};

#endif
