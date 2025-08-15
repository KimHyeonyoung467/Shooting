#pragma once
#include "pch.h" 

class ObjectStatus
{
public:
	ObjectStatus(const int& hp, const int& sp, const int& ap, const int& dp, const float& spd, const float& shootspd);

	const void setHealthPoint(const int& hp) { healthPoint = hp; }
	const void setShootPoint(const int& sp) {  shootPoint = sp; }
	const void setAttackPoint(const int& ap) { attackPoint = ap; }
	const void setDefancePoint(const int& dp) { defancePoint = dp; }
	
	const void setMoveSpeed(const float& spd) { movespeed = spd; }
	const void setShootSpeed(const float& spd) { shootspeed = spd; }

	const int getHealthPoint() { return healthPoint; }
	const int getShootPoint() { return shootPoint; }
	const int getAttackPoint() { return attackPoint; }
	const int getDefancePoint() { return defancePoint; }
	
	const float getMoveSpeed() { return movespeed; }
	const float getShootSpeed() { return shootspeed; }

private:
	int healthPoint;
	int shootPoint;
	int attackPoint;
	int defancePoint;
	float movespeed;		// 0.5 
	float shootspeed;		// 3.0
};

