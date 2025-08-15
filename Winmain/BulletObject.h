#pragma once
#include "..\ShootModule\GameObject.h"
#include "..\ShootModule\SceneManager.h" 
#include "..\ShootModule\ColliderLiner.h" 

class BulletObject :
	public GameObject
{
public:
	static BulletObject*create(Transform* tr, const shared_ptr<Scenes::SceneManager>& scene)
	{
		isCreated = true; 
		return new BulletObject(tr, scene); 
	};
	~BulletObject(); 

	void Initialize() override;
	void update() override;
	void Render() override;

	void BulletMove();

	void Curve(float anglesec, float dampingPerSec = 0.0f); 

private:
	BulletObject(Transform* tr, const shared_ptr<Scenes::SceneManager>& scene);
	const Transform* m_playerTransform;
	
	ColliderLiner* m_cLine; 
	shared_ptr<Scenes::SceneManager> m_scene;

	bool isCurves = false; 
	float radian = 0.0f; 
	float damPerSec = 0.0f; 
};
