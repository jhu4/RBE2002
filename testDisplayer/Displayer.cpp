#include "Arduino.h"
#include "Displayer.h"
#include "LCD.h"
#include "LED.h"

Displayer::Displayer(LCD lcd, LED led, LED led2, LED led3, LED led4, LED led5):
  Displayer(lcd, led, led2, led3, led4, led5) {

}

void Displayer::initialize() {
  lcd.initialize();
  led.initialize();
  led2.initialize();
  led3.initialize();
  led4.initialize();
  led5.initialize();
}

void Displayer::updateLocation(Location location){
  location.update(x, y);
  
}

