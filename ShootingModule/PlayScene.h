#pragma once
#include "Scene.h"
#include "keyboardInputManager.h" 
#include "AppResourceManager.h"

namespace Scenes
{
	class PlayScene :
		public Scene
	{
	public:
		PlayScene(); 
		~PlayScene() = default; 
		void Initialize() override;
		void update() override;
		void Render() override;

	private : 
		shared_ptr<Resource::AppResourceManager> m_appResource; 
	};

}


