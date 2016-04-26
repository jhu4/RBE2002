#include <Arduino.h>
#include "IMU.h"

unsigned long time=0;
bool hi=true;
void setup(){
  Serial.begin(9600);
}

IMU imu;
void loop(){
  if(!imu.isInitialized()){
    imu.initialize();
  }
  if(imu.update()){
    Serial.println("Hey,I worked");
  }
  Serial.print(imu.getgyroZ());
  Serial.print("\t");
  Serial.println(imu.getEndAngle());
  if(millis()>5000 && hi){
    imu.setEndAngle(190);
    hi=false;
  }
}
