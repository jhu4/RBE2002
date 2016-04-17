#ifndef ENCODER_H
#define ENCODER_H

class Encoder{
	private:
		int pin1;
		int pin2;
		
	public:	
		Encoder(int p1, int p2);
		~Encoder();
};

#endif