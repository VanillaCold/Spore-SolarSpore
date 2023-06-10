#pragma once

#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cSpaceToolData.h>
#include <Spore\Simulator\cDefaultProjectileWeapon.h>
using namespace Simulator;
class ConvertPlanet
	:public Simulator::cDefaultProjectileWeapon
{
public:
	ConvertPlanet();
	~ConvertPlanet();
	virtual bool OnHit(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int) override;
};