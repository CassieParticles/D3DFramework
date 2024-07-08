#pragma once
#include <functional>
#include <string>

#include <engine/Engine/Input/Input.h>

class InputAction
{
public:
	enum ActionType
	{
		DOWN_OR,
		PRESS_OR,
		RELEASE_OR,
		DOWN_AND,
		PRESS_AND,
		RELEASE_AND
	};

	InputAction(const std::string& name,int* inputs, int inputCount, ActionType type);
	InputAction(const std::string& name, int* inputs, int inputCount, std::function<bool(bool* current, bool* last, int count)> actionFunction);
	~InputAction();

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

	//One boolean for each input action, allows more complex methods
	bool* pressedThisFrame;
	bool* pressedLastFrame;
	
	//Type of action
	std::function<bool(bool* curr, bool* last, int count)> actionFunction;
};