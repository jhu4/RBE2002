#include <LiquidCrystal.h>

#include <TimerOne.h>
#include "WallSensorManager.h"
#include <Arduino.h>
#include "LCD.h"

volatile int meow;

LCD lcd(40,41,42,43,44,45);
WallSensorManager ws(0,1,2,lcd);

void setup() {
  Serial.begin(9600);
  ws.initialize();  
  Timer1.initialize(50000);
  Timer1.attachInterrupt(testMapDistanceFunction);
  lcd.initialize();

}

void loop() {
  
}

void testMapDistanceFunction(){
  ws.checkState();
  ws.mapDistance();
  Serial.print(ws.getDistance1());
  Serial.print("\t");
  Serial.println(ws.getDistance2());
}

void testCheckState(){
  bool hello = ws.checkState();
  enum MotionState status = ws.reportCurrent();
  if(hello){
    switch(status){
      case TURN_RIGHT:
        lcd.display("Right          ");        
        break;
      case SECOND_RIGHT_TURN:
        lcd.display("Second right      ");
        break;
      case TURN_LEFT:
        lcd.display("Left          ");
        break;
      case GO_STRAIGHT:
        lcd.display("GO_STRAIGHT        ");
        break;
      case TRANSITION:
        lcd.display("TRANSITION         ");
        break;
      default:
        lcd.display("You suck        ");
    }
  }
}

