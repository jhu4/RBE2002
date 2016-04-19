#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

class LightSensor{
	private:
		const int Apin;
		const int Dpin;
		const int offset;
		bool isCandle;
		int averageReading;
		long accumulator;
		int counter;
		int currentReading;
		int lastReading;

	public:
		LightSensor(int Apin, int Dpin, int ofs);
    bool sense();
		void initialize();
		bool isDetectLight();
		bool isGetCloser();
		int getReading();
		float getDistance();
};

#endif
