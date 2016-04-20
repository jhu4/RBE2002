#ifndef LOCATION_H
#define LOCATION_H
#include <Arduino.h>

class Location{
	private:
    float x;
    float y;

	public:	
		Location();
		float getX();
		float getY();
		void update(float deltaX, float deltaY);
		bool isOrigin(int offset);
  
};

#endif
