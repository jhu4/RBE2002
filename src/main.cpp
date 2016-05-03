/*
Main program
main.cpp
state machine to run the robot

author: Zachary Armsby
*/

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

///////////////////////// IMU code from Joes Lab 4 code
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

#define enablePin 11

// initialize encoders
Encoder* eLeft = new Encoder(2,3);
Encoder* eRight = new Encoder(18,19);

// initialize motors
Motor* leftMotor = new Motor(10, 7, 8, 1);
Motor* rightMotor = new Motor(6, 24, 23, 0);

// initialize motor controllers
MotorController* leftControl = new MotorController(leftMotor, eLeft, 0.2, 0.7, 0.0);
MotorController* rightControl = new MotorController(rightMotor, eRight, 0.2, 0.7, 0.0);

// initialize LCD
LCD* lcd = new LCD(40,41,42,43,44,45);

// initialize distance sensors
DistanceSensor* distA = new DistanceSensor(A2);
DistanceSensor* distB = new DistanceSensor(A1);
DistanceSensor* distC = new DistanceSensor(A0);

// intialize wall follower
ZWallFollower* follower = new ZWallFollower(distA, distB, distC, leftControl, rightControl, 150, 100 , 2 , 0, 1);

// initialize locator (odometery system)
Locator* locator = new Locator(leftControl, rightControl);

// intialize candle sensor
LightSensor lightSensor(3,120);

// initialize turret controller
TurretController* turretController = new TurretController(4,5,lightSensor);

// state machine states
enum State {WALL_FOLLOW_INIT, WALL_FOLLOW, STOP_INIT, STOP, TURN_90_OFFWALL,
	DRIVE_TO_CANDLE, TURN_90_CANDLE, DRIVE_TO_WALL, TURN_90_WALL, FLAME_INIT,
	FLAME, EXTINGUISH};
// initial robot state
State robotState = WALL_FOLLOW_INIT;

void setup() {

	pinMode(enablePin, OUTPUT);
	digitalWrite(enablePin, HIGH);

///////////////////////// IMU code from Joes Lab 4 code
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

/////////////////////////
}

// timer for stopping period
long lastTime = 0;

// timer for checking if have been running for more than 10 secs
long lastTimeA = 0;

// timer for blowing out the candle
long blowTimer = 0;

// booleans for if encoder motor moves have finished
bool leftDone = false;
bool rightDone = false;

// has the candle been found
bool hasCandle = false;

// candle coordinates
double cx = 0;
double cy = 0;
double cz = 0;


void loop() {

	switch (robotState) {
		// initialize wallfollowing (exicuted once before wallfollowing)
		case WALL_FOLLOW_INIT:
			follower->enable();
			robotState = WALL_FOLLOW;

			turretController->initialize();

			lastTimeA = millis();
			break;

		// wall following active
		case WALL_FOLLOW:
			// updated the wallfollower to controll the robot's motion
			follower->update();

			// update the odometery data from motor controllers
			locator->update();

			// check if at origin after start
			if ((locator->atOrigin(200.0)) && ((millis()-lastTimeA) > 10000)){
				robotState = STOP_INIT;
			}

			// scan with the turret and candel sensor and turn towards it when found
			lightSensor.sense();
			if (turretController->updownScan() && !hasCandle){
				lcd->display("FOUND Candle");
				robotState = TURN_90_OFFWALL;
				hasCandle = true;
				gyro_z = 0;
			}
			break;

		// initialize stoping (exicuted once before stoping)
		case STOP_INIT:
			// set speed to 0
			leftControl->setSpeed(0);
			rightControl->setSpeed(0);

			// update the motors
			leftControl->update();
			rightControl->update();

			// disable the wallfollower
			follower->disable();

			// start time of the stop
			lastTime = millis();
			robotState = STOP;
			break;

		case STOP:
			// remain stoped for 10 sec
			if ((millis()-lastTime) < 10000){
				// update the motor controllers
				leftControl->update();
				rightControl->update();
			} else {
				// resume wallfollowing
				robotState = WALL_FOLLOW_INIT;
			}
			break;

		// turn 90 degrees using the gyro
		case TURN_90_OFFWALL:
			///////////////////////// IMU code from Joes Lab 4 code
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
			 /////////////////////////

			// move motors until turn is complete
			leftControl->setSpeed(-250);
			rightControl->setSpeed(200);
			if (gyro_z > 30){
				leftControl->setSpeed(0);
				rightControl->setSpeed(0);
				robotState = DRIVE_TO_CANDLE;
				gyro_z = 0;
			}
			// update the motors
			leftControl->update();
			rightControl->update();
			//update odomotry data
			locator->update();
			break;

		case DRIVE_TO_CANDLE:
			// drive until detect candle in front of the robot
			distC->getDistance();
			if (distC->getAverage() < 11){
				leftControl->setSpeed(0);
				rightControl->setSpeed(0);
				leftControl->update();
				rightControl->update();

				// get candle x,y
				cx = locator->getCandleX(230);
				cy = locator->getCandleY(230);
				robotState = TURN_90_CANDLE;
			}
			leftControl->setSpeed(100);
			rightControl->setSpeed(100);

			// update the motor controllers
			leftControl->update();
			rightControl->update();
			// update the odometery data
			locator->update();
			break;

		// turn away from the candle to go to the wall
		case TURN_90_CANDLE:
			// move with encoders untill turn is complete
			if(!leftDone){
				leftDone = leftControl->moveTicks(500, 150);
			}
			if(!rightDone){
				rightDone = rightControl->moveTicks(-500, -250);
			}

			// next state if turn is finished
			if(leftDone && rightDone){
				leftDone = false;
				rightDone = false;
				robotState = FLAME_INIT;
			}

			// update the motor controllers
			leftControl->update();
			rightControl->update();

			// update the odometery data
			locator->update();
			break;

		// drive straight until detect a wall
		case DRIVE_TO_WALL:
			// drive until detect a wall
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

			// upadate motro controllers
			leftControl->update();
			rightControl->update();

			// update the odometery data
			locator->update();
			break;

		// turn onto the wall
		case TURN_90_WALL:
			// move with encoders untill turn is complete
			if(!leftDone){
				leftDone = leftControl->moveTicks(-700, -250);
			}
			if(!rightDone){
				rightDone = rightControl->moveTicks(700, 150);
			}

			// exit state when turn is complete
			if(leftDone && rightDone){
				leftDone = false;
				rightDone = false;
				robotState = WALL_FOLLOW_INIT;
			}

			// update motor controllers
			leftControl->update();
			rightControl->update();

			// update odometery data
			locator->update();
			break;

		// initialize the flame detection sequence (only runs once)
		case FLAME_INIT:
			leftControl->setSpeed(0);
			rightControl->setSpeed(0);

			// update the motor controllers
			leftControl->update();
			rightControl->update();

			//disable the wall follower
			follower->disable();
			robotState = FLAME;
			break;

		// detect the flame
		case FLAME:
			// scan for the candle
			if (turretController->findCandleScan()){
				// determine z candle height
				double angle = turretController->getPitchAngle();
				cz = (tan((angle-90)*0.0174533)*9)+7.4;
				robotState = EXTINGUISH;
				blowTimer = millis();
			}
			// update the motor controllers
			leftControl->update();
			rightControl->update();
			break;

		// blow out the candle
		case EXTINGUISH:
			// blow for 10 seconds
			if (millis()-blowTimer > 10000){
				// turn off the fan and display the x,y,z corrdinates
				// and that the candle has been extinguished
				digitalWrite(22,LOW);
				lcd->display(cx,cy,cz);
				robotState = DRIVE_TO_WALL;
			} else {
				// turn the fan on
				digitalWrite(22, HIGH);
			}
			// update the motor controllers
			leftControl->update();
			rightControl->update();
			break;

		// catch the defualt case (should not happen but, useful for debuging)
		default:
			delay(10000);
			break;
	}

}
