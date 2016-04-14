#ifndef DISPLAYER_H
#define DISPLAYER_H
#include "LCD.h"
#include "LED.h"

class Displayer{
  private:
    LCD lcd;
    LED led[5];
  public:
    void updateLocation(Location location);
    
}

#endif
