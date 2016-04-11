#include <WallSensors.h>

WallSensors::WallSensors(int head, int side1, int side2):
headpin(pin1),sidepin1(side1),sidepin2(side2),
sidedistance1(0),sidedistance2(0),headdistance(0){

}

void WallSensors::initializing(){
	pinMode(headpin, INPUT);
	pinMode(sidepin1, INPUT);
	pinMode(sidepin2, INPUT);
}

/**Report the status in enum form 
*/
enum MotionStatus WallSensors::reportStatus(){

}

bool WallSensors::isSideWall(){

}

bool WallSensors::isFrontWall(){

}



/*Private*/
bool WallSensors::isTurningRight(){
	return (sidedistance1-sidedistance2)>50;
}

bool WallSensors::isTurningLeft(){
	return (sidedistance2-sidedistance1)>50;
}

bool isWallinFront(){
	return headdistance<600;
}

float getDistanceNaunce(){
	return sidedistance1-sidedistance2;	
}