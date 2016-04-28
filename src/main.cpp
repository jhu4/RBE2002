#include "Motor.h"
#include "Encoder.h"
#include "MotorController.h"
#include "LCD.h"
#include "DistanceSensor.h"
#include "ZWallFollower.h"
#include "Locator.h"

#include "LightSensor.h"
#include "TurretController.h"

//#include "IMU.h"

#include <Arduino.h>

#define enablePin 11

/////////////////////////IMU

#include <Wire.h>
#include <L3G.h>

L3G gyro;


float G_Dt=0.005;    // Integration time (DCM algorithm)  We will run the integration loop at 50Hz if possible

long timer=0;   //general purpose timer
long timer1=0;

float G_gain=.00875; // gyros gain factor for 250deg/sec
float gyro_x; //gyro x val
float gyro_y; //gyro x val
float gyro_z; //gyro x val
float gyro_xold; //gyro cummulative x value
float gyro_yold; //gyro cummulative y value
float gyro_zold; //gyro cummulative z value
float gerrx; // Gyro x error
float gerry; // Gyro y error
float gerrz; // Gyro 7 error


/////////////////////////







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

// changed 150, 100
LightSensor lightSensor(3,120);
TurretController* turretController = new TurretController(4,5,lightSensor);


//enum State {WALL_FOLLOW_INIT, WALL_FOLLOW, STOP_INIT, STOP, FLAME_INIT, FLAME, EXTINGUISH, DRIVE_STRAIGHT, FLAME_INIT_2, FLAME_2};
enum State {WALL_FOLLOW_INIT, WALL_FOLLOW, STOP_INIT, STOP, TURN_90_OFFWALL, DRIVE_TO_CANDLE, TURN_90_CANDLE, DRIVE_TO_WALL, TURN_90_WALL, FLAME_INIT, FLAME, EXTINGUISH};
State robotState = WALL_FOLLOW_INIT;

//IMU* imu = new IMU();

void setup() {

	pinMode(enablePin, OUTPUT);
	digitalWrite(enablePin, HIGH);



/////////////////////////////////////IMU
	Wire.begin(); // i2c begin

  if (!gyro.init()) // gyro init
  {
    Serial.println("Failed to autodetect gyro type!");
    while (1);
  }
  timer=millis(); // init timer for first reading
  gyro.enableDefault(); // gyro init. default 250/deg/s
  delay(1000);// allow time for gyro to settle
  for(int i =0;i<100;i++){  // takes 100 samples of the gyro
  gyro.read();
  gerrx+=gyro.g.x;
  gerry+=gyro.g.y;
  gerrz+=gyro.g.z;
   delay(25);
  }

  gerrx = gerrx/100; // average reading to obtain an error/offset
  gerry = gerry/100;
  gerrz = gerrz/100;
	//while (!(imu->isInitialized())){
	//	imu->initialize();
//	}
////////////////////////////////////IMU



}


long lastTime = 0;
long lastTimeA = 0;
long startTicks = 0;
long blowTimer = 0;
long waitTimer = 0;
float candleDistance = 0;

bool leftDone = false;
bool rightDone = false;

bool hasCandle = false;

double angleA = 0;
double angleB = 0;

double cx = 0;
double cy = 0;

double cz = 0;


void loop() {

	switch (robotState) {
		case WALL_FOLLOW_INIT:
			follower->enable();
			robotState = WALL_FOLLOW;

			turretController->initialize();

			lastTimeA = millis();
			break;
		case WALL_FOLLOW:
			//lcd->display("WALLFOLLOW");
			follower->update();
			locator->update();
			if ((locator->atOrigin(200.0)) && ((millis()-lastTimeA) > 10000)){
				robotState = STOP_INIT;
			}

			lightSensor.sense();
			if (turretController->updownScan() && !hasCandle){
				lcd->display("FOUND Candle");
				robotState = TURN_90_OFFWALL;
				hasCandle = true;
				gyro_z = 0;
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
			if ((millis()-lastTime) < 10000){
				leftControl->update();
				rightControl->update();
			} else {
				robotState = WALL_FOLLOW_INIT;
			}
			break;
		// case FLAME_INIT:
		// 	leftControl->setSpeed(0);
		// 	rightControl->setSpeed(0);
		// 	leftControl->update();
		// 	rightControl->update();
		// 	follower->disable();
		// 	robotState = FLAME;
		// 	break;
		// case FLAME:
		// 	if (turretController->findCandleScan()){
		// 		angleA = turretController->getYawAngle();
		// 		robotState = DRIVE_STRAIGHT;
		// 		//robotState = EXTINGUISH;
		// 		//blowTimer = millis();
		// 	}
		// 	leftControl->update();
		// 	rightControl->update();
		// 	break;
		// case DRIVE_STRAIGHT:
		// 	if(!leftDone){
		// 		leftDone = leftControl->moveTicks(3200, 100);
		// 	}
		//
		// 	if(!rightDone){
		// 		rightDone = rightControl->moveTicks(3200, 100);
		// 	}
		//
		// 	if(leftDone && rightDone){
		// 		leftDone = false;
		// 		rightDone = false;
		// 		robotState = FLAME_INIT_2;
		// 	}
		// 	leftControl->update();
		// 	rightControl->update();
		// 	break;


		case TURN_90_OFFWALL:



			if((millis()-timer)>=5){

		   gyro.read(); // read gyro
		   timer=millis(); //reset timer
		   gyro_x=(float)(gyro.g.x-gerrx)*G_gain; // offset by error then multiply by gyro gain factor
		   gyro_y=(float)(gyro.g.y-gerry)*G_gain;
		   gyro_z=(float)(gyro.g.z-gerrz)*G_gain;

		   gyro_x = gyro_x*G_Dt; // Multiply the angular rate by the time interval
		     gyro_y = gyro_y*G_Dt;
		       gyro_z = gyro_z*G_Dt;

		    gyro_x +=gyro_xold; // add the displacment(rotation) to the cumulative displacment
		     gyro_y += gyro_yold;
		       gyro_z += gyro_zold;

		     gyro_xold=gyro_x ; // Set the old gyro angle to the current gyro angle
		      gyro_yold=gyro_y ;
		      gyro_zold=gyro_z ;
		   }


		 //lcd->display(gyro_z);

			//imu->setEndAngle(90);
			leftControl->setSpeed(-250);
			rightControl->setSpeed(200);
			if (gyro_z < 30){

			} else {
				leftControl->setSpeed(0);
				rightControl->setSpeed(0);
				robotState = DRIVE_TO_CANDLE;
				gyro_z = 0;
			}
			leftControl->update();
			rightControl->update();
			locator->update();
			break;


		// case TURN_90_OFFWALL:
		// 	//lcd->display("OFFWALL    ");
		// 	if(!leftDone){
		// 		leftDone = leftControl->moveTicks(-700, -150);
		// 	}
		//
		// 	if(!rightDone){
		// 		rightDone = rightControl->moveTicks(700, 120);
		// 	}
		//
		// 	if(leftDone && rightDone){
		// 		leftDone = false;
		// 		rightDone = false;
		// 		robotState = DRIVE_TO_CANDLE;
		// 	}
		// 	leftControl->update();
		// 	rightControl->update();
		// 	locator->update();
		// 	break;

		case DRIVE_TO_CANDLE:
		//lcd->display("DRIVETOCANDLE    ");
			distC->getDistance();
			if (distC->getAverage() < 11){
				leftControl->setSpeed(0);
				rightControl->setSpeed(0);
				leftControl->update();
				rightControl->update();
				cx = locator->getCandleX(230);
				cy = locator->getCandleY(230);
				robotState = TURN_90_CANDLE;
			}
			leftControl->setSpeed(100);
			rightControl->setSpeed(100);
			leftControl->update();
			rightControl->update();
			locator->update();
			break;

		case TURN_90_CANDLE:
		//lcd->display("TURN90CANDLE");
			if(!leftDone){
				leftDone = leftControl->moveTicks(500, 150);
			}

			if(!rightDone){
				rightDone = rightControl->moveTicks(-500, -250);
			}

			if(leftDone && rightDone){
				leftDone = false;
				rightDone = false;
				robotState = FLAME_INIT;
			}
			leftControl->update();
			rightControl->update();
			locator->update();
			break;


		case DRIVE_TO_WALL:
			//lcd->display("DRIVETOWALL");
			distC->getDistance();
			if (distC->getAverage() < 11){
				leftControl->setSpeed(0);
				rightControl->setSpeed(0);
				leftControl->update();
				rightControl->update();
				robotState = TURN_90_WALL;
			}
			leftControl->setSpeed(100);
			rightControl->setSpeed(105);
			leftControl->update();
			rightControl->update();
			locator->update();
			break;

		case TURN_90_WALL:
			//lcd->display("TURN_90_WALL    ");
			if(!leftDone){
				leftDone = leftControl->moveTicks(-700, -250);
			}

			if(!rightDone){
				rightDone = rightControl->moveTicks(700, 150);
			}

			if(leftDone && rightDone){
				leftDone = false;
				rightDone = false;
				robotState = WALL_FOLLOW_INIT;
			}
			leftControl->update();
			rightControl->update();
			locator->update();
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
				double angle = turretController->getPitchAngle();
				cz = (tan((angle-90)*0.0174533)*9)+7.4;
				robotState = EXTINGUISH;
				blowTimer = millis();
			}
			leftControl->update();
			rightControl->update();
			break;

		case EXTINGUISH:
			if (millis()-blowTimer > 10000){
				digitalWrite(22,LOW);
				lcd->display(cx,cy,cz);
				robotState = DRIVE_TO_WALL;
			} else {
				digitalWrite(22, HIGH);
			}
			leftControl->update();
			rightControl->update();
			break;
		default:
			delay(10000);
			break;
	}

}
