#include "LightSensor.h"
#include <TimerOne.h>

LightSensor ls(11, 50);
void setup() {
  ls.initialize();
  Serial.begin(9600);
//  Timer1.initialize(500000);
//  Timer1.attachInterrupt(aaaa);
}

void aaaa(){
  Serial.print("isDetectLight:");
  Serial.println(ls.isDetectLight());
  Serial.print("isGetCloser:");
  Serial.println(ls.isGetCloser());
  Serial.print("watch:");
  Serial.println(ls.sense());
}

void loop() {
  ls.sense();
  Serial.println(ls.getReading());
}
//1000 Normal light
//

