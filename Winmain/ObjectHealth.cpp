#include "pch.h"
#include "ObjectHealth.h"
#include <cmath>

ObjectHealth::ObjectHealth(GameObject* on, shared_ptr<Scenes::SceneManager> scene) :owner(on), m_scene(scene)
{

}

ObjectHealth::~ObjectHealth()
{
}

void ObjectHealth::TakeDamage(GameObject* Attacker)
{
	// HealthPoint 
	auto defancerHealth(owner->getState()->getHealthPoint());

	// AttackPoint 
	auto AttackerAttack(Attacker->getState()->getAttackPoint());

	// Attacker �� �����ϴ� ���� 
	cout << "[DEBUG] TakeDamage : " << defancerHealth - AttackerAttack << endl <<
		"[DEBUG] healthPoint : " << getState()->getHealthPoint() << endl;

	owner->getState()->setHealthPoint(max(0, defancerHealth - AttackerAttack));

}

void ObjectHealth::TakeDefance(GameObject* Attacker)
{
	// DefancePoint
	auto defancerDefance(owner->getState()->getDefancePoint());

	// AttackPoint 
	auto attackerAttack(Attacker->getState()->getAttackPoint());

	// Attacker �� DefancePoint ���� 
	int damage = (defancerDefance - attackerAttack);
	owner->getState()->setDefancePoint(max(0, damage));

}

void ObjectHealth::Battle(GameObject* Attacker)
{
	if (Attacker->getObjectType() == ObjectType::BULLET)
		TakeDamage(Attacker);
}

void ObjectHealth::GameOver()
{
	if (owner->getState()->getHealthPoint() != 0) return;

	if (!owner->IsCreated())
	{
		owner->MarkDeath();
	}

	// ���� isCreate �� �ٽ� true �� ���� 
	if (owner->getObjectType() == ObjectType::ENEMY) {
		if (m_shootTimer.isElapssed(0.3f))
			owner->IsCreate(true);
	}

}
