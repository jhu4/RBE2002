#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

class LightSensor{
	private:
		int pin;

	public:
		LightSensor(int pin);
		~LightSensor();
		bool isDetectLight();
		float reportDistance();
};

#endif
