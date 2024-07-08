#include "InputActionManager.h"

#include <iostream>

InputActionManager* InputActionManager::instance = nullptr;

InputActionManager* InputActionManager::Instance()
{
	if (instance == nullptr)
	{
		instance = new InputActionManager();
	}

	return instance;
}

void InputActionManager::addInputAction(const std::string& name, int* inputs, int inputCount, InputAction::ActionType actionType)
{
	//In case inputs isn't heap allocated
	int* inputsHeap = new int[inputCount];
	std::copy(inputs, inputs + inputCount, inputsHeap);
	
	inputActions.emplace_back(name, inputsHeap, inputCount, actionType);
}

void InputActionManager::update()
{
	for (int i = 0; i < inputActions.size(); ++i)
	{
		inputActions.at(i).Update();
	}
}

bool InputActionManager::getActionTriggered(const std::string& name)
{
	int index;
	if (index = getActionIndex(name) == -1)
	{
		return false;
	}
	return inputActions.at(index).getTriggered();
}

int InputActionManager::getActionIndex(const std::string& name)
{
	for (int i = 0; i < inputActions.size(); ++i)
	{
		if (inputActions.at(i).getName() == name)
		{
			return i;
		}
	}
	std::cerr << "Error: Failed to find input action\n";
	return -1;
}


