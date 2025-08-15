#include "pch.h"
#include "GameObject.h"
#include "Timer.h" 

bool GameObject::isCreated = false;

GameObject::GameObject()
	: m_transform(new Transform()), m_render(make_shared<RendererManager>(m_transform)),
	m_appResource(Resource::AppResourceManager::Get()), isOutSide(false), m_objType(), m_ownerType(ObjectType::NONE),
	deltaTime(0.5f), isShoot(false), isCollision(false), isDeath(false), m_direction{ 1.0f, 0.0f }, m_shootTimer(), m_bullet(nullptr),
	m_state(new ObjectStatus(1, 1, 1, 1, NULL, 0.3f)), // 기본 적으로 healthPoint = 10, p = 5.
	m_d2dResource(Resource::D2DResourceManager::Get())
{
	getState()->setShootPoint(5);
}

GameObject::~GameObject()
{
	delete m_transform;
	delete m_state;
}

void GameObject::Initialize()
{
	//Random test code 
	std::srand(static_cast<float>(std::time(nullptr))); // 난수를 얻는 seed 초기화 

	// transform 의 적용을 위한 rendererManager 의 Initialize. 
	m_render->Initialize();
}

void GameObject::update()
{
	cout << endl;
	cout << endl;
	cout << "[DEBUG] ObjectType : " << enum_to_string(getObjectType()) <<
		endl << " Object Position update" << endl;
	cout << "[DEBUG] Position : " << "X : " << m_transform->getlocalPosition().get_xpos() <<
		" Y : " << m_transform->getlocalPosition().get_ypos() << endl;
	cout << endl;
	cout << endl;

	m_render->update();


}

void GameObject::Render()
{
	// 렌더 매니저에 접근해서 사각형 그리기 함수 호출 
	m_render->Render();
}

const void GameObject::ScreenOutSideCheck()
{
	// 스크린 크기 
	auto screen_xpos(getAppResource()->getWidth());
	auto screen_ypos(getAppResource()->getHeight());

	// 게임 오브젝트의 위치 좌표 
	auto pos(this->getTransform()->getlocalPosition());
	auto scale(this->getTransform()->getlocalScale());

	const float width(scale->get_xpos() * 0.5f);
	const float height(scale->get_ypos() * 0.5f);

	const bool outside = (
		pos->get_xpos() + width < 0.0f) ||
		pos->get_xpos() - width > screen_xpos ||
		pos->get_ypos() + height < 0.0f ||
		pos->get_ypos() - height > screen_ypos;

	isOutSide = outside;

	cout << "[DEBUG] GameObject isOutSide : " << isOutSide << endl;
}

const bool GameObject::CheckObjectAABBCollision(GameObject* obj)
{
	// 오브젝트의 네 면을 구할 Rect 
	auto A_rect = getRenderManager()->getRect();
	auto B_rect = obj->getRenderManager()->getRect();

	if (A_rect.left > B_rect.right || A_rect.right < B_rect.left ||
		A_rect.top > B_rect.bottom || A_rect.bottom < B_rect.top)
	{
		auto color = obj->getRenderManager()->getColor();
		obj->getRenderManager()->setColor(color);

		IsCollisioned(false);

		return IsCollision();
	}
	IsCollisioned(true);
	return IsCollision();

}

const void GameObject::ObjectCollider(GameObject* obj)
{
	// 상대와의 충돌 여부 
	IsCollisioned(CheckObjectAABBCollision(obj));
	cout << "[DEBUG] ObjectCollider isCollision : " << IsCollision() << endl;

}

void GameObject::objectColliderupdate()
{

}

string GameObject::enum_to_string(const ObjectType& type)
{
	switch (type)
	{
	case 0: return "Player";
	case 1: return "Enemy";
	case 2: return "Bullet";
	}
	return "";

}