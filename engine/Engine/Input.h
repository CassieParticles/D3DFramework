#pragma once

class Window;


class Input
{
public:
	static Input* Instance();

	//Update inputs to current frame
	void update();

	//Down-Held down, Pressed-Pressed this frame, Released-Released this frame
	bool getKeyDown(int key);
	bool getKeyPressed(int key);
	bool getKeyReleased(int key);
protected:
	Input();
	~Input();

	static Input* instance;

	bool* keyStatesCurrent;
	bool* keyStatesPrev;

	Window* window;
};