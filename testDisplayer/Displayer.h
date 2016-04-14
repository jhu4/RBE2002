#ifndef DISPLAYER_H
#define DISPLAYER_H
#include "LCD.h"
#include "LED.h"
#include "Location.h"

class Displayer{
  private:
    LCD lcd;
    LED led[5];
  public:
    Displayer(LCD lcd, LED led, LED led2, LED led3, LED led4, LED led5);
    void initialize();
    void updateLocation(Location location);
    
}

#endif
