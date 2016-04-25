#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "Motor.h"
#include "Encoder.h"
#include "PID_v1.h"

//#define TICKTOMM 0.0687223393

#define TICKTOMM 0.0697223393

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
		bool inMove;
		long startTick;

	public:

		MotorController(Motor* motor, Encoder* encoder, double kp, double ki, double kd);
		double getSpeed();
		void setSpeed(double speed);
		void update();
		long getTickDistance();
		bool moveTicks(int ticks, int speed);
		~MotorController();

};

#endif
