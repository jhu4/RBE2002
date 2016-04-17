#include "LightSensor.h"
#include <TimerOne.h>

LightSensor ls(0, 50);
void setup() {
  ls.initialize();
  Serial.begin(9600);
  Timer1.initialize(50000);
  Timer1.attachInterrupt(testDetectLight);
}

void testDetectLight(){
  Serial.print("isDetectLight:");
  Serial.print(ls.isDetectLight());
  Serial.print("\t \t");
  Serial.print("isGetCloser:");
  Serial.print(ls.isGetCloser());
  Serial.print("\t");
  Serial.print("sense:");
  Serial.println(ls.sense());
}

void getDataExperiment(){
  Serial.println(ls.getReading());
}

void loop() {
  ls.sense();
//  Serial.println(ls.getReading());
}
//1000 Normal light
//

