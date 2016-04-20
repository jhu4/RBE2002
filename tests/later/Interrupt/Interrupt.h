#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <Arduino.h>

#define MAX_INTERRUPTS 10

typedef void (*vfunc)();

class Interrupt {
  private:

  public:
    static Interrupt* ISRVectorTable[MAX_INTERRUPTS];
    Interrupt();
    static void Register(int interruptNum, Interrupt* interrupt);
    static void Interrupt_0();
    static void Interrupt_1();
    static void Interrupt_2();
    static void Interrupt_3();
    static vfunc getInterrupt(int num);
    virtual void isr();
};

class Timer;

class TimerInterrupt: public Interrupt {
  private:
    Timer* timer;
  public:
    TimerInterrupt(Timer* timer);
    virtual void isr();
};

class Timer {
  friend class TimerInterrupt;
  private:
    TimerInterrupt* interrupt;
    int count;
  public:
    Timer();
    int getCount();
};

#endif
