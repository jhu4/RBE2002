#include <Arduino.h>

#include <TimerOne.h>
#include "WallSensor.h"

void setup() {
  Serial.begin(9600);
  Timer1.initialize(500000);
  Timer1.attachInterrupt(Timer1ISR);
}

WallSensor ws(0);

void loop() {
  
}

void Timer1ISR(){
  Serial.println(ws.sense());
//  Serial.print("isFindGap: ");
//  Serial.println(ws.isFindGap());
  Serial.print("isWall:  ");
  Serial.println(ws.isWall());
}

