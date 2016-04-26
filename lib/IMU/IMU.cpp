#include "IMU.h"

IMU::IMU():
	time(0)
	,enable(true),index(0)
	,endAngle(0){

}



bool IMU::initialize(){
	if(enable){
		gyro.init();
		gyro.enableDefault();
		enable=false;
		time = millis()+1000;
	}
	if(millis()>=time && !enable){
		gyro.read();
  	gerrx+=gyro.g.x;
  	gerry+=gyro.g.y;
  	gerrz+=gyro.g.z;
  	time = millis()+25;
  	index++;
  	if(index==100){
  		gerrx = gerrx/100;
  		gerry = gerry/100;
 		  gerrz = gerrz/100;
 		  time = 0;
  		return true;
  	}
	}
	return false;
}


void IMU::setEndAngle(int angle){
	endAngle=angle+gyro_z;
}



bool IMU::update(){
  if (millis()>=time) {
    gyro.read();
    gyro_x = (gyro.g.x - gerrx) * G_gain;
    gyro_y = (gyro.g.y - gerry) * G_gain;
    gyro_z = (gyro.g.z - gerrz) * G_gain;

    gyro_x = gyro_x * G_Dt;
    gyro_y = gyro_y * G_Dt;
    gyro_z = gyro_z * G_Dt;

    gyro_x += gyro_xold;
    gyro_y += gyro_yold;
    gyro_z += gyro_zold;

    gyro_xold = gyro_x ;
    gyro_yold = gyro_y ;
    gyro_zold = gyro_z ;
    // flag = 0;

    time = millis()+5;
	}

	return (abs(endAngle-gyro_z)<2? true: false);
}
