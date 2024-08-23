#pragma once

#include <chrono>

class TimeManager
{
public:
	TimeManager();

	void Start();
	void Tick();

	double DeltaTime();
	double FPS();
	double MSPF();
	double ElapsedTime();
protected:

	////All times are in ms
	//double previousTime;	//Time last frame
	//double currentTime;		//Time this frame

	std::chrono::steady_clock::time_point previousTime;
	std::chrono::steady_clock::time_point currentTime;

	double elapsedTime;		//Time since start was called

	int frameCount;	//Number of frames since start
};