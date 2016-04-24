#include "Displayer.h"


Displayer::Displayer(LCD& lcd_in,LED* led_in[LEDNUM]):
  lcd(lcd_in),
  led(led_in),
  index(0){
}

void Displayer::initialize() {
  lcd.initialize();
  for(int i=0;i<LEDNUM;i++){
    led[i]->initialize();
  }
}

void Displayer::updateLocation(Location& loca){
  lcd.display(loca.getX(),loca.getY());
}

void Displayer::LEDon(){
  for(int i=0;i<LEDNUM;i++){
    led[i]->on();
  }
}
