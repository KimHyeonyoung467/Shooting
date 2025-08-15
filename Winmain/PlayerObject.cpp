#include "pch.h"
#include "PlayerObject.h"
#include "..\ShootModule\Timer.h" 
#include <algorithm>


PlayerObject::PlayerObject(const shared_ptr<Scenes::SceneManager>& scene) : m_scene(scene)
, m_textdraw(new TextDraw()), m_battle(new ObjectHealth(this, m_scene)),
m_cLine(ColliderLiner::drawLiner(this->getTransform())), m_d2dResource(Resource::D2DResourceManager::Get())
{
	if (!isCreated) return;

	isCreated = true;

	// 오브젝트 타입을 PLAYER 로 지정 
	setObjectType(ObjectType::PLAYER);

	// Player 기본 스탯 
	getState()->setHealthPoint(1);
	getState()->setShootPoint(5);
	getState()->setMoveSpeed(5.0f);
	getState()->setAttackPoint(4);
	getState()->setDefancePoint(8);
	getState()->setShootSpeed(5.0f);
}

PlayerObject::~PlayerObject()
{
	isCreated = false;
	delete m_textdraw;
}

void PlayerObject::Initialize()
{
	getTransform()->setlocalPosition(0.0f, 0.0f);
	getTransform()->setlocalscale(15.0f, 10.0f);
	getRenderManager()->setColor(D2D1::ColorF::Aqua);

	m_textdraw->Initialize();
	m_textdraw->setText(L"생성된 총알 개수 : ");

	m_textdraw->getTextTransform()->setlocalPosition(10.0f, 10.0f);
	m_textdraw->getTextTransform()->setlocalscale(150.0f, 20.0f);

	m_cLine->Initialize();

	m_shootTimer.Reset(); 

	// 적용을 위해서 맨 아래쪽에 위치. 
	GameObject::Initialize();
}

void PlayerObject::update()
{
	auto& key = Input::InputManager<Input::KeyboardDevice>::GetInstance();
	key.update();
	PlayerMoveInput();

	BulletShoot();

	ScreenOutSideCheck();

	m_cLine->update();

	auto objects = m_scene->getcurentScene()->getGameObjects();

	// 오브젝트들을 순회하여 피격된 총알이 enemy의 총알일 때를 체크한다. 
	for (auto obj : objects)
	{
		if (obj->getObjectType() == ObjectType::BULLET && obj->getOwnerType() == ObjectType::ENEMY)
		{
			cout << endl;
			cout << endl;
			cout << enum_to_string(this->getObjectType()) << " Collider Started CallBack : " << endl;
			cout << "[DEBUG] Bullet Owner Type : " << enum_to_string(obj->getOwnerType()) << endl;
			ObjectCollider(obj);

			if (IsCollision() == true) {
				cout << "[DEBUG] Player Battle Start " << endl;
				m_battle->Battle(obj);
				IsDeath(true);

			}
		}
		if (getState()->getHealthPoint() == 0 && IsDead())
		{
			m_battle->GameOver();

			if (m_shootTimer.isElapssed(0.5f))
				m_scene->ChangeScene("End");
		}
	}

	GameObject::update();
}

void PlayerObject::Render()
{
	cout << endl;
	cout << "GameObject is Player Create" << endl;
	cout << endl;

	// text test code 
	m_textdraw->drawText(getState()->getShootPoint());

	m_cLine->Render();

	GameObject::Render();
}

void PlayerObject::PlayerMoveInput()
{
	cout << "[DEBUG] " << "PlayerMove" << endl;

	auto& key = Input::InputManager<Input::KeyboardDevice>::GetInstance();
	auto moveSpeed = getState()->getMoveSpeed();

	// player 의 이동 범위를 윈도우 창의 넓이로 지정 
	auto width = getAppResource()->getWidth();
	auto height = getAppResource()->getHeight();

	auto pos = getTransform()->getlocalPosition();

	if (key.isKeyDown('W'))
	{
		getTransform()->setlocalPosition(pos.get_xpos(), pos.get_ypos() - moveSpeed * deltaTime);
	}
	if (key.isKeyDown('S'))
	{
		getTransform()->setlocalPosition(pos.get_xpos(), pos.get_ypos() + moveSpeed * deltaTime);
	}
	if (key.isKeyDown('A'))
	{
		getTransform()->setlocalPosition(pos.get_xpos() - moveSpeed * deltaTime, pos.get_ypos());
	}
	if (key.isKeyDown('D'))
	{
		getTransform()->setlocalPosition(pos.get_xpos() + moveSpeed * deltaTime, pos.get_ypos());
	}
	m_textdraw->update();

}

void PlayerObject::BulletShoot()
{
	auto& key = Input::InputManager<Input::KeyboardDevice>::GetInstance();

	if (key.isKeyPressed('R'))
	{
		if (m_scene->getcurentScene() && getState()->getShootPoint() > 0)
		{
			isOutSide = false;
			isShoot = true;
			if (!isShoot) return;

			// 총알을 생성 
			m_bullet = BulletObject::create(this->getTransform(), m_scene);

			// 총알을 가진 Object 가 누구인지 
			m_bullet->setOwnerType(ObjectType::PLAYER);

			m_bullet->Initialize();
			m_bullet->setDirection(Vector2(1.0f, 0.0f));
			m_bullet->getState()->setShootSpeed(3.0f);

			auto shootPoint = getState()->getShootPoint();
			--shootPoint;

			getState()->setShootPoint(shootPoint);

			m_scene->getcurentScene()->addpendingObject(m_bullet); // 현재 씬에 추가


		};
	}

}

