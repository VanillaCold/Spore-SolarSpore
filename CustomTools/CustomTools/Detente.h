#pragma once

#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cSpaceToolData.h>
#include <Spore\Simulator\cDefaultProjectileWeapon.h>
using namespace Simulator;
class Detente
	:public Simulator::cDefaultProjectileWeapon
{
public:
	Detente();
	~Detente();
	virtual bool OnHit(cSpaceToolData* pTool, const Vector3& position, cSpaceToolData::SpaceToolHit hitType, int) override;
};