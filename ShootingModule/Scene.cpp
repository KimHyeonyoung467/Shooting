#include "pch.h"
#include "Scene.h"
#include <cmath>

namespace Scenes
{

	Scene::Scene()
		: m_type(MENU), isRespawning(false), m_enemyCreator(nullptr),
		m_text(new TextDraw()), scoreCount(0)
	{
		m_text->Initialize();
		m_text->setText(L" Score : ");

	}

	// function 을 사용해서 외부에서 등록한 함수를 사용할 수 있게 하는 함수 ㄴ
	void Scene::SetEnemyCreator(std::function<GameObject* ()> creator)
	{
		m_enemyCreator = creator;
	}

	void Scene::EnemyRespawn()
	{

		auto player = getGameObject(ObjectType::PLAYER);
		if (!player || player->IsDead() || player->getState()->getHealthPoint() == 0)
		{
			isRespawning = false;
			return;
		}

		if (!m_enemyCreator) return;

		bool enemyExists = false;
		// 현재 씬에 적이 있는지 확인
		for (const auto& obj : m_objects)
		{
			if (obj->getObjectType() == ObjectType::ENEMY && !obj->IsOutSide())
			{
				enemyExists = true;
				break;
			}

			if (obj->IsDead() && obj->IsOutSide())
			{
				isRespawning = false;
				break;
			}
		}
		if (!enemyExists && !isRespawning)
		{
			isRespawning = true;
			m_RespawnTimer.Reset();
		}

		if (isRespawning && m_RespawnTimer.isElapssed(ENEMY_RESPAWN_DELAY))
		{
			GameObject* newEnemy = m_enemyCreator();			// 팩토리 함수로 적 생성
			newEnemy->Initialize();									// 생성된 적 초기화
			addpendingObject(newEnemy);							// 씬에 추가
			isRespawning = false;									// 리스폰 상태 초기화
		}
	}


	void Scene::Initialize()
	{

	}

	void Scene::update()
	{
		m_text->getTextTransform()->setlocalPosition(-100.0f, 50.0f);
		m_text->update();

		EnemyRespawn();

		// 먼저 기존 객체들을 업데이트합니다. 이 루프 동안에는 m_objects에 아무것도 추가되지 않습니다.
		for (auto& obj : m_objects)
		{
			obj->update();
		}

		// 화면 밖으로 나간 BULLET 개수를 삭제
		removeBulletCount();

		// 업데이트 순회가 끝난 후, 보류 중인 객체들을 m_objects로 옮깁니다.
		if (!m_pendingObjects.empty())
		{
			std::move(m_pendingObjects.begin(), m_pendingObjects.end(), std::back_inserter(m_objects));
			m_pendingObjects.clear();
		}
		
		removeContainer();
			
	}

	void Scene::Render()
	{
		// vector 로 저장한 GameObject 목록의 루프를 돌려서 모든 오브젝트의 렌더 호출. 
		for (vector<GameObject*>::iterator it = m_objects.begin(); it != m_objects.end(); ++it)
		{
			(*it)->Render();

		}
		m_text->setTextColor(D2D1::ColorF::White);

		auto size = m_objects.size();

		m_text->drawText(scoreCount);
	}

	void Scene::addGameObject(GameObject* obj)
	{
		cout << endl;
		cout << endl;
		cout << endl;
		std::cout << "[Scene::addGameObject] push type=" << obj->enum_to_string(obj->getObjectType())
			<< " this=" << this << std::endl;
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		m_objects.push_back(std::move(obj));
		std::cout << " size=" << m_objects.size() << std::endl;
	}


	void Scene::addpendingObject(GameObject* obj)
	{
		m_pendingObjects.push_back(std::move(obj));
	}

	void Scene::removeGameObject(ObjectType type)
	{
		for (auto it = m_objects.begin(); it != m_objects.end();)
		{
			if ((*it)->getObjectType() == type || (*it)->IsOutSide())
			{
				(*it)->IsShoot(false);

				// 플레이어를 삭제할 때 
				if ((*it)->getObjectType() == ObjectType::PLAYER)
				{
					delete* it;
					m_objects.erase(it);
					setType(SceneType::END);
				}

				delete* it;
				m_objects.erase(it);
			}
			else ++it;
		}
	}

