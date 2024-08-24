#include "Timer.h"

Timer::Timer(double interval, TimeManager* timeManager) :interval{ interval }, timeManager{ timeManager }, sumTime{}
{
}

void Timer::Tick()
{
	sumTime += timeManager->DeltaTime();
	if (enabled = sumTime > interval)
	{
		sumTime -= interval;
	}
}
