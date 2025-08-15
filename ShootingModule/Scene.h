#pragma once
#include "pch.h" 
#include "GameObject.h" 
#include "Timer.h" 
#include <functional>
#include "DrawText.h" 

enum SceneType
{
	MENU,
	PLAY,
	END,
	SCENE_COUNT // 씬 개수 
};

namespace Scenes
{
	class Scene
	{
	public:
		Scene();
		virtual void Initialize();
		virtual void update();
		virtual void Render();

		// GameObject 추가 
		void addGameObject(GameObject* obj);
		void addpendingObject(GameObject* obj);

		void removeGameObject(ObjectType type);
		void removeBulletCount();
		void removeContainer(); 
		
		GameObject* getGameObject(ObjectType type);
		GameObject* getGameObject(ObjectType type, ObjectType ownerType);
		vector<GameObject*> getGameObjects(); 

		// setType 만으로 type 을 변경하여 씬 전환 가능. 
		void setType(SceneType type) { m_type = type; }
		const SceneType getType() const { return m_type; }
		
		void SetEnemyCreator(std::function<GameObject* ()> creator);
		
		void EnemyRespawn(); 

		const bool const IsRespawning() { return isRespawning; }

		const int getScore() const { return scoreCount; }
	private:
		SceneType m_type;

		// string 타입의 이름을 통해서 매치한 Scene 을 가져올 수 있게 한다. 
		vector<GameObject*> m_objects;
		// 추가할 객체들을 보관하는 임시 목록
		std::vector<GameObject*> m_pendingObjects; 

		// test code 
		Time::Timer<> m_RespawnTimer;

		bool isRespawning; 
		const float ENEMY_RESPAWN_DELAY = 3.0f;
		int scoreCount = 0; 

		TextDraw* m_text; 

		// function  
		std::function<GameObject* ()> m_enemyCreator; 

	};

}


