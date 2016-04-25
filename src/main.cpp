#include "Motor.h"
#include "Encoder.h"
#include "MotorController.h"
#include "LCD.h"
#include "DistanceSensor.h"
#include "ZWallFollower.h"

#include <Arduino.h>

#define enablePin 11
#define MMTOIN 0.0393701

Encoder* eLeft = new Encoder(2,3);
Encoder* eRight = new Encoder(18,19);

Motor* leftMotor = new Motor(10, 7, 8, 1);
Motor* rightMotor = new Motor(6, 4, 5, 0);

MotorController* leftControl = new MotorController(leftMotor, eLeft, 0.2, 0.7, 0.0);
MotorController* rightControl = new MotorController(rightMotor, eRight, 0.2, 0.7, 0.0);

LCD* lcd = new LCD(40,41,42,43,44,45);

DistanceSensor* distA = new DistanceSensor(A2);
DistanceSensor* distB = new DistanceSensor(A1);
DistanceSensor* distC = new DistanceSensor(A0);


ZWallFollower* follower = new ZWallFollower(distA, distB, distC, leftControl, rightControl, 150, 100 , 2 , 0, 1);


enum State {WALL_FOLLOW, TURN, STOP, FLAME};
State robot_state = WALL_FOLLOW;

void setup() {

	pinMode(enablePin, OUTPUT);
	digitalWrite(enablePin, HIGH);
	//leftControl->setSpeed(100);
	//rightControl->setSpeed(100);
}

unsigned long lastTime = millis();
bool toggle = 0;

double leftDist = 0;
double rightDist = 0;
double leftDistOld = 0;
double rightDistOld = 0;
double leftDistDiff = 0;
double rightDistDiff = 0;

double wheelSpace = 177;
double theta = 0;
double heading = 0;
double radius = 0;

double x = 0;
double y = 0;


// bool rightDone = false;
// bool leftDone = false;

void loop() {

	switch (robot_state) {
		case WALL_FOLLOW:
			follower->update();


			// if (!rightDone){
			// 	rightDone = rightControl->moveTicks(3200, 100);
			// }
			// if (!leftDone){
			// 	leftDone = leftControl->moveTicks(3200, 100);
			// }
			//
			// leftControl->update();
			// rightControl->update();

///////////////////
			leftDist = leftControl->getTickDistance();
			rightDist = rightControl->getTickDistance();

			leftDistDiff = (leftDist-leftDistOld)*TICKTOMM;
			rightDistDiff = (rightDist-rightDistOld)*TICKTOMM;

			leftDistOld = leftDist;
			rightDistOld = rightDist;

			theta = (-leftDistDiff+rightDistDiff)/(wheelSpace);
			heading = theta + heading;

			if (theta != 0){
				radius = (rightDistDiff/theta)-(wheelSpace/2);
				x = x + (radius*(sin(theta+heading)-sin(heading)));
				y = y + (radius*(cos(heading)-cos(theta+heading)));
			} else {
				x = x + leftDistDiff*cos(heading);
				y = y + leftDistDiff*sin(heading);
			}

			lcd->display(x*MMTOIN,y*MMTOIN);

			break;
		case TURN:
			break;
		case STOP:
			break;
		case FLAME:
			break;
	}

}
