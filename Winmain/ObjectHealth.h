#pragma once
#include "pch.h" 
#include "..\ShootModule\GameObject.h"
#include "..\ShootModule\SceneManager.h"

class ObjectHealth : public GameObject
{
public: 
	ObjectHealth(GameObject* on, shared_ptr<Scenes::SceneManager> scene);
	~ObjectHealth(); 

	// 상대의 Status 를 받아서 자신의 HealthPoint Status 를 감소  
	void TakeDamage(GameObject* Attacker);

	// 상대의 Attack Status 를 받아서 자신의 DefancePoint Status 를 감소 
	void TakeDefance(GameObject* Attacker);

	// DefancePoint가 0이 되면 TakeDamage 를 통해서 HealthPoint 를 감소
	void Battle(GameObject* Attacker);

	// Player 의 healthPoint 가 0이 되었을 때 호출해서 Scene 의 m_objects 안에 있는 GameObject 를 삭제 후 End Scene 으로 전환. 
	void GameOver();


private: 
	GameObject* owner; 
	shared_ptr<Scenes::SceneManager> m_scene;
};

