#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "Motor.h"
#include "Encoder.h"
#include "PID_v1.h"

class MotorController{
	private:
		Motor* motor;
		Encoder* encoder;
		unsigned long prevTime;
		double input;
		double output;
		double setPoint;
		PID pid;

	public:

		MotorController(Motor* motor, Encoder* encoder, double kp, double ki, double kd);
		double getSpeed();
		void setSpeed(double speed);
		void update();
		double getOutput();
		~MotorController();

};

#endif
