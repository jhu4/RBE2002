#include "SpecialWallSensor.h"

SpecialWallSensor::SpecialWallSensor(int p):WallSensor(p){

}

bool SpecialWallSensor::isWall(){
	return reading>220;
}
