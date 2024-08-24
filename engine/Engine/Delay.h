#pragma once

#include <engine/Engine/TimeManager.h>

class Delay
{
public:
	Delay(double delay, TimeManager* timeManager = TimeManager::getTimeManager());
	~Delay() = default;

	void Tick();

	bool isEnabled() { return enabled; }
	void reset() 
	{ 
		time = 0;
		triggered = false;
	}
protected:
	TimeManager* timeManager;

	double delay;
	double time;

	bool enabled;
	bool triggered;
};