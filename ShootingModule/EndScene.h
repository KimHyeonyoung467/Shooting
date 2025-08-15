#pragma once
#include "Scene.h"
#include "keyboardInputManager.h" 

namespace Scenes
{
	class EndScene :
		public Scene
	{
	public:
		EndScene();
		~EndScene() = default;
		void Initialize() override;
		void update() override;
		void Render() override;
	
	};

}


