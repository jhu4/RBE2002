#include <Arduino.h>
#include "TurretController.h"
#include "LightSensor.h"
#include "Fan.h"
#include <Servo.h>

LightSensor ls(3,100);
TurretController tc(4,5,ls);
void setup(){
  Serial.begin(9600);
  pinMode(9,OUTPUT);
  tc.initialize();
  delay(2000);
}

void loop(){

  if(ls.isDetectLight()){
    tc.findCandleScan();
  }
  else{
    tc.updownScan();
  }

}
