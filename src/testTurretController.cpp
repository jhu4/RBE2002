#include <Arduino.h>
#include "TurretController.h"
#include "LightSensor.h"
#include "Fan.h"
#include <Servo.h>

LightSensor ls(3,11,100);
Fan fan(25);
TurretController tc(24,9,fan,ls);
Servo hi;
void setup(){
  Serial.begin(9600);
  Serial.println("Setup");
  pinMode(5,OUTPUT);
  digitalWrite(5,HIGH);

  tc.initialize();
  delay(1000);
  pinMode(10,INPUT);
  digitalWrite(10,HIGH);
  pinMode(11,INPUT);
  digitalWrite(11,LOW);
}

void loop(){
  if(tc.getPitchAngle()>=120&& tc.getPitchAngle()<160){
    if(tc.updownScan()){
      delay(2000);
    }
    // Serial.println("I am here");
  }
  // Serial.println(tc.getYawAngle());
  // ls.sense();
  // Serial.println(ls.getDistance());
}
