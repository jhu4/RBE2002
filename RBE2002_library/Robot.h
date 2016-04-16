#ifndef ROBOT_H
#define ROBOT_H

#include <FanController.h>
#include <Displayer.h>
#include <WallFollower.h>
#include <Location.h>

class Robot{
	private:	
		FanController fancontroller;
		WallFollower wallfollower;
		Displayer displayer;
		Location location;
		LightSensor lightsensor;
		int yawAngle,pitchAngle;
		float deltaX,deltaY,Z;
		bool isfindCandle;
		void locateInYaw();
		void locateInPitch();
		void returnToOrigin();

	public:
		Robot(Location& l,FanController f, Displayer d, WallFollower w, LightSensor ls);
		~Robot();
		void initializing();
		void robotGO();
		void locateCandle();
};
#endif
