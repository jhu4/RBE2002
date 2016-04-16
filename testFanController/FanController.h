#ifndef FANCONTROLLER_H
#define FANCONTROLLER_H
#include <Servo.h>
#include "LightSensor.h"

class FanController {
  private:
    int _yaw;
    int _pitch;
    int reportPitchAngle();
    int reportYawAngle();
    float getCandleDistance();
    bool findCandle();

  public:

    FanController(int _yaw, int _pitch);
    Servo yawServo;
    Servo pitchServo;
    int posPitch; 
    int posYaw; 
    void initialize();
    bool up();
    bool down();
    bool left();
    bool right();
};

#endif
