#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H


class LightSensor{
	private:
		static const int capacity=20;
		const int Apin;
		const unsigned int offset;
		bool isCandle;
		unsigned int averageReading;
		int index;
		int size;
		int readinglst[capacity];
		void indexIncrement();
		int lastIndex();

	public:
		LightSensor(int Apin, unsigned int ofs);
    bool sense();
		void initialize();
		bool isDetectLight();
		bool isGetCloser();
		int getReading();
		float getDistance();
		bool getIsCandle();
};

#endif
