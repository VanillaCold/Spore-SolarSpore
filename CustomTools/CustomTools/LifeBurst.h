#pragma once

#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cSpaceToolData.h>
#include <Spore\Simulator\cDefaultProjectileWeapon.h>
using namespace Simulator;
class LifeBurst
	:public Simulator::cDefaultProjectileWeapon
{
public:
	LifeBurst();
	~LifeBurst();
	bool OnHit(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int);
	//virtual bool WhileFiring(cSpaceToolData* pTool, const Vector3& aimPoint, int) override;
};