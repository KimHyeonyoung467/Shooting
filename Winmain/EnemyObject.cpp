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

	// 오브젝트 타입을 ENEMY 로 지정 
	setObjectType(ObjectType::ENEMY);

	// Enemy 기본 스탯. 총 1번  공격해야 삭제 가능 
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
	m_textdraw->setText(L"적이 생성한 총알 개수 : ");

	m_cLine->Initialize();

	GameObject::Initialize();
}

void EnemyObject::RandomCreate()
{
	if (!isCreated) isCreated = true;

	auto width = getAppResource()->getWidth();
	auto height = getAppResource()->getHeight();


	// mt19937 : 
	// 난수를 만드는 random 라이브러리 함수
	// Mersenne Twister 알고리즘을 사용한 난수 생성기	 
	// random_device : 하드웨어 혹은 OS 에서 제공하는 난수를 생성. 
	static std::mt19937 rng(std::random_device{}());
	// Mersenne Twister 알고리즘 : 
	// 4 x 10^6021개 의 난수를 생성할 수 있는 알고리즘. 

	// 최소값과 최대값을 지정하여서 고르게 분포. 
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

	// Enemy 가 화면 외부로 나갔는 지 체크. 
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

	// 오브젝트들을 순회하여 피격된 총알이 enemy의 총알일 때를 체크한다. 
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
						MarkDeathCount();		// 죽음 카운트 +1 

					IsDeath(true);			// Enemy 가 죽었기 때문에 true. 	
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
		// bullet 생성 
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

			// 화면 창에 개수를 띄우기 위한 작업 Enemy 는 화면에 있는 동안은 총알을 계속 출력. 
			if (this->getState()->getShootPoint() != 0)
				--shootPoint;

			this->getState()->setShootPoint(shootPoint);
		}
		m_shootTimer.Reset();


	}
};


