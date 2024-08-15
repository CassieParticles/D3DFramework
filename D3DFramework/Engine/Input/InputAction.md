Stores array of inputs + size of array
Stores std::function to evaluate how input is handled (input this frame, input last frame, output result)
Used within [[InputActionManager]] to create InputActions
Inputs can be changed at runtime

premade std::functions for down, pressed and released

Function to check if input action is active