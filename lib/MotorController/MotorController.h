#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "Motor.h"
#include "Encoder.h"
#include "PID_v1.h"

#define TICKTOMM 0.0687223393

class MotorController{
	private:
		Motor* motor;
		Encoder* encoder;
		unsigned long prevTime;
		double input;
		double output;
		double setPoint;
		long tickDistance;
		PID pid;

	public:

		MotorController(Motor* motor, Encoder* encoder, double kp, double ki, double kd);
		double getSpeed();
		void setSpeed(double speed);
		void update();
		long getTickDistance();
		~MotorController();

};

#endif
