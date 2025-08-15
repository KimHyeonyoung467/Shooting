#include "pch.h"
#include "ObjectBattle.h"

ObjectBattle::ObjectBattle()
{

}

void ObjectBattle::TakeDamage(GameObject* Attacker, GameObject* defancer)
{
	// HealthPoint 
	auto defancerHealth(defancer->getState()->getHealthPoint());
		
	// AttackPoint 
	auto AttackerAttack(Attacker->getState()->getAttackPoint());

	// Attacker 가 defancer 를 공격하는 시점 
	int damage = AttackerAttack - defancerHealth;
	defancer->getState()->setHealthPoint(damage);

	cout << "[DEBUG] Battle : " << endl <<
		"[DEBUG] defancer Object Type : " << defancer->enum_to_string(defancer->getObjectType()) << endl
		<< "[DEBUG] defancer HelthPoint : " << defancer->getState()->getHealthPoint() << endl;

}

void ObjectBattle::TakeDefance(GameObject* Attacker, GameObject* defancer)
{
	// DefancePoint
	auto defancerDefance(defancer->getState()->getDefancePoint());

	// AttackPoint 
	auto attackerAttack(Attacker->getState()->getAttackPoint());

	// defancer 의 DefancePoint 감소 
	int damage = defancerDefance - attackerAttack;
	defancer->getState()->setDefancePoint(damage);
}

void ObjectBattle::Battle(GameObject* Attacker, GameObject* defancer)
{
	if (Attacker->IsCollision())
		TakeDamage(Attacker, defancer);
}

void ObjectBattle::GameOver(GameObject* obj)
{
	if (obj->getState()->getHealthPoint() != 0) return;

	// obj 가 Player 인지, Enemy 인지 2중 체크 필요하다면 추가 

}