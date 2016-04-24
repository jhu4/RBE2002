#ifndef DISPLAYER_H
#define DISPLAYER_H
#include "LCD.h"
#include "LED.h"
#include "Location.h"
#include <Arduino.h>

#define LEDNUM 5
class Displayer{
  private:
    LCD &lcd;
    LED** led;
    int index;
  public:
    Displayer(LCD& lcd, LED* led[LEDNUM]);
    void initialize();
    void updateLocation(Location& location);
    void LEDon();

};

#endif
