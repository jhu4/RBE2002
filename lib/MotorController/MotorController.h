#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "Motor.h"
#include "Encoder.h"
#include "PID_v1.h"

class MotorController{
	private:
		Motor motor;
		Encoder encoder;

	public:
		MotorController(Motor motor, Encoder encoder);
		float setSpeed();
		~MotorController();

};

#endif
