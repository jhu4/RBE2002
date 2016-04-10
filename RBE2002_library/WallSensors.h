#ifndef WALLSENSORS_H
#define WALLSENSORS_H

class WallSensors{
	private:
		int headPin;
		int tailPin;
		float headDistance;
		float tailDistance;

	public:
		WallSensors(int pin1, int pin2);
		void initializing();
		bool isTurningRight();
		bool isTurningLeft();
		float getDistanceNaunce();
};

#endif
