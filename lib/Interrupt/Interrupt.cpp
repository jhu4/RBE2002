#include "Interrupt.h"

Interrupt* Interrupt::ISRVectorTable[MAX_INTERRUPTS];


Interrupt::Interrupt(){
}

void Interrupt::Register(int index, Interrupt* interrupt){
  ISRVectorTable[index] = interrupt;
}

void Interrupt::Interrupt_0(){
  ISRVectorTable[0]->isr();
}

void Interrupt::Interrupt_1(){
  ISRVectorTable[1]->isr();
}

vfunc Interrupt::getInterrupt(int num){
  if (num == 0 ){
    return Interrupt::Interrupt_0;
  } else {
    return Interrupt::Interrupt_1;
  }
}

void Interrupt::isr(){
}



TimerInterrupt::TimerInterrupt(Timer* timerA){
  timer = timerA;
  Interrupt::Register(0, this);
}

void TimerInterrupt::isr(){
  (timer->count)++;
}



Timer::Timer(){
  interrupt = new TimerInterrupt(this);
}

int Timer::getCount(){
  return count;
}
