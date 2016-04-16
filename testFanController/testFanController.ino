#include "FanController.h"
#include <Servo.h>
FanController fanC(5, 3);
bool is0 = true;
bool is180 = true;
void setup() {
  Serial.begin(9600);
  fanC.initialize();
  delay(1000);

}

void loop() {

}
