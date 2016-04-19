#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>
#include "Interrupt.h"


class Encoder;

class EncoderInterrupt: public Interrupt {
  private:
    Encoder* encoder;
  public:
    EncoderInterrupt(Encoder* encoder);
    virtual void isr();
};

class Encoder{
	friend class EncoderInterrupt;
	private:
		static int count;

		int pinA;
		int pinB;
		volatile int tick;
		EncoderInterrupt* interrupt;

	public:
		int id;
		Encoder(int pinA, int pinB);
		void tickISR();
		void resetTicks();
		int getTicks();
		~Encoder();
};

#endif
