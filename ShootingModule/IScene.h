#pragma once
#include "pch.h"

namespace Scenes
{

	class IScene
	{
	public:
		IScene() = default;
		virtual ~IScene() = default;

		virtual void Initialize() = 0;
		virtual void update() = 0;
		virtual void Render() = 0;

	};

}

