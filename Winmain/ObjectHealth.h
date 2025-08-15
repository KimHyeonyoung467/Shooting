#pragma once
#include "pch.h" 
#include "..\ShootModule\GameObject.h"
#include "..\ShootModule\SceneManager.h"

class ObjectHealth : public GameObject
{
public: 
	ObjectHealth(GameObject* on, shared_ptr<Scenes::SceneManager> scene);
	~ObjectHealth(); 

	// ����� Status �� �޾Ƽ� �ڽ��� HealthPoint Status �� ����  
	void TakeDamage(GameObject* Attacker);

	// ����� Attack Status �� �޾Ƽ� �ڽ��� DefancePoint Status �� ���� 
	void TakeDefance(GameObject* Attacker);

	// DefancePoint�� 0�� �Ǹ� TakeDamage �� ���ؼ� HealthPoint �� ����
	void Battle(GameObject* Attacker);

	// Player �� healthPoint �� 0�� �Ǿ��� �� ȣ���ؼ� Scene �� m_objects �ȿ� �ִ� GameObject �� ���� �� End Scene ���� ��ȯ. 
	void GameOver();


private: 
	GameObject* owner; 
	shared_ptr<Scenes::SceneManager> m_scene;
};

