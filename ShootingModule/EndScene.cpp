#include "pch.h"
#include "EndScene.h"
namespace Scenes
{

	EndScene::EndScene() 
	{

	}

	void EndScene::Initialize()
	{

	}

	void EndScene::update()
	{
		Scenes::Scene::update();

	}

	void EndScene::Render()
	{
		cout << "EndScene Render" << endl;
		Scenes::Scene::Render();
	}



}