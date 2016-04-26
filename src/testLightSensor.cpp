#include <Arduino.h>
#include "LightSensor.h"

LightSensor ls(3,150);
void setup(){
  Serial.begin(9600);
  ls.initialize();
}

void loop(){
  ls.sense();
  Serial.println(ls.getAverageReading());
}
