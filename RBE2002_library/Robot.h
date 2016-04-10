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
		Location loca;

	public:
		Robot(FanController f, Displayer d, WallFollower w);
		~Robot();
		void initializing();
		void robotGO();
};
#endif
