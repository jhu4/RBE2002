#ifndef MOTOR_H
#define MOTOR_H

class Motor{
	private:
		int pin;
		int directionpin;
		
	public:	
		Motor(int p, int directionpin);
		~Motor();
};

#endif