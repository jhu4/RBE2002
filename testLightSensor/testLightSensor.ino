#include "LightSensor.h"
#include <TimerOne.h>


LightSensor ls(7, 150);

void setup() {
  ls.initializing();
  Serial.begin(9600);
  Timer1.initialize(500000);
  Timer1.attachInterrupt(aaaa);
}

void aaaa(){
  Serial.println(ls.watch());
}
void loop() {

}



