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

	// player �� transform ���� 
	auto player_pos = m_playerTransform->getlocalPosition();
	auto player_scale = m_playerTransform->getlocalScale();
	auto bullet_scale = getTransform()->getlocalScale();

	// �÷��̾��� �߾� X ��ǥ = �÷��̾��� X ��ġ + (�÷��̾� �ʺ� / 2)
	float player_center_x = player_pos.get_xpos() + (player_scale.get_xpos() / 2.0f);
	// �÷��̾��� �߾� Y ��ǥ = �÷��̾��� Y ��ġ + (�÷��̾� ���� / 2)
	float player_center_y = player_pos.get_ypos() + (player_scale.get_ypos() / 2.0f);

	// ���� ���� ��ġ ���
	float spawn_xpos = player_center_x - (bullet_scale.get_xpos() / 2.0f);
	float spawn_ypos = player_center_y - (bullet_scale.get_ypos() / 2.0f);

	getTransform()->setlocalPosition(spawn_xpos, spawn_ypos);

	m_cLine->Initialize(); 

	GameObject::Initialize();
}

// 1.  �Ѿ� �ȿ��� ���� ������ ������ �� Ȯ�� �߰� �ϰ� ���� .
void BulletObject::update()
{
	getRenderManager()->setColor(D2D1::ColorF::Red);
	BulletMove();

	// ��ũ�� ������ ����� �� �׻� üũ �ϱ� 
	// ����ٸ� isOutSide = true �� ��ȯ 
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

	// �Ѿ� ������ �����´�. 
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
	// ������Ʈ Ÿ���� BULLET ���� ���� 
	setObjectType(ObjectType::BULLET);

}

