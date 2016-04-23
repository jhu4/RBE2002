#include <Arduino.h>
#include "FanController.h"
#include "LightSensor.h"
#include <Servo.h>


LightSensor ls(5,6,150);
FanController fc(9,8,7,ls);

void setup(){

}

void loop(){
  
}
