#pragma once

#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cSpaceToolData.h>
#include <Spore\Simulator\cDefaultProjectileWeapon.h>
using namespace Simulator;
class SpiceDye
	:public Simulator::cToolStrategy
{
public:
	SpiceDye();
	~SpiceDye();
	bool OnHit(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int);
	virtual bool Update(cSpaceToolData* pTool, bool showErrors, const char16_t** = nullptr);
	virtual bool OnSelect(cSpaceToolData* pTool);
	//virtual bool WhileFiring(cSpaceToolData* pTool, const Vector3& aimPoint, int) override;
};