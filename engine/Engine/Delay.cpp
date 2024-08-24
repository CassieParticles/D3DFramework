#include "Delay.h"

Delay::Delay(double delay, TimeManager* timeManager):delay{delay},timeManager{timeManager},time{0},triggered{false},enabled{false}
{
}

void Delay::Tick()
{
	if (enabled)
	{
		//Was enabled last frame
		triggered = true;
		enabled = false;
	}
	if (!triggered)
	{
		time += timeManager->DeltaTime();
		enabled = time > delay;
	}


}
