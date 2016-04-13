#ifndef LED_H
#define LED_H

class LED{
  private:
    int _pin;
  public:
    LED(int pin);
    void initialize();
    void on();
    void off();
};

#endif

