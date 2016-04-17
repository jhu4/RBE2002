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
		
	public:	
		Motor(int speedPin, int dirAPin, int dirBPin);
		setDir(bool forwardDir);
		setSpeed(int speed);
		~Motor();
};

#endif