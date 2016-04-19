#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

class Encoder{
	private:
		int pinA;
		int pinB;
		volatile int tick;

	public:
		Encoder(int pinA, int pinB);
		void tickISR();
		void resetTicks();
		int getTicks();
		~Encoder();
};

#endif
