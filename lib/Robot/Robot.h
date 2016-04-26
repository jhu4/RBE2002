#ifndef ROBOT_H
#define ROBOT_H

#include "TurretController.h"
#include "Displayer.h"
#include "ZWallFollower.h"
#include "Location.h"

class Robot{
	private:
		bool isFindCandle;
		bool isYawScanEnded;
		bool isPitchScanEnded;
		TurretController& tc;
		ZWallFollower& wf;
		Displayer& displayer;
		Location& loca;
		void returnToOrigin();

	public:
		Robot(Location& l,ZWallFollower& wf, TurretController& tc, Displayer& dp);
		~Robot();
		void initializing();
		void robotGO();
};
#endif
