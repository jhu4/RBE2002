#include <Arduino.h>
#include "TurretController.h"
#include "LightSensor.h"
#include "Fan.h"
#include <Servo.h>

LightSensor ls(3,12,100);
Fan fan(25);
TurretController tc(9,24,fan,ls);
Servo hi;
void setup(){
  Serial.begin(9600);
  pinMode(9,OUTPUT);
  tc.initialize();
  delay(2000);
  pinMode(3,INPUT);
  digitalWrite(3,LOW);
  pinMode(12,INPUT);
  digitalWrite(12,LOW);
}

void loop(){

  if(tc.findCandleScan()){
  }

}
