#ifndef FANCONTROLLER_H
#define FANCONTROLLER_H
#include <Servo.h>
#include "LightSensor.h"
#include <Arduino.h>

#define HALFANGLE 6
#define INDEX (180/HALFANGLE)
class Fan{
  private:
    int pin;
  public:
    Fan(int pin);
    void initialize();
    void on();
    void off();
};

class FanController {
  private:
    int _yaw,_pitch;
    int yawAngle,pitchAngle;
    int posPitch,posYaw;
    Fan fan;
    LightSensor& ls;
    Servo yawServo;
    Servo pitchServo;

  public:

    FanController(int _yaw, int _pitch, int fan, LightSensor& ls);
    void initialize();
    bool up();
    bool down();
    bool left();
    bool right();
    int getPitchAngle();
    int getYawAngle();
    float getCandleDistance();
    void findCandle();
};

#endif
