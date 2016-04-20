#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>
#include "Interrupt.h"


class Encoder;

class EncoderInterruptA: public Interrupt {
  private:
    Encoder* encoder;
  public:
    EncoderInterruptA(Encoder* encoder);
    virtual void isr();
};

class EncoderInterruptB: public Interrupt {
  private:
    Encoder* encoder;
  public:
    EncoderInterruptB(Encoder* encoder);
    virtual void isr();
};

class Encoder{
	friend class EncoderInterruptA;
  friend class EncoderInterruptB;
	private:
		static int count;

		int pinA;
		int pinB;
		volatile int tick;
		EncoderInterruptA* interruptA;
    EncoderInterruptB* interruptB;
    bool stateA;
    bool stateB;
    bool pstateA;
    bool pstateB;

	public:
		int id;
		Encoder(int pinA, int pinB);
		void tickISR();
		void resetTicks();
		int getTicks();
		~Encoder();
};

#endif
