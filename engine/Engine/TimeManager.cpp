#include "TimeManager.h"

#include <glfw3.h>


TimeManager::TimeManager(Window* window) :window{ window }, previousTime{}, currentTime{}, elapsedTime{}, frameCount{ 0 }
{
}

void TimeManager::Start()
{
	elapsedTime = 0;
	frameCount = 0;
	previousTime = glfwGetTime();
	currentTime = glfwGetTime();
}

void TimeManager::Tick()
{
	previousTime = currentTime;
	currentTime = glfwGetTime();
	elapsedTime += DeltaTime();
	++frameCount;
}

double TimeManager::DeltaTime()
{
	return currentTime - previousTime;
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
