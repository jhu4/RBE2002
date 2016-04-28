#ifndef	IMU_H
#define IMU_H

#include <Arduino.h>
#include "L3G.h"
#include <Wire.h>

class IMU{
	private:
		const float G_gain=0.00870;
		const float G_Dt = 0.0155;
		float gyro_x,gyro_y,gyro_z;
		float gyro_xold,gyro_yold,gyro_zold;
		float gerrx,gerry,gerrz;
		unsigned long time;
		bool enable;
		int index;
		float endAngle;
		bool isinitialize;
		L3G gyro;


	public:
		IMU();
		void initialize();
		void setEndAngle(float angle);
		bool isInitialized();
		bool update();
		float getgyroY();
		float getgyroZ();
		float getgyroX();
		float getEndAngle();


};

#endif
