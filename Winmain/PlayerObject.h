#pragma once
#include "..\ShootModule\KeyboardInputManager.h" 
#include "..\ShootModule\ColliderLiner.h" 
#include "..\ShootModule\SceneManager.h" 
#include "..\ShootModule\GameObject.h"
#include "..\ShootModule\DrawText.h"
#include "BulletObject.h" 
#include "ObjectHealth.h"
class PlayerObject :
	public GameObject
{
public:
	static PlayerObject* create(const shared_ptr<Scenes::SceneManager>& scene)
	{
		isCreated = true; 
		return new PlayerObject(scene);
	}
	~PlayerObject(); 

	// update override - 키보드 함수를 사용해 move .  transform 의 x, y 값을 수정해서 matrix를 업데이트 하기. 
	// Render .. 색깔 변환  등등.. 
	void Initialize() override;
	void update() override;
	void Render() override;

	// Input  
	void PlayerMoveInput();
	void BulletShoot();

private:
	PlayerObject(const shared_ptr<Scenes::SceneManager>& scene);
	shared_ptr<Scenes::SceneManager> m_scene;

	//BulletObject* m_bullet;
	TextDraw* m_textdraw;
	ObjectHealth* m_battle;
	ColliderLiner* m_cLine;

	shared_ptr<Resource::D2DResourceManager> m_d2dResource;
};

