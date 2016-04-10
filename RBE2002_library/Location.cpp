#include <Location.h>

Location::Location():x(0),y(0){

} 

Location::~Location(){
	
}

float Location::getX(){
	return this->x;
}

float Location::getY(){
	return this->y;
}


void Location::update(float x, float y){
	this->x+=x;
	this->y+=y;
}

