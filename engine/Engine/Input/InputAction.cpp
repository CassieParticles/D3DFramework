#include "InputAction.h"

InputAction::InputAction(const std::string& name, int* inputs, int inputCount, ActionType type) :name{ name },inputs { inputs }, inputCount{ inputCount }
{
	input = Input::Instance();
	switch (type)
	{
	case DOWN:
		actionFunction = [](bool c, bool l) -> bool {return c; };
		break;
	case PRESS:
		actionFunction = [](bool c, bool l) ->bool {return c && !l; };
		break;
	case RELEASE:
		actionFunction = [](bool c, bool l) ->bool {return !c && l; };
		break;
	}
}

void InputAction::Update()
{
	//Set last frame to be the "this frame" for last frame
	pressedLastFrame = pressedThisFrame;
	pressedThisFrame = false;
	for (int i = 0; i < inputCount; ++i)
	{
		pressedThisFrame |= Input::Instance()->getKeyDown(inputs[i]);
	}
}

bool InputAction::getTriggered()
{
	return actionFunction(pressedThisFrame, pressedLastFrame);
}
