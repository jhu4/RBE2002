#include "IMU.h"

IMU::IMU():
	time(0)
	,enable(true),index(0)
	,endAngle(999)
	,isinitialize(false){

}



void IMU::initialize(){
	if(enable){
		Wire.begin();
		if(!gyro.init()){
			Serial.println("Failed to autodetect gyro type!");
		}
		else{
			enable=false;
		}
		gyro.enableDefault();
		time = millis()+1000;
	}
	if(millis()>=time && !enable){
		gyro.read();
  	gerrx+=gyro.g.x;
  	gerry+=gyro.g.y;
  	gerrz+=gyro.g.z;
  	index++;
  	if(index>=100){
  		gerrx = gerrx/100;
  		gerry = gerry/100;
 		  gerrz = gerrz/100;
 		  time = 0;
  		isinitialize=true;
  	}
		time = millis()+25;
	}
}

bool IMU::isInitialized(){
	return isinitialize;
}

void IMU::setEndAngle(float angle){
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

float IMU::getgyroY(){
	return gyro_y;
}

float IMU::getgyroZ(){
	return gyro_z;
}

float IMU::getgyroX(){
	return gyro_x;
}

float IMU::getEndAngle(){
	return endAngle;
}
