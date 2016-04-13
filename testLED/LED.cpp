#include "Arduino.h"
#include "LED.h"

LED::LED(int pin){
  _pin = pin;
}

void LED::initializing(){
  pinMode(_pin, OUTPUT);
}

void LED::on(){
  digitalWrite(_pin, HIGH);
}

void LED::off(){
  digitalWrite(_pin, LOW);
}


