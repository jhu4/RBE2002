#ifndef WALLFOLLOWER_H
#define WALLFOLLOWER_H
#include <Arduino.h>
#include <PID_v1.h>
#include "Location.h"
#include "MotorController.h"
#include "WallSensorManager.h"
#include "LightSensor.h"
class WallFollower{
	private:
		WallSensorManager& m;
		MotorController& mc1;
		MotorController& mc2;
		Location& loca;
		LCD& debugger;
		int speed;
		bool isStop;
		double pid_in;
		double pid_out;
		double pid_setpoint;
		void forward();
		void backward();
		void turnRight();
		void turnLeft();
		PID pid;

	public:
		WallFollower(WallSensorManager& m, MotorController& mc1, MotorController& mc2, Location& Loca, LCD& lcd,double kp, double ki, double kd,int s);
		~WallFollower();
		void initialize();
		void followTheWall();
		void stop();
};

#endif
