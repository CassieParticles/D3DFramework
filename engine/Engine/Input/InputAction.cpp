#include "InputAction.h"
#include "InputActionFuncs.h"	//Common functions

InputAction::InputAction(const std::string& name, int* inputs, int inputCount, ActionType type) :name{ name },inputs { inputs }, inputCount{ inputCount }
{
	input = Input::Instance();
	pressedThisFrame = new bool[inputCount];
	pressedLastFrame = new bool[inputCount];

	switch (type)
	{
	case DOWN_OR:
		actionFunction = InputActions::downOrFunc;
		break;
	case PRESS_OR:
		actionFunction = InputActions::pressedOrFunc;
		break;
	case RELEASE_OR:
		actionFunction = InputActions::releasedOrFunc;
		break;
	case DOWN_AND:
		actionFunction = InputActions::downAndFunc;
		break;
	case PRESS_AND:
		actionFunction = InputActions::pressedAndFunc;
		break;
	case RELEASE_AND:
		actionFunction = InputActions::releasedAndFunc;
		break;
	}

}

InputAction::InputAction(const std::string& name, int* inputs, int inputCount, std::function<bool(bool* current, bool* last, int count)> actionFunction) :name{ name }, inputs{ inputs }, inputCount{ inputCount }, actionFunction{ actionFunction }
{
	input = Input::Instance();
	pressedThisFrame = new bool[inputCount];
	pressedLastFrame = new bool[inputCount];
}

InputAction::~InputAction()
{
	delete[] inputs;
	delete[] pressedThisFrame;
	delete[] pressedLastFrame;
}

void InputAction::Update()
{
	//Set last frame to be the "this frame" for last frame

	//Swap arrays, saves copying them
	bool* temp = pressedLastFrame;
	pressedLastFrame = pressedThisFrame;
	pressedThisFrame = temp;

	for (int i = 0; i < inputCount; ++i)
	{
		pressedThisFrame[i] = input->getKeyDown(inputs[i]);
	}
}

bool InputAction::getTriggered()
{
	return actionFunction(pressedThisFrame, pressedLastFrame,inputCount);
}
