#pragma once
#include <cstdlib>
#include "..//ShootModule//Application.h"
#include "..//ShootModule//SceneManager.h"
#include "..//ShootModule//GameObject.h" 

#include "PlayerObject.h" 
#include "EnemyObject.h" 

class DemoGameApp : public Application 
{
public: 
	DemoGameApp(); 
	void Initialize() override; 
	void update()	 override;
	void Render()	 override;

private: 
	shared_ptr<Scenes::SceneManager> m_scene;

	// GameObject µî·Ï 
	GameObject* m_player;
};

