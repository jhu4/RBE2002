#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H


class LightSensor{
	private:
		static const int capacity=50;
		const int Apin;
		const int threshold;
		bool isCandle;
		long averageReading;
		int index;
		int size;
		int readinglst[capacity];
		void indexIncrement();
		int lastIndex();

	public:
		LightSensor(int Apin, unsigned int thr);
    bool sense();
		void initialize();
		bool isDetectLight();
		//bool isGetCloser();
		int getReading();
		float getDistance();
		int getAverageReading();
		void reset();
};

#endif
