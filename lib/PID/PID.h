#ifndef PID_H
#define PID_H

#include <Arduino.h>

class PID{
private:

  double* input;
  double* output;
  double* setPoint;
  double kp;
  double ki;
  double kd;
  unsigned int timeIter;
  unsigned int lastTime;
  double iTerm;
  double lastError;
  double maxOut;
  double minOut;


public:
  PID(double*, double*, double*,double, double, double);
  bool compute();
  void setOutputLimits(double min, double max);

};

#endif
