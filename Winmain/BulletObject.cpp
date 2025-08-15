#include "pch.h"
#include "BulletObject.h"


BulletObject::~BulletObject()
{
	isCreated = false;
}

void BulletObject::Initialize()
{
	cout << endl;
	cout << "Bullet Create" << endl;
	cout << endl;

	getTransform()->setlocalscale(4.0f, 15.0f);
	getRenderManager()->setColor(D2D1::ColorF::Black);

	// player 의 transform 정보 
	auto player_pos = m_playerTransform->getlocalPosition();
	auto player_scale = m_playerTransform->getlocalScale();
	auto bullet_scale = getTransform()->getlocalScale();

	// 플레이어의 중앙 X 좌표 = 플레이어의 X 위치 + (플레이어 너비 / 2)
	float player_center_x = player_pos.get_xpos() + (player_scale.get_xpos() / 2.0f);
	// 플레이어의 중앙 Y 좌표 = 플레이어의 Y 위치 + (플레이어 높이 / 2)
	float player_center_y = player_pos.get_ypos() + (player_scale.get_ypos() / 2.0f);

	// 최종 스폰 위치 계산
	float spawn_xpos = player_center_x - (bullet_scale.get_xpos() / 2.0f);
	float spawn_ypos = player_center_y - (bullet_scale.get_ypos() / 2.0f);

	getTransform()->setlocalPosition(spawn_xpos, spawn_ypos);

	m_cLine->Initialize(); 

	GameObject::Initialize();
}

// 1.  총알 안에서 월드 밖으로 나갔는 지 확인 추가 하고 삭제 .
void BulletObject::update()
{
	getRenderManager()->setColor(D2D1::ColorF::Red);
	BulletMove();

	// 스크린 영역을 벗어났는 지 항상 체크 하기 
	// 벗어났다면 isOutSide = true 로 변환 
	ScreenOutSideCheck();

	m_cLine->update();
	GameObject::update();
}

void BulletObject::Render()
{

	m_cLine->Render();

	GameObject::Render();
}

void BulletObject::BulletMove()
{
	auto pos = getTransform()->getlocalPosition();
	auto shootSpeed = getState()->getShootSpeed();

	// 총알 방향을 가져온다. 
	Vector2 dir = getDirection();
	float rad = getTransform()->getRotation(); 

	float dx = dir.get_xpos() * shootSpeed * deltaTime;
	float dy = dir.get_ypos() * shootSpeed * deltaTime;
		
	getTransform()->setlocalPosition(
		pos.get_xpos() + dx,
		pos.get_ypos() + dy);

}


void BulletObject::Curve(float anglesec, float dampingPerSec /*= 0.0f*/)
{

}

BulletObject::BulletObject(Transform* tr, const shared_ptr<Scenes::SceneManager>& scene)
	: m_playerTransform(tr), m_scene(scene), m_cLine(ColliderLiner::drawLiner(this->getTransform()))
{
	if (!isCreated) return;

	isCreated = true;
	// 오브젝트 타입을 BULLET 으로 지정 
	setObjectType(ObjectType::BULLET);

}

