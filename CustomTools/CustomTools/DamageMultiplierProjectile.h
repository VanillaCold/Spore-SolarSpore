#pragma once

#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cDefaultProjectileWeapon.h>

#define DamageMultiplierProjectilePtr intrusive_ptr<DamageMultiplierProjectile>
using namespace Simulator;

class DamageMultiplierProjectile 
	: public Object
	, public DefaultRefCounted
	, public Simulator::cDefaultProjectileWeapon
{
public:

	static const uint32_t STRATEGY_ID = id("DmgMultProjectile");
	static const uint32_t TYPE = id("DamageMultiplierProjectile");
	
	DamageMultiplierProjectile();
	~DamageMultiplierProjectile();

	virtual bool OnHit(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int) override;

	int AddRef() override;
	int Release() override;
	void* Cast(uint32_t type) const override;
};
