#include "PID.h"

PID::PID(double* input, double* output, double* setPoint ,double kp, double ki, double kd):
input(input),
output(output),
setPoint(setPoint),
kp(kp),
ki(ki),
kd(kd),
timeIter(100),
lastTime(millis()-timeIter),
iTerm(0),
lastError(0),
maxOut(255),
minOut(0){
}

void PID::setOutputLimits(double min, double max){
  maxOut = max;
  minOut = min;
}

bool PID::compute(){
  if ((millis() - lastTime) > timeIter){
    double error = ((*setPoint) - (*input))*timeIter/1000;

    double out = (kp*error)+(ki*iTerm)+(kd*(error-lastError));

    if (out > maxOut){
      *output = maxOut;
    } else if (out < minOut){
      *output = minOut;
    } else {
      *output = out;
    }

    iTerm = iTerm + error;
    lastError = error;
    return true;
  } else {
    return false;
  }
}
