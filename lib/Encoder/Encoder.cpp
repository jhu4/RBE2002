#include "Encoder.h"
int Encoder::count = 0;

EncoderInterrupt::EncoderInterrupt(Encoder* encoderA){
  encoder = encoderA;
  Interrupt::Register(encoder->id, this);
}

void EncoderInterrupt::isr(){
  (encoder->tick)++;
}


Encoder::Encoder(int pinA, int pinB):
pinA(pinA),
pinB(pinB),
tick(0),
interrupt(new EncoderInterrupt(this)){
	id = count;
	count++;

	pinMode(pinA, INPUT);
	pinMode(pinB, INPUT);
	attachInterrupt(digitalPinToInterrupt(pinA), Interrupt::getInterrupt(id), CHANGE);
	attachInterrupt(digitalPinToInterrupt(pinB), Interrupt::getInterrupt(id), CHANGE);

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
