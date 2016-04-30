/*
MotorController class to controll high level motor functions
Motor.cpp
high level motor operations

author: Zachary Armsby
*/

#include "MotorController.h"

// initalize motor controller and start pid
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

// set the speed/ setpoint for pid
void MotorController::setSpeed(double speed){
	setPoint = speed;
}

// update the motor speed with pid
void MotorController::update(){
	if (pid.Compute()){
		input = (this->getSpeed());
		motor->setSpeed(output);
	}
}

// calculate the motor speed
double MotorController::getSpeed(){

	unsigned long currTime = micros();

	// read encoder
	int ticks = encoder->read();
	encoder->write(0);

	// encoder directionally reads encoder
	if (motor->isInvert()){
		ticks = -ticks;
	}

	// add to distance
	tickDistance = tickDistance + ticks;

	// speed calculation
	float secs = (float(currTime-prevTime)/1000000);
	prevTime = currTime;
	return ticks*TICKTOMM/secs;
}

// get distance the motor has travel since initalization in ticks
long MotorController::getTickDistance(){
	return tickDistance;
}

// move until has moved the desired number of ticks
bool MotorController::moveTicks(int ticks, int speed){

	// start the move
	if (!inMove){
		this->setSpeed(speed);
		inMove = true;
		startTick = this->getTickDistance();
	}

	// determine if done with move
	bool isDone = false;
	if (ticks < 0){
		isDone = ((this->getTickDistance() - startTick) <= ticks);
	} else {
		isDone = ((this->getTickDistance() - startTick) >= ticks);
	}

	// stop the move
	if (isDone){
		inMove = false;
		this->setSpeed(0);
		return true;
	}
	return false;
}

MotorController::~MotorController(){}
