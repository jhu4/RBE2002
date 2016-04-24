#include <Arduino.h>
#include "TurretController.h"
#include "LightSensor.h"
#include "Fan.h"
#include <Servo.h>

LightSensor ls(22,23,150);
Fan fan(25);
TurretController tc(9,24,fan,ls);
// Servo hi;
void setup(){
  Serial.begin(9600);
  tc.initialize();
  delay(1000);
  pinMode(10,OUTPUT);
  digitalWrite(10,HIGH);
  pinMode(11,OUTPUT);
  digitalWrite(11,LOW);
}

void loop(){
  tc.scan();
}
