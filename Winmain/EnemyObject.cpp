#include "pch.h"
#include "EnemyObject.h"
#include <algorithm>
#include <cmath>
#include <random>

EnemyObject::~EnemyObject()
{
	isCreated = false;
	isDeath = false;
	delete m_textdraw;
}

EnemyObject::EnemyObject(Transform* tr, const shared_ptr<Scenes::SceneManager>& scene)
	: m_scene(scene), m_textdraw(new TextDraw()), m_battle(new ObjectHealth(this, m_scene)),
	m_pTransform(tr), m_cLine(ColliderLiner::drawLiner(this->getTransform()))
{

	// ������Ʈ Ÿ���� ENEMY �� ���� 
	setObjectType(ObjectType::ENEMY);

	// Enemy �⺻ ����. �� 1��  �����ؾ� ���� ���� 
	getState()->setHealthPoint(1);
	getState()->setShootPoint(5);
	getState()->setDefancePoint(6);
	getState()->setAttackPoint(3);
	getState()->setMoveSpeed(3.0f);
	getState()->setShootSpeed(0.5f);

	isCreated = true;
}

void EnemyObject::Initialize()
{
	//srand(static_cast<unsigned int>(time(nullptr)));
	RandomCreate();

	getTransform()->setlocalscale(20.0f, 10.0f);

	getRenderManager()->setColor(D2D1::ColorF::Black);

	m_textdraw->Initialize();
	m_textdraw->setText(L"���� ������ �Ѿ� ���� : ");

	m_cLine->Initialize();

	GameObject::Initialize();
}

void EnemyObject::RandomCreate()
{
	if (!isCreated) isCreated = true;

	auto width = getAppResource()->getWidth();
	auto height = getAppResource()->getHeight();


	// mt19937 : 
	// ������ ����� random ���̺귯�� �Լ�
	// Mersenne Twister �˰����� ����� ���� ������	 
	// random_device : �ϵ���� Ȥ�� OS ���� �����ϴ� ������ ����. 
	static std::mt19937 rng(std::random_device{}());
	// Mersenne Twister �˰��� : 
	// 4 x 10^6021�� �� ������ ������ �� �ִ� �˰���. 

	// �ּҰ��� �ִ밪�� �����Ͽ��� ���� ����. 
	std::uniform_real_distribution<float> distY(0.0f, height - 10.0f);

	float r_ypos = distY(rng);

	getTransform()->setlocalPosition(width - 60.0f, r_ypos);

	cout << "[ENEMY] Random Position : " << endl <<
		"x : " << getTransform()->getlocalPosition().get_xpos() << endl <<
		"y : " << getTransform()->getlocalPosition().get_ypos() << endl;

}
void EnemyObject::update()
{
	if (m_shootTimer.isElapssed(0.5f))
	{
		getRenderManager()->setColor(D2D1::ColorF::SaddleBrown);
	}

	// Enemy �� ȭ�� �ܺη� ������ �� üũ. 
	this->ScreenOutSideCheck();


	if (IsOutSide())
	{
		MarkDeath();
	}

	if (m_shootTimer.isElapssed(1.0f))
		EnemyShoot();

	m_textdraw->getTextTransform()->setlocalPosition(-50.0f, 10.0f);
	m_textdraw->update();

	EnemyMove();
	m_cLine->update();

	auto objects = m_scene->getcurentScene()->getGameObjects();

	// ������Ʈ���� ��ȸ�Ͽ� �ǰݵ� �Ѿ��� enemy�� �Ѿ��� ���� üũ�Ѵ�. 
	for (auto obj : objects)
	{
		if (obj->getObjectType() == ObjectType::BULLET && obj->getOwnerType() == ObjectType::PLAYER)
		{
			cout << endl;
			cout << endl;
			cout << enum_to_string(this->getObjectType()) << " Collider Started CallBack : " << endl;
			cout << "[DEBUG] Bullet Owner Type : " << enum_to_string(obj->getOwnerType()) << endl;

			ObjectCollider(obj);

			if (IsCollision() == true) {
				cout << "[DEBUG] Enemy Battle Start " << endl;
				m_battle->Battle(obj);

				if (getState()->getHealthPoint() == 0)
				{
					if (getState()->getHealthPoint() == 0 && !IsDead())
						MarkDeathCount();		// ���� ī��Ʈ +1 

					IsDeath(true);			// Enemy �� �׾��� ������ true. 	
				}
			}
		}
	}
	if (IsDead())
	{
		m_battle->GameOver();
	}

	GameObject::update();


}

void EnemyObject::Render()
{
	cout << endl;
	cout << "GameObject is Enemy Create" << endl;
	cout << endl;

	m_textdraw->setTextColor(D2D1::ColorF::White);
	m_textdraw->drawText(this->getState()->getShootPoint());
	m_cLine->Render();
	GameObject::Render();
}

void EnemyObject::EnemyMove()
{
	auto pos = getTransform();
	auto movespeed = getState()->getMoveSpeed();

	pos->setlocalPosition(pos->getlocalPosition().get_xpos()
		- movespeed * deltaTime, pos->getlocalPosition().get_ypos());

};

void EnemyObject::EnemyShoot()
{

	if (m_scene->getcurentScene() && this->getState()->getShootPoint() > 0 && m_shootTimer.isElapssed(0.5f))
	{

		isShoot = true;
		if (!isShoot) return;
		// bullet ���� 
		m_bullet = BulletObject::create(this->getTransform(), m_scene);
		m_bullet->Initialize();
		m_bullet->setOwnerType(ObjectType::ENEMY);

		if (isShoot)
		{
			auto p_tr = m_pTransform->getlocalPosition();

			auto bullet_tr = m_bullet->getTransform()->getlocalPosition();
			auto dir = p_tr - bullet_tr;
			dir.Normalized();

			m_bullet->setDirection(dir * 0.2f);
			m_bullet->getState()->setShootSpeed(0.2f);

			m_scene->getcurentScene()->addpendingObject(m_bullet);

			// Shoot Count 
			auto shootPoint = this->getState()->getShootPoint();

			// ȭ�� â�� ������ ���� ���� �۾� Enemy �� ȭ�鿡 �ִ� ������ �Ѿ��� ��� ���. 
			if (this->getState()->getShootPoint() != 0)
				--shootPoint;

			this->getState()->setShootPoint(shootPoint);
		}
		m_shootTimer.Reset();


	}
};


