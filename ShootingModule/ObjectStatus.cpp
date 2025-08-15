#include "pch.h"
#include "ObjectStatus.h"

ObjectStatus::ObjectStatus(const int& hp, const int& sp, const int& ap, const int& dp, const float& spd, const float& shootspd)
	: healthPoint(hp), shootPoint(sp), attackPoint(ap), defancePoint(dp), movespeed(spd), shootspeed(shootspd)
{

}
