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
// #include "SpecialWallSensor.h"
// #include "WallSensor.h"
// #include <Arduino.h>
// SpecialWallSensor sws(0);
// WallSensor w1(1);
// WallSensor w2(2);
// LCD lcd(40,41,42,43,44,45);
// void setup(){
//   w1.initialize();
//   w2.initialize();
//   lcd.initialize();
//   // sws.initialize();
// }
// void loop(){
//   w1.sense();
//   w2.sense();
//   lcd.display((float)w1.getReading(),(float)w2.getReading());
// }
