#include "LED.h"

LED led1(9);
LED led2(8);

void setup() {
  led1.initializing();
  led2.initializing();

}

void loop() {
  led1.on();
  led2.on();
  delay(1000);
  led1.off();
  delay(1000);
  led2.off();

}
