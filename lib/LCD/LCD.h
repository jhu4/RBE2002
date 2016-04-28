#ifndef LCD_H
#define LCD_H
#include <LiquidCrystal.h>
#include <Arduino.h>

class LCD{
  private:
    LiquidCrystal lcd;
    unsigned long lastTime;

  public:
    LCD(int p1,int p2, int p3, int p4, int p5, int p6);
    void initialize();
    void display(double x, double y);
    void display(bool x, bool y);
    void display(float x, float y, float z);
    void display(String message);
    void display(float z);
    void display(int z);
    void display(long ticks);
    void display(unsigned long ticks);
    void display(double x);
    bool delayWrite();

};

#endif
