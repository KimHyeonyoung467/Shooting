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
  
    // Enemy �� �����ϴ� ��ġ�� �����ϰ� ��ġ �ϰ� �ϴ� �Լ� 
    void RandomCreate(); 

    void Initialize() override;
    void update() override;
    void Render() override;     

    // Enemy �̵� ���� �ٸ� class �� ���� ���� ������ �������� ������? 
    void EnemyMove(); 

    // Enemy �Ѿ� �߻� �Լ� 
    // ���� Ÿ�̸� �ð��� ���� �߻�. 
    void EnemyShoot(); 

private: 
    EnemyObject(Transform* tr, const shared_ptr<Scenes::SceneManager>& scene);
    shared_ptr<Scenes::SceneManager> m_scene;

    TextDraw* m_textdraw;
    ObjectHealth* m_battle;

    Transform* m_pTransform;

    ColliderLiner* m_cLine; 


};

