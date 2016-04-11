#ifndef WALLSENSORS_H
#define WALLSENSORS_H

enum MotionStatus{
	TURN_RIGHT,
	TURN_LEFT,
	GO_STRAIGHT
};


class WallSensors{
	private:
		int headPin;
		int sidePin1;
		int sidePin2;
		float sidedistance1;
		float sidedistance2;
		float headdistance;
		bool isTurningRight();
		bool isTurningLeft();
		float getDistanceNaunce();

	public:
		WallSensors(int pin1, int pin2);
		void initializing();
		bool isSideWall();
		bool isFrontWall();
		enum MotionStatus reportStatus();
};

#endif
