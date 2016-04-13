#include <TimerOne.h>
#include "WallSensorManager.h"
#include <Arduino.h>
#include "LCD.h"

LCD lcd(40,41,42,43,44,45);
WallSensorManager ws(0,1,2);

void setup() {
  Serial.begin(9600);
  ws.initialize();  
  Timer1.initialize(50000);
  Timer1.attachInterrupt(timerISR);
}

void loop() {
  
}

void timerISR(){
  enum MotionStatus status = ws.reportNextState();
  switch(status){
    case TURN_RIGHT:
      lcd.display("Right");
      break;
    case TURN_LEFT:
      lcd.display("Left");
      break;
    case GO_STRAIGHT:
      lcd.display("GO_STRAIGHT");
      break;
    default:
      lcd.display("You really suck");
  }
}

