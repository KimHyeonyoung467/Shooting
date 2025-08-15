#include "pch.h"
#include "KeyboardInputManager.h"

namespace Input {
	InputManager<KeyboardDevice>& InputManager<KeyboardDevice>::GetInstance()
	{
		static InputManager instance; // Singleton Instance Get Code 
		return instance;
	}

	void InputManager<KeyboardDevice>::update()
	{
		std::memcpy(prevState.data(), currState.data(), sizeof(SHORT) * MAX_KEY_COUNT);
		for (int i = 0; i < MAX_KEY_COUNT; ++i)
		{
			currState[i] = GetAsyncKeyState(i);
		}
	}

	bool InputManager<KeyboardDevice>::isKeyDown(int vKey) const  // key Button Down 
	{
		return (currState[vKey] & KEY_PRESSED_FLAG) != 0;
	}

	bool InputManager<KeyboardDevice>::isKeyPressed(int vKey) const // key Button Pressed
	{
		return (!(prevState[vKey] & KEY_PRESSED_FLAG) && (currState[vKey] & KEY_PRESSED_FLAG));
	}

	bool InputManager<KeyboardDevice>::isKeyReleased(int vKey) const  // Key Button Up 
	{
		return ((prevState[vKey] & KEY_PRESSED_FLAG) && !(currState[vKey] & KEY_PRESSED_FLAG));
	}

}