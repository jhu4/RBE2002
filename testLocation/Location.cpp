#include "Location.h"

Location::Location():{
  x = 0;
  y = 0;
} 

Location::~Location(){
	
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

