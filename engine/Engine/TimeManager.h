#pragma once

#include <engine/Engine/Window.h>

class TimeManager
{
public:
	TimeManager(Window* window = Window::Instance());

	void Start();
	void Tick();

	double DeltaTime();
	double FPS();
	double MSPF();
	double ElapsedTime();
protected:
	Window* window;

	//All times are in ms
	double previousTime;	//Time last frame
	double currentTime;		//Time this frame
	double elapsedTime;		//Time since start was called

	int frameCount;	//Number of frames since start
};