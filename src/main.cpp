#include "Motor.h"
#include "Encoder.h"
#include "MotorController.h"
#include "LCD.h"
#include "DistanceSensor.h"
#include "ZWallFollower.h"
#include "Locator.h"

#include "LightSensor.h"
#include "TurretController.h"

#include <Arduino.h>

#define enablePin 11

Encoder* eLeft = new Encoder(2,3);
Encoder* eRight = new Encoder(18,19);

Motor* leftMotor = new Motor(10, 7, 8, 1);
Motor* rightMotor = new Motor(6, 24, 23, 0);

MotorController* leftControl = new MotorController(leftMotor, eLeft, 0.2, 0.7, 0.0);
MotorController* rightControl = new MotorController(rightMotor, eRight, 0.2, 0.7, 0.0);

LCD* lcd = new LCD(40,41,42,43,44,45);

DistanceSensor* distA = new DistanceSensor(A2);
DistanceSensor* distB = new DistanceSensor(A1);
DistanceSensor* distC = new DistanceSensor(A0);

ZWallFollower* follower = new ZWallFollower(distA, distB, distC, leftControl, rightControl, 150, 100 , 2 , 0, 1);

Locator* locator = new Locator(leftControl, rightControl);


LightSensor lightSensor(3,150);
TurretController* turretController = new TurretController(4,5,lightSensor);


enum State {WALL_FOLLOW_INIT, WALL_FOLLOW, STOP_INIT, STOP, FLAME_INIT, FLAME, EXTINGUISH};
State robotState = WALL_FOLLOW_INIT;

void setup() {

	pinMode(enablePin, OUTPUT);
	digitalWrite(enablePin, HIGH);
}


long lastTime = 0;
long lastTimeA = 0;
long startTicks = 0;
long blowTimer = 0;
long waitTimer = 0;

bool hasCandle = false;
void loop() {

	switch (robotState) {
		case WALL_FOLLOW_INIT:
			follower->enable();
			robotState = WALL_FOLLOW;

			turretController->initialize();

			lastTimeA = millis();
			break;
		case WALL_FOLLOW:
			follower->update();
			locator->update();
			//lcd->display(locator->atOrigin(100.0), ((millis()-lastTimeA) > 10000));
			if ((locator->atOrigin(100.0)) && ((millis()-lastTimeA) > 10000)){
				robotState = STOP_INIT;
				//lcd->display("Stop");
			}

			lightSensor.sense();
			if (turretController->updownScan() && !hasCandle){
				robotState = FLAME_INIT;
			}
			break;
		case STOP_INIT:
			leftControl->setSpeed(0);
			rightControl->setSpeed(0);
			leftControl->update();
			rightControl->update();
			follower->disable();
			lastTime = millis();
			robotState = STOP;
			break;
		case STOP:
		//lcd->display(millis()-lastTime);

			if ((millis()-lastTime) < 10000){
				leftControl->update();
				rightControl->update();
			} else {
				robotState = WALL_FOLLOW_INIT;
			}
			break;
		case FLAME_INIT:
			leftControl->setSpeed(0);
			rightControl->setSpeed(0);
			leftControl->update();
			rightControl->update();
			follower->disable();
			robotState = FLAME;
			break;
		case FLAME:
			if (turretController->findCandleScan()){
				robotState = EXTINGUISH;
				blowTimer = millis();
			}
			leftControl->update();
			rightControl->update();
			break;
		case EXTINGUISH:
			if (millis()-blowTimer > 5000){
				//lcd->display("OFF");
				digitalWrite(22,LOW);
				hasCandle = true;
				robotState = WALL_FOLLOW_INIT;
				// if (millis()-blowTimer > 10000){
				// 	hasCandle = true;
				// 	robotState = WALL_FOLLOW_INIT;
				// }
			} else {
				//lcd->display(millis()-blowTimer);
				digitalWrite(22, HIGH);
			}
			leftControl->update();
			rightControl->update();
			break;
		default:
			//lcd->display("DEFAULT");
			delay(10000);
			break;
	}

}
