#include "Location.h"

Location::Location(){
  x = 0;
  y = 0;
} 

float Location::getX(){
	return x;
}

float Location::getY(){
	return y;
}

void Location::update(float x, float y){
	this->x+=x;
	this->y+=y;
}

bool Location::isOrigin(int offset){
	return (abs(x-0)<offset && abs(y-0)<offset);
}