#include "Displayer.h"
#include "LCD.h"
#include "LED.h"
#include "Location.h"

Location loca;
LCD lcd(40,41,42,43,44,45);
LED led(23);
LED led2(22);
LED led3(24);
LED led4(25);
LED led5(26);

void setup() {
  Displayer.initialize();

}

void loop() {
  

}
