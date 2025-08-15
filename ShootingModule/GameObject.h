#pragma once
#include "AppResourceManager.h"
#include "D2DResourceManager.h"
#include "RendererManager.h"
#include "Transform.h" 
#include "Timer.h" 
#include "ObjectStatus.h"

class BulletObject; 

enum ObjectType
{
	PLAYER,
	ENEMY,
	BULLET,
	NONE
};

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Initialize();
	virtual void update();
	virtual void Render();

	void setTransform(Transform* tr) { m_transform = tr; };
	Transform* getTransform() { return m_transform; }

	// 월드 스크린에서 나갔는 지 체크하는 함수 
	const void ScreenOutSideCheck();

	// 체크 설정 
	bool IsOutSide() { return isOutSide; }
	const bool IsCreated() const { return isCreated; }
	void IsCreate(const bool& create) { isCreated = create; }
	const bool IsShooting() const { return isShoot; }
	void IsShoot(const bool& shoot) { isShoot = shoot; }
	const bool IsCollision() const { return isCollision; }
	void IsCollisioned(const bool& collision) { isCollision = collision; }
	const bool IsDead() const { return isDeath; }
	void IsDeath(const bool& death) { isDeath = death; }
	void IsSpawnDelayed(const bool& delay) { isRespawnDelay = delay; }
	const bool IsRespawnDelay() { return isRespawnDelay; }

	void MarkDeath() { isDeath = true; }

	// 총알 개수 가져오기 
	virtual int getBulletCount() const { return 0; }

	// 총알 가져오기 
	virtual GameObject* getBullet() { return nullptr; }
	static string enum_to_string(const ObjectType& type);

	// object 타입 세팅 
	ObjectType getObjectType() { return m_objType; }
	void setObjectType(const ObjectType& type) { m_objType = type; }

	// 죽음 카운트 세팅 
	int getDeathCount() { return deathCount; }
	void MarkDeathCount() { ++deathCount; }

	// owner 타입 세팅 
	ObjectType getOwnerType() { return m_ownerType; }
	void setOwnerType(const ObjectType& type) { m_ownerType = type; }

	// 충돌 체크는 이 함수를 사용할 것. 
	const void ObjectCollider(GameObject* obj);
	void objectColliderupdate(); 

	// 방향 설정 
	 Vector2 getDirection() const { return m_direction; }
	void setDirection(const Vector2& dir) { m_direction = dir; }
	void setDirection(const float& dir) { direction = dir; }

	// state 설정할 수 있는 setter 는 getState 안에서 사용. 
	ObjectStatus* getState() const { return m_state; }	
	
	Resource::AppResourceManager* getAppResource() { return m_appResource.get(); }
	Resource::D2DResourceManager* getd2DResource() { return m_d2dResource.get(); };
	shared_ptr<RendererManager> getRenderManager() { return m_render; }

protected: 	
	float deltaTime; 
	int deathCount;  // 오브젝트가 죽었을 때의 카운트 

	bool isShoot;		   
	bool isOutSide;
	bool isCollision; 
	bool isDeath;
	bool isRespawnDelay; 
	static bool isCreated; 

	//int m_direction = +1.0f;	  // 발사 방향
	Vector2 m_direction; 
	float direction = +1.0f; 

	// 총알을 쏘는 타이밍 타이머 
	Time::Timer<> m_shootTimer;

	GameObject* m_bullet;
		
private: 	
	Transform* m_transform; 
	shared_ptr<RendererManager> m_render;

	ObjectType m_objType; 
	ObjectType m_ownerType; 
	ObjectStatus* m_state; 

	shared_ptr<Resource::AppResourceManager> m_appResource;
	shared_ptr< Resource::D2DResourceManager> m_d2dResource;

	// 달리 수정할 수 없도록 private 선언 
	const bool CheckObjectAABBCollision(GameObject* obj);
};

inline float clampf(float value, float minVal, float maxVal) {
	if (value < minVal)  return minVal;
	if (value > maxVal) return maxVal;

	return value;
}

