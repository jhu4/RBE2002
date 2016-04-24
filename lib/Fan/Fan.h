#ifndef FAN_H
#define FAN_H
#include <Arduino.h>

class Fan{
  private:
    int pin;
  public:
    Fan(int pin);
    void initialize();
    void on();
    void off();
};

#endif
