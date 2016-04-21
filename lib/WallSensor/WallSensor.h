#ifndef WALLSENSOR_H
#define WALLSENSOR_H

class WallSensor{
	protected:
		int pin;
		int reading;
		int lastreading;
		int wallValue;

	public:
		WallSensor(int pin, int isWallValue);
		void initialize();
    int getReading();
    int sense();
		bool isWall();
		bool isFindGap();
		bool isGap();
		bool isSame();
		bool notWall();
};

#endif