	void Scene::removeBulletCount()
	{
		int removedPlayerBulletCount = 0;
		int removedEnemyBulletCount = 0;

		// 2. 화면 밖으로 나간 총알(BULLET)을 찾아서 삭제하고, 소유자별로 개수를 셉니다.
		for (auto it = m_objects.begin(); it != m_objects.end();)
		{
			// 객체가 'BULLET' 타입이고 화면 밖에 나갔는지 확인합니다.
			if ((*it)->getObjectType() == ObjectType::BULLET && (*it)->IsOutSide()) {

				// 총알의 소유자를 확인하고 해당 카운트를 증가시킵니다.
				if ((*it)->getOwnerType() == ObjectType::PLAYER) {
					++removedPlayerBulletCount;
				}
				else if ((*it)->getOwnerType() == ObjectType::ENEMY) {
					++removedEnemyBulletCount;
				}

				delete* it;
				it = m_objects.erase(it);
			}
			else {
				++it;
			}
		}


		//  삭제된 총알이 있다면, 각  총알 수를 업데이트
		if (removedPlayerBulletCount > 0 || removedEnemyBulletCount > 0)
		{
			for (auto& obj : m_objects)
			{
				// 플레이어를 찾아 플레이어 총알 수만 감소
				if (obj->getObjectType() == PLAYER && removedPlayerBulletCount > 0)
				{
					auto curentCount = obj->getState()->getShootPoint();

					if (obj->getState()->getShootPoint() != 5)
					{
						obj->getState()->setShootPoint(curentCount + removedPlayerBulletCount);
					}
					// shootPoint 가 5까지 일 떄, 
					else if (obj->getState()->getShootPoint() <= 5)
					{
						obj->IsShoot(false);
					}
					else if (obj->getState()->getShootPoint() == 0 && m_RespawnTimer.isElapssed(0.5f)) // 쏠 수 있는 발사 카운트가 0이고, 0.5f 초 의 시간이 지났을 때. 
					{
						auto shootPoint = obj->getState()->getShootPoint();
						++shootPoint;
						obj->getState()->setShootPoint(shootPoint);
					}
				}
				// 적을 찾아 적 총알 수만 감소
				else if (obj->getObjectType() == ENEMY && removedEnemyBulletCount > 0)
				{
					auto curentCount = obj->getState()->getShootPoint();

					if (obj->getState()->getShootPoint() != 0)
					{
						obj->getState()->setShootPoint(curentCount + removedEnemyBulletCount);
					}
					else if (obj->getState()->getShootPoint() == 0 && m_RespawnTimer.isElapssed(0.5f)) // 쏠 수 있는 발사 카운트가 0이고, 0.5f 초 의 시간이 지났을 때. 
					{
						obj->IsShoot(false);

						auto shootPoint = obj->getState()->getShootPoint();
						++shootPoint;
						obj->getState()->setShootPoint(shootPoint);
						obj->IsShoot(true);
					}
				}

			}
		}
	}

	void Scene::removeContainer()
	{
		// 죽은 object 를 실제 컨테이너에서 삭제 
		for (std::vector<GameObject*>::iterator it = m_objects.begin(); it != m_objects.end(); /* no ++it here */)
		{
			if ((*it)->IsOutSide() && (*it)->getState()->getHealthPoint() != 0)
			{
				(*it)->IsShoot(false);
				delete* it;
				it = m_objects.erase(it);
			}
			else if ((*it)->IsDead() && ((*it)->getState()->getHealthPoint() == 0))
			{
				if ((*it)->getObjectType() == ObjectType::ENEMY)
				{
					++scoreCount;
				}

				delete* it;
				it = m_objects.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	GameObject* Scene::getGameObject(ObjectType type)
	{
		GameObject* findObject;
		for (vector<GameObject*>::iterator it = m_objects.begin(); it != m_objects.end(); ++it)
		{
			if ((*it)->getObjectType() == type)
			{
				return findObject = (*it);
			}
		}
		return nullptr;
	}

	GameObject* Scene::getGameObject(ObjectType type, ObjectType ownerType)
	{
		GameObject* findObject;
		for (vector<GameObject*>::iterator it = m_objects.begin(); it != m_objects.end(); ++it)
		{
			if ((*it)->getObjectType() == type && (*it)->getOwnerType() == ownerType)
			{
				return findObject = (*it);
			}
		}
		return nullptr;
	}

	vector<GameObject*> Scene::getGameObjects()
	{
		return m_objects;
	}

}

