#pragma once
#include "Scene.h"
#include <unordered_map>

namespace Scenes {

	class SceneManager
	{
	public:
		SceneManager();
		~SceneManager();

		// 씬을 생성하여  Scene 파일의 unordared_map 에 저장된다. 
		void CreateScene(const string& name, unique_ptr<Scenes::Scene> scene);

		// 현재 타입에 따라서, 현재 씬을 타입에 맞는 씬으로 변경한다. 
		void ChangeScene(const string& name);

		// 현재 씬에 따라서 update 와 Render 를 호출 
		void update();
		void Render();

		// 생성한 씬들의 인스턴스 주소를 vector m_vScenes 에 저장 
		void addScene(const string& name, unique_ptr<Scenes::Scene> scene);
		Scenes::Scene* getScene(const string& name);

		// 현재 씬 상태에 따라서 이름 변경 
		void setName(const string& nm) { m_sceneName = nm; }
		const string& getName() const { return m_sceneName; }

		// 현재 씬을 변경하고 지정 
		void setcurentScene(Scenes::Scene* curScene) { m_curentScene = curScene; }
		Scenes::Scene* getcurentScene() { return m_curentScene; }

	private:
		// key 
		string m_sceneName;


		// 생성한 씬들의 주소를 저장할 컨테이너 
		unordered_map<string, unique_ptr<Scenes::Scene>> m_Scenemap; // 씬들을 관리할 컨테이너

		// 씬 제어 씬 인스턴스 주소에 따라서 변경하게 하기 
		Scenes::Scene* m_curentScene;


		static void vaildate(const Scenes::Scene* scene)
		{
			if (scene == nullptr)
				throw invalid_argument("ScenManager :: m_curentScene is Nullptr!");
		}

	};
}
