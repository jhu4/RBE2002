#include "Encoder.h"
int Encoder::count = 0;

EncoderInterruptA::EncoderInterruptA(Encoder* encoderA){
  encoder = encoderA;
  Interrupt::Register(encoder->id, this);
}

void EncoderInterruptA::isr(){
  encoder->pstateA = encoder->stateA;
  encoder->stateA = !(encoder->stateA);

  if (!(encoder->stateA) && !(encoder->stateB)){
    if (!(encoder->pstateA) && (encoder->pstateB) ){
      (encoder->tick)++;
    } else {
      (encoder->tick)--;
    }
  } else if (!(encoder->stateA) && (encoder->stateB)){
    if ((encoder->pstateA) && (encoder->pstateB) ){
      (encoder->tick)++;
    } else {
      (encoder->tick)--;
    }
  } else if ((encoder->stateA) && !(encoder->stateB)){
    if ((encoder->pstateA) && (encoder->pstateB) ){
      (encoder->tick)--;
    } else {
      (encoder->tick)++;
    }
  } else {
    if (!(encoder->pstateA) && (encoder->pstateB) ){
      (encoder->tick)--;
    } else {
      (encoder->tick)++;
    }
  }

}



EncoderInterruptB::EncoderInterruptB(Encoder* encoderA){
  encoder = encoderA;
  Interrupt::Register(encoder->id+1, this);
}

void EncoderInterruptB::isr(){
  encoder->pstateB = encoder->stateB;
  encoder->stateB = !(encoder->stateB);

  if (!(encoder->stateA) && !(encoder->stateB)){
    if (!(encoder->pstateA) && (encoder->pstateB) ){
      (encoder->tick)++;
    } else {
      (encoder->tick)--;
    }
  } else if (!(encoder->stateA) && (encoder->stateB)){
    if ((encoder->pstateA) && (encoder->pstateB) ){
      (encoder->tick)++;
    } else {
      (encoder->tick)--;
    }
  } else if ((encoder->stateA) && !(encoder->stateB)){
    if ((encoder->pstateA) && (encoder->pstateB) ){
      (encoder->tick)--;
    } else {
      (encoder->tick)++;
    }
  } else {
    if (!(encoder->pstateA) && (encoder->pstateB) ){
      (encoder->tick)--;
    } else {
      (encoder->tick)++;
    }
  }


}




Encoder::Encoder(int pinA, int pinB):
pinA(pinA),
pinB(pinB),
tick(0),
interruptA(new EncoderInterruptA(this)),
interruptB(new EncoderInterruptB(this)),
stateA(0),
stateB(0),
pstateA(0),
pstateB(0){
	id = count;
	count = 2 + count;

	pinMode(pinA, INPUT);
	pinMode(pinB, INPUT);
	attachInterrupt(digitalPinToInterrupt(pinA), Interrupt::getInterrupt(id), CHANGE);
	attachInterrupt(digitalPinToInterrupt(pinB), Interrupt::getInterrupt(id+1), CHANGE);

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
