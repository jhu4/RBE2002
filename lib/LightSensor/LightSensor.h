#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H


class LightSensor{
	private:
		static const int capacity=20;
		const int Apin;
		const int Dpin;
		const unsigned int offset;
		bool isCandle;
		bool enable;
		unsigned int averageReading;
		int index;
		int size;
		int readinglst[capacity];

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
