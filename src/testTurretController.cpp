#include <Arduino.h>
#include "TurretController.h"
#include "LightSensor.h"
#include "Fan.h"
#include <Servo.h>
#include "TimerOne.h"

LightSensor ls(3,150);
TurretController tc(4,5,ls);

void testls(){
  ls.sense();
  Serial.print("average:");
  Serial.print(ls.getAverageReading());
  Serial.print("\t");
  Serial.print("current:");
  Serial.print(ls.getReading());
  Serial.print("\t");
  Serial.print("isDetectLight:");
  Serial.println(ls.isDetectLight());
}


void setup(){
  Serial.begin(9600);
  pinMode(9,OUTPUT);
  tc.initialize();
  delay(2000);
  //Timer1.initialize(1000000);
  //Timer1.attachInterrupt(testls);
}

void loop(){

  if(ls.isDetectLight()){
    tc.findCandleScan();
  }
  else{
    if(tc.updownScan()){

    }
  }


  // testls();
  // delay(1000);

}
