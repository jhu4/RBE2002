#include <Arduino.h>
#include "Displayer.h"


Displayer::Displayer(LCD& lcd_in, LED& led_in):
  lcd(lcd_in),
  led(led_in),
  index(0){
}

void Displayer::initialize() {
  lcd.initialize();
  led.initialize();

}

void Displayer::updateLocation(Location loca){
  lcd.display(loca.getX(),loca.getY());
  
}
