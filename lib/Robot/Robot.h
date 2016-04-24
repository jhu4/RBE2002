#ifndef ROBOT_H
#define ROBOT_H

#include "TurretController.h"
#include "Displayer.h"
#include "ZWallFollower.h"
#include "Location.h"

class Robot{
	private:
		TurretController tc;
		ZWallFollower wf;
		Displayer displayer;
		Location loca;
		void returnToOrigin();

	public:
		Robot(Location& l,FanController f, Displayer d, WallFollower w, LightSensor ls);
		~Robot();
		void initializing();
		void robotGO();
};
#endif
