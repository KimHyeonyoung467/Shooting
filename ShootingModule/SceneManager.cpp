#include "pch.h"
#include "SceneManager.h"

namespace Scenes
{


	SceneManager::SceneManager()
		: m_sceneName("empty"), m_curentScene()
	{
	}

	SceneManager::~SceneManager()
	{

	}

	void SceneManager::CreateScene(const string& name, unique_ptr<Scenes::Scene> scene)
	{
		addScene(name, std::move(scene));
	}

	void SceneManager::ChangeScene(const string& name)
	{
		Scenes::Scene* nextScene = getScene(name);

		// type 별 현재 이름 설정 
		if (nextScene)
		{
			m_curentScene = nextScene;
			m_sceneName = name;
		}
	}

	void SceneManager::update()
	{
		// 항상 체크해서 씬을 전환 
		cout << endl;
		cout << endl;
		cout << endl;
		cout << "[DEBUG] curent Scene  : " << m_sceneName << endl;
		vaildate(m_curentScene);

		m_curentScene->update(); // m_curScene 이 널이 아닐 때 항상 호출하게 하기. 

		if (m_curentScene->getScore() == 10)
			ChangeScene("End"); 

	}
	void SceneManager::addScene(const string& name, unique_ptr<Scenes::Scene> scene)
	{
		m_Scenemap[name] = std::move(scene);
	}

	Scenes::Scene* SceneManager::getScene(const string& name)
	{
		auto findScene = m_Scenemap.find(name);

		// 찾아낸 Scene 이 존재하는 경우 
		if (findScene != m_Scenemap.end())
		{
			cout << "[Debug] " << name << " 씬을 찾아냈습니다!" << endl;
			auto& scene = findScene->second;

			return scene.get();
		}
		return nullptr;
	}

	void SceneManager::Render()
	{
		if (!m_curentScene) return;

		vaildate(m_curentScene);

		m_curentScene->Render();

	}
}