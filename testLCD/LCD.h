#ifndef LCD_H
#define LCD_H
#include <LiquidCrystal.h>


class LCD{
  private:
          

  public:
         void displayRobotLocation(float x, float y);
         void displayFireLocation(float x, float y, float z);
          
};

#endif
