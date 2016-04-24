#include <Arduino.h>
#include "TurretController.h"
#include "LightSensor.h"
#include "Fan.h"
#include <Servo.h>

LightSensor ls(12,11,150);
Fan fan(25);
TurretController tc(9,24,fan,ls);
// Servo hi;
void setup(){
  pinMode(5,OUTPUT);
  digitalWrite(5,HIGH);
  Serial.begin(9600);
  tc.initialize();
  delay(1000);
  pinMode(10,INPUT);
  digitalWrite(10,HIGH);
  pinMode(11,INPUT);
  digitalWrite(11,LOW);
}

void loop(){
  if(tc.scan()){
    delay(5000);
  }
}
