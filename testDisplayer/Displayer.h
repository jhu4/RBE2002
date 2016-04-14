#ifndef DISPLAYER_H
#define DISPLAYER_H
#include "LCD.h"
#include "LED.h"
#include "Location.h"


class Displayer{
  private:
    LCD lcd;
    LED led;
    int index;
  public:
    Displayer(LCD lcd, LED led);
    void initialize();
    void updateLocation(Location location);
    
};

#endif
