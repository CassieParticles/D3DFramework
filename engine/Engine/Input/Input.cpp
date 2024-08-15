#include "Input.h"

#include <glfw3.h>

#include <engine/Engine/Window.h>

Input* Input::instance = nullptr;

Input::Input()
{
	keyStatesCurrent = new bool[GLFW_KEY_LAST];
	keyStatesPrev = new bool[GLFW_KEY_LAST];
	window = Window::Instance();
}

Input::~Input()
{
	delete[] keyStatesCurrent;
	delete[] keyStatesPrev;
}

Input* Input::Instance()
{
	if (instance == nullptr)
	{
		instance = new Input();
	}

	return instance;
}

void Input::update()
{
	//Poll events to get key inputs
	glfwPollEvents();

	//Swap arrays, so prev array is last frame's keys, better then copying current to prev every frame
	bool* tempPtr = keyStatesPrev;
	keyStatesPrev = keyStatesCurrent;
	keyStatesCurrent = tempPtr;

	//Update current array with this frame's inputs
	for (int i = 0; i < GLFW_KEY_LAST; ++i)
	{
		keyStatesCurrent[i] = glfwGetKey(window->getWindow(), i);
	}
}

bool Input::getKeyDown(int key)
{
	return keyStatesCurrent[key];
}

bool Input::getKeyPressed(int key)
{
	return keyStatesCurrent[key] && !keyStatesPrev[key];
}

bool Input::getKeyReleased(int key)
{
	return !keyStatesCurrent[key] && keyStatesPrev[key];
}