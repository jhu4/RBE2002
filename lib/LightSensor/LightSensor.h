#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

#define INDEXMAX 20

class LightSensor{
	private:
		const int Apin;
		const int Dpin;
		const unsigned int offset;
		bool isCandle;
		bool enable;
		unsigned int averageReading;
		int index;
		int readinglst[INDEXMAX];

	public:
		LightSensor(int Apin, int Dpin, unsigned int ofs);
    bool sense();
		void initialize();
		bool isDetectLight();
		bool isGetCloser();
		int getReading();
		float getDistance();
		void indexIncrement();
		int lastIndex();
};

#endif
