#ifndef LCD_H
#define LCD_H
#include <LiquidCrystal.h>

class LCD{
  private:
    LiquidCrystal lcd;

  public:
    LCD(int p1,int p2, int p3, int p4, int p5, int p6);
    void initialize();
    void display(float x, float y);
    void display(float x, float y, float z);
    void display(String message);
    void display(float z);
          
};

#endif
