#ifndef FANCONTROLLER_H
#define FANCONTROLLER_H
#include <Servo.h>
#include "LightSensor.h"

class FanController{
  private:
    Servo yaw;
    Servo pitch;
    LightSensor lightsensor;
    int reportPitchAngle();
    int reportYawAngle();
    float getCandleDistance();
    boolean findCandle();
    
  public:
    FanController(Servo yaw, Servo pitch);
    
    void initialize();
    void up();
    void down();
    void left();
    void right();
};

#endif
