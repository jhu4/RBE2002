#include "Motor.h"
#include "Encoder.h"
#include "MotorController.h"
#include "LCD.h"
#include "DistanceSensor.h"
#include "ZWallFollower.h"
#include "Locator.h"

#include <Arduino.h>

#define enablePin 11

Encoder* eLeft = new Encoder(2,3);
Encoder* eRight = new Encoder(18,19);

Motor* leftMotor = new Motor(10, 7, 8, 1);
Motor* rightMotor = new Motor(6, 4, 5, 0);

MotorController* leftControl = new MotorController(leftMotor, eLeft, 0.2, 0.7, 0.0);
MotorController* rightControl = new MotorController(rightMotor, eRight, 0.2, 0.7, 0.0);

//LCD* lcd = new LCD(40,41,42,43,44,45);

DistanceSensor* distA = new DistanceSensor(A2);
DistanceSensor* distB = new DistanceSensor(A1);
DistanceSensor* distC = new DistanceSensor(A0);

ZWallFollower* follower = new ZWallFollower(distA, distB, distC, leftControl, rightControl, 150, 100 , 2 , 0, 1);

Locator* locator = new Locator(leftControl, rightControl);

enum State {WALL_FOLLOW, STOP, FLAME};
State robot_state = WALL_FOLLOW;

void setup() {

	pinMode(enablePin, OUTPUT);
	digitalWrite(enablePin, HIGH);
}

void loop() {

	switch (robot_state) {
		case WALL_FOLLOW:
			follower->update();
			locator->update();
			break;
		case STOP:
			break;
		case FLAME:
			break;
	}

}
