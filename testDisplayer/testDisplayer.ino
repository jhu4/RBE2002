#include "Displayer.h"
#include "LCD.h"
#include "LED.h"
#include "Location.h"
#include <LiquidCrystal.h>

Location loca(3.50,12.23);
LCD lcd(40, 41, 42, 43, 44, 45);
LED led(23);


Displayer d(lcd, led);

void setup() {
  d.initialize();

}

void loop() {
  d.updateLocation(loca);

}
