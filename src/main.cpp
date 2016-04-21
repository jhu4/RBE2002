// #include "Motor.h"
// #include "Encoder.h"
// #include "MotorController.h"
//
//
//
// #include <Arduino.h>
//
// #define enablePin 11
//
// Encoder* eLeft = new Encoder(2,3);
// Encoder* eRight = new Encoder(18,19);
//
// Motor* leftMotor = new Motor(10, 7, 8, 1);
// Motor* rightMotor = new Motor(6, 4, 5, 0);
//
// MotorController* leftControl = new MotorController(leftMotor, eLeft, 0.2, 0.6, 0.0);
// MotorController* rightControl = new MotorController(rightMotor, eRight, 0.2, 0.7, 0.0);
//
// void setup() {
// 	pinMode(enablePin, OUTPUT);
// 	digitalWrite(enablePin, HIGH);
//
// 	leftControl->setSpeed(50);
// 	rightControl->setSpeed(50);
// }
//
// int x = -220;
// void loop() {
// 	leftControl->update();
// 	rightControl->update();
// }
//
// #include "LCD.h"
// #include "WallSensor.h"
// #include "WallSensorManager.h"
// #include <Arduino.h>
// WallSensor sws(0,160);
// WallSensor w1(1,90);
// WallSensor w2(2,120);
// LCD lcd(40,41,42,43,44,45);
// WallSensorManager wm(sws,w1,w2,lcd,3500);
// void setup(){
//   sws.initialize();
//   w1.initialize();
//   w2.initialize();
//   lcd.initialize();
//   // sws.initialize();
// }
// void loop(){
//   wm.checkState();
//   lcd.display((float)wm.getDistance1(),(float)wm.getDistance2());
//   // lcd.display((float)w2.isWall(),(float)w1.isWall());
//   lcd.display((float)sws.getReading());
// }
