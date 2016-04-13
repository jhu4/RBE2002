#ifndef LED_H
#define LED_H

class LED{
  private:
    int _pin;
  public:
    LED(int pin);
    void initializing();
    void on();
    void off();
};

#endif

