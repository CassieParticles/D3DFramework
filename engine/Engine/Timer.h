#pragma once

#include <engine/Engine/TimeManager.h>

class Timer
{
public:
	Timer(double interval, TimeManager* timeManager = TimeManager::getTimeManager());
	~Timer() = default;

	double changeInteval(double interval) { this->interval = interval; }

	void Tick();


	bool isEnabled() { return enabled; }
protected:
	TimeManager* timeManager;

	double interval;

	double sumTime;

	bool enabled;
};
