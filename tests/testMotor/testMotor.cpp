//testMotor.ino

#include "Motor.h"
#include <Arduino.h>

int led = 13;

void setup() {
	Motor leftMotor = new Motor(10, 8, 7);
	Motor rightMotor = new Motor(6, 5, 4);
}

void loop() {
}
