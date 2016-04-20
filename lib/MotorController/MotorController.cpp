#include "MotorController.h"
#define TICKTOMM 0.0687223393


MotorController::MotorController(Motor* motor, Encoder* encoder, double kp, double ki, double kd):
motor(motor),
encoder(encoder),
prevTime(0),
input(0),
output(0),
setPoint(0),
pid(&input,&output,&setPoint,kp,ki,kd, DIRECT){
	pid.SetOutputLimits(-255, 255);
	//pid.SetOutputLimits(0, 510);
	//pid.SetControllerDirection(DIR);
	pid.SetMode(AUTOMATIC);
}


void MotorController::setSpeed(double speed){
	setPoint = speed;
}

void MotorController::update(){
	if (pid.Compute()){
		input = (this->getSpeed());
		motor->setSpeed(output);
		// if (setPoint != 0){
		// 	Serial.print(setPoint);
		// 	Serial.print(",\t\t");
		// 	Serial.print(input);
		// 	Serial.print(",\t\t");
		// 	Serial.println(output);
		// }

		//Serial.print("\t\t");
	}
}

//mm per sec
double MotorController::getSpeed(){

	unsigned long currTime = micros();
	int ticks = encoder->read();
	encoder->write(0);

	// robot forward is encoder negative
	// if (!motor->isInvert()){
	// 	ticks = -ticks;
	// }
	float secs = (float(currTime-prevTime)/1000000);
	prevTime = currTime;
	return ticks*TICKTOMM/secs;
}

MotorController::~MotorController(){}
