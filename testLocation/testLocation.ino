#include <Location.h>
Location loca;

void setup() {
  Serial.begin(9600);
  Serial.println(loca.getX());
  Serial.println(loca.getY());
  loca.update(10,-5.3);
  Serial.println(loca.getX());
  Serial.println(loca.getY());
}


void loop() {

}

