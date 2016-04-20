#ifndef MOTOR_H
#define MOTOR_H

#define FORWARD 1
#define BACKWARD 0

class Motor{
	private:
		int speedPin;
		int dirAPin;
		int dirBPin;
		bool dir;
		int speed;
		bool invert;

	public:
		Motor(int speedPin, int dirAPin, int dirBPin, bool invert);
		void setDir(bool forwardDir);
		void setSpeed(int speed);
		~Motor();
};

#endif
