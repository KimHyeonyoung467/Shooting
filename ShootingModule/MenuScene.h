#pragma once
#include "Scene.h"

namespace Scenes
{
	class MenuScene
		: public Scene
	{
	public:
		void Initialize() override;
		void update() override;
		void Render() override;
	};

}

