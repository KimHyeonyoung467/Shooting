#pragma once
#include "..\ShootModule\Timer.h" 
#include "..\ShootModule\DrawText.h"
#include "..\ShootModule\ColliderLiner.h"
#include "..\ShootModule\GameObject.h"
#include "BulletObject.h" 
#include "ObjectHealth.h"
#include <cmath> 
class EnemyObject :
    public GameObject
{
public: 
	static EnemyObject* create(Transform* tr, const shared_ptr<Scenes::SceneManager>& scene)
	{
  
		return new EnemyObject(tr, scene);
	}
    ~EnemyObject(); 
  
    // Enemy 의 생성하는 위치를 랜덤하게 위치 하게 하는 함수 
    void RandomCreate(); 

    void Initialize() override;
    void update() override;
    void Render() override;     

    // Enemy 이동 추후 다른 class 에 뺴서 여러 구현이 가능하지 않을까? 
    void EnemyMove(); 

    // Enemy 총알 발사 함수 
    // 일정 타이머 시간에 따라서 발사. 
    void EnemyShoot(); 

private: 
    EnemyObject(Transform* tr, const shared_ptr<Scenes::SceneManager>& scene);
    shared_ptr<Scenes::SceneManager> m_scene;

    TextDraw* m_textdraw;
    ObjectHealth* m_battle;

    Transform* m_pTransform;

    ColliderLiner* m_cLine; 


};

