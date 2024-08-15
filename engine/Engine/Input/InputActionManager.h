#pragma once

#include <vector>

#include <engine/Engine/Input/InputAction.h>

class InputActionManager
{
public:
	static InputActionManager* Instance();
	
	void setUpdateInput() { updateInput = true; }

	void addInputAction(const std::string& name,int* inputs, int inputCount, InputAction::ActionType actionType);

	void update();

	bool getActionTriggered(const std::string& name);
protected:
	bool updateInput{};

	static InputActionManager* instance;

	std::vector<InputAction> inputActions;

	int getActionIndex(const std::string& name);
};