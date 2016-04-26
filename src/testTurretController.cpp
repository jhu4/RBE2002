#include <Arduino.h>
#include "TurretController.h"
#include "LightSensor.h"
#include "Fan.h"
#include <Servo.h>

LightSensor ls(3,12,100);
Fan fan(25);
TurretController tc(4,5,fan,ls);
Servo hi;
void setup(){
  Serial.begin(9600);
  pinMode(9,OUTPUT);
  tc.initialize();
  delay(2000);
}

void loop(){

  if(tc.findCandleScan()){
  }

}
