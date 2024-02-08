#pragma once

#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cDefaultProjectileWeapon.h>

#define PoisonProjectileWeaponPtr intrusive_ptr<PoisonProjectileWeapon>

class PoisonProjectileWeapon 
	: public Simulator::cDefaultProjectileWeapon
{
public:

	static const uint32_t STRATEGY_ID = id("PoisonProjectileWeapon");
	static const uint32_t TYPE = id("PoisonProjectileWeapon");
	
	PoisonProjectileWeapon();
	~PoisonProjectileWeapon();
	
	virtual bool OnHit(Simulator::cSpaceToolData* pTool, const Vector3& position, Simulator::SpaceToolHit hitType, int) override;

	int AddRef() override;
	int Release() override;
	void* Cast(uint32_t type) const override;

	};
