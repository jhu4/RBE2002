#ifndef LOCATION_H
#define LOCATION_H

class Location{
	private:
    float x;
    float y;

	public:	
		Location();
		~Location();
		float getX();
		float getY();
		void update(float deltaX, float deltaY);
  
};

#endif
