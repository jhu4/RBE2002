#include <WallSensors.h>

WallSensors::WallSensors(int pin1, int pin2):
headpin(pin1),tailpin(pin2){

}

void WallSensors::initializing(){
	pinMode(headpin, INPUT);
	pinMode(tailpin, OUTPUT);
}

bool WallSensors::isTurningRight(){

}

bool WallSensors::isTurningLeft(){

}

float getDistanceNaunce(){
	
}