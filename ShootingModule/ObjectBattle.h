#pragma once
#include "pch.h" 
#include "Scene.h" 
#include "GameObject.h"
class ObjectBattle
{
public:
	ObjectBattle();
	// 상대의 Status 를 받아서 자신의 HealthPoint Status 를 감소  
	void TakeDamage(GameObject* Attacker, GameObject* defancer);

	// 상대의 Attack Status 를 받아서 자신의 DefancePoint Status 를 감소 
	void TakeDefance(GameObject* Attacker, GameObject* defancer);

	// DefancePoint가 0이 되면 TakeDamage 를 통해서 HealthPoint 를 감소
	void Battle(GameObject* Attacker, GameObject* defancer);

	// Player 의 healthPoint 가 0이 되었을 때 호출해서 Scene 의 m_objects 안에 있는 GameObject 를 삭제 후 End Scene 으로 전환. 
	// Enemy 의 healthPoint 가 0이 되었을 때에는 Scene 의 m_objects 안에 있는 Enemy GameObject 를 삭제 후, Enemy 를 다시 생성할 수 있도록 하기. 
	void GameOver(GameObject* obj);

private:
	shared_ptr<Scenes::Scene> m_scene;
};

