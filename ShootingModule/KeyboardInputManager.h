#pragma once
#include <array> 
#include "InputManager.h" 


namespace Input
{

	struct KeyboardDevice {};

	template<> 
	class InputManager<KeyboardDevice>
	{
	public: 
		static InputManager& GetInstance(); 

		void update(); 
		bool isKeyDown(int vKey) const;
		bool isKeyPressed(int vKey) const;
		bool isKeyReleased(int vKey) const;

	private: 
		InputManager() = default; 
		~InputManager() = default; 

		InputManager(const InputManager&) = delete; 
		InputManager& operator=(const InputManager&) = delete; 

		std::array<SHORT, Input::MAX_KEY_COUNT> prevState{}; 
		std::array<SHORT, Input::MAX_KEY_COUNT> currState{}; 

	};
}

