#ifndef WALLSENSOR_H
#define WALLSENSOR_H

class WallSensor{
	protected:
		int pin;
		int reading;
		int lastreading;

	public:
		WallSensor(int pin);
		void initialize();
    int getReading();
    int sense();
		bool isWall();
		bool isFindGap();
		bool isGap();
		bool isSame();
		
};

#endif
