#ifndef WALLSENSOR_H
#define WALLSENSOR_H

class WallSensor{
	private:
		int pin;
		int reading;
		int lastreading;

	public:
		WallSensor(int pin);
		void initializing();
    int sense();
		bool isWall();
		bool isFindGap();
		bool isGap();
		bool isSame();
		
};

#endif
