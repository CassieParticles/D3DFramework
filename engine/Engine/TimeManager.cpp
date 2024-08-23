#include "TimeManager.h"

#include <chrono>

TimeManager::TimeManager() : previousTime{}, currentTime{}, elapsedTime{}, frameCount{ 0 }
{
}

void TimeManager::Start()
{
	elapsedTime = 0;
	frameCount = 0;
	previousTime = std::chrono::high_resolution_clock::now();
	currentTime = std::chrono::high_resolution_clock::now();
}

void TimeManager::Tick()
{
	previousTime = currentTime;
	currentTime = std::chrono::high_resolution_clock::now();
	elapsedTime += DeltaTime();
	++frameCount;
}

double TimeManager::DeltaTime()
{
	long long microTime = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - previousTime).count();
	return microTime / 1000000.0;
}

double TimeManager::FPS()
{
	return frameCount / elapsedTime;
}

double TimeManager::MSPF()
{
	return 1000.0 / FPS();
}

double TimeManager::ElapsedTime()
{
	return elapsedTime;
}
