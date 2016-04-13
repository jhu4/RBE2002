#include "LED.h"

LED led1(23);
LED led2(22);

void setup() {
  led1.initialize();
  led2.initialize();

}

void loop() {
  led1.on();
  led2.on();
  delay(1000);
  led1.off();
  delay(1000);
  led2.off();
  delay(1000);

}
