#include "MotorController.h"



MotorController::MotorController(Motor* motor, Encoder* encoder, double kp, double ki, double kd):
motor(motor),
encoder(encoder),
prevTime(0),
input(0),
output(0),
setPoint(0),
tickDistance(0),
pid(&input,&output,&setPoint,kp,ki,kd,DIRECT),
inMove(0),
startTick(0){
	pid.SetOutputLimits(-255, 255);
	pid.SetMode(AUTOMATIC);
}

void MotorController::setSpeed(double speed){
	setPoint = speed;
}

void MotorController::update(){
	if (pid.Compute()){
		input = (this->getSpeed());
		motor->setSpeed(output);
	}
}

double MotorController::getSpeed(){

	unsigned long currTime = micros();
	int ticks = encoder->read();
	encoder->write(0);
	if (motor->isInvert()){
		ticks = -ticks;
	}
	tickDistance = tickDistance + ticks;

	float secs = (float(currTime-prevTime)/1000000);
	prevTime = currTime;
	return ticks*TICKTOMM/secs;
}


long MotorController::getTickDistance(){
	return tickDistance;
}

bool MotorController::moveTicks(int ticks, int speed){
	if (inMove){
		//this->update();
	} else{
		this->setSpeed(speed);
		inMove = true;
		startTick = this->getTickDistance();
	}

	bool isDone = false;
	if (ticks < 0){
		isDone = ((this->getTickDistance() - startTick) <= ticks);
	} else {
		isDone = ((this->getTickDistance() - startTick) >= ticks);
	}

	if (isDone){
		inMove = false;
		this->setSpeed(0);
		return true;
	}
	return false;
}

MotorController::~MotorController(){}
