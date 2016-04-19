#include "Encoder.h"

Encoder::Encoder(int pinA, int pinB):
pinA(pinA),
pinB(pinB),
tick(0){
}

void Encoder::tickISR(){
	tick++;
}

void Encoder::resetTicks(){
	tick = 0;
}

int Encoder::getTicks(){
	int tickHold = tick;
	tick = 0;
	return tickHold;
}

Encoder::~Encoder(){

}
