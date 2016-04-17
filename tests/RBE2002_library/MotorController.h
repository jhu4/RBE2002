#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <Motor.h>
#include <Encoder.h>
#include <PID_v1.h>

class MotorController{
	private:
		Motor motor;
		Encoder encoder;
		PID pid;

	public:
		MotorController(int motorpin, int motordirectionpin, int encoderpin1, int encoderpin2);
		~MotorController();
		float reportDeltaX();
		float reportDeltaY();
		void setSpeed(float speed);
};

#endif
