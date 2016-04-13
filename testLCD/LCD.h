#ifndef LCD_H
#define LCD_H
#include <LiquidCrystal.h>


class LCD{
  private:
    LiquidCrystal lcd;

  public:
    LCD(int p1,int p2, int p3, int p4, int p5, int p6);
    void initializing();
    void displayRobotLocation(float x, float y);
    void displayRobotLocation(float x, float y, float z);
          
};

#endif
