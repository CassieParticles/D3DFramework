#pragma once
#include <functional>
#include <string>

#include <engine/Engine/Input/Input.h>

class InputAction
{
public:
	enum ActionType
	{
		DOWN,
		PRESS,
		RELEASE
	};

	InputAction(const std::string& name,int* inputs, int inputCount, ActionType type);
	~InputAction() { delete[] inputs; }

	void Update();

	bool getTriggered();

	const std::string& getName() { return name; }
protected:
	//Input pointer
	Input* input;

	std::string name;

	//All inputs tied to this action
	int* inputs;
	int inputCount;

	//Since variable number of input actions, it's easier to have this here
	bool pressedThisFrame{};
	bool pressedLastFrame{};
	
	//Type of action
	std::function<bool(bool curr, bool last)> actionFunction;
};