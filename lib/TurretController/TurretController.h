#ifndef TurretController_H
#define TurretController_H
#include <Arduino.h>
#include <Servo.h>
#include "LightSensor.h"
#include "Fan.h"


#define HALFANGLE 1
#define INDEX (180/HALFANGLE)
#define TICKTIME 50

enum turretDirection{
  UP,
  DOWN,
  LEFT,
  RIGHT
};


class TurretController {
  private:
    bool isYawScanFinished,isPitchScanFinished;
    int index;
    int _yaw,_pitch;
    int yawMinReading, pitchMinReading;
    int yawAngle,pitchAngle;
    int posPitch,posYaw;
    unsigned long time ;
    enum turretDirection yawDirection;
    enum turretDirection pitchDirection;
    LightSensor& ls;
    Servo yawServo;
    Servo pitchServo;
    void reset();

  public:

    TurretController(int _yaw, int _pitch, LightSensor& ls);
    void initialize();
    bool up();
    bool down();
    bool left();
    bool right();
    int getPitchAngle();
    int getYawAngle();
    float getCandleDistance();
    bool findCandleScan();
    int getYawPos();
    bool scan();
    bool updownScan();
};

#endif
