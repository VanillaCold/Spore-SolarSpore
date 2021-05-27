#pragma once

#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cSpaceToolData.h>
#include <Spore\Simulator\cDefaultProjectileWeapon.h>
using namespace Simulator;
class StaffofDeath
	:public Simulator::cDefaultProjectileWeapon
{
public:
	StaffofDeath();
	~StaffofDeath();
	 bool OnHit(cSpaceToolData* pTool, const Vector3& position, cSpaceToolData::SpaceToolHit hitType, int);
	//virtual bool WhileFiring(cSpaceToolData* pTool, const Vector3& aimPoint, int) override;
};