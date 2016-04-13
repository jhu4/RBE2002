#ifndef LCD_H
#define LCD_H

class LED{
  private:
    int _pin;
    bool _status;
  public:
    LED(int pin);
    void initializing();
    void on();
    void off();
};

#endif

