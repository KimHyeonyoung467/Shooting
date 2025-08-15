#pragma once
#include "InputConstants.h"

namespace Input
{
	template<typename DeviceType> 
	class InputManager;

	struct KeyboardDevice; 

	using Keyboard = InputManager<KeyboardDevice>;
}