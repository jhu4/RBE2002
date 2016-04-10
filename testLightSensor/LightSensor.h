#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

class LightSensor{
	private:
		const int pin;
		const int offset;
		int averageReading;
		long accumulator;
		int counter;
		int currentReading;
		int lastReading;

	public:
		LightSensor(int pin, int ofs);
    bool watch();
		void initializing();
		bool isDetectLight();
		bool isGetCloser();
};

#endif
