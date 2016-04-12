#include <WallSensorManager.h>


WallSensorManager::WallSensorManager(int p, int p1, int p2):
head(p),side1(p1),side2(p2){

}

void WallSensorManager::initializing(){
	head.initializing();
	side1.initializing();
	side2.initializing();
}

enum MotionStatus WallSensorManager::reportStatus(){

}



