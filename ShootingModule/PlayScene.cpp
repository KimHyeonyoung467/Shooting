#include "pch.h"
#include "PlayScene.h"

namespace Scenes
{

	PlayScene::PlayScene() : m_appResource(Resource::AppResourceManager::Get())
	{

	}

	void PlayScene::Initialize()
	{
		
	}

	void PlayScene::update()
	{
		Scenes::Scene::update();

	}

	void PlayScene::Render()
	{
		cout << "PlayScene Render" << endl;
		Scenes::Scene::Render();
	}



}
