#pragma once

#include <Spore\BasicIncludes.h>

#define PoisonLaserWeaponPtr intrusive_ptr<PoisonLaserWeapon>
#include <Spore\Simulator\cDefaultBeamTool.h>

class PoisonLaserWeapon
	: public Simulator::cDefaultBeamTool
{
public:

	static const uint32_t STRATEGY_ID = id("PoisonProjectileWeapon");
	static const uint32_t TYPE = id("PoisonProjectileWeapon");

	PoisonLaserWeapon();
	~PoisonLaserWeapon();

	virtual bool OnHit(Simulator::cSpaceToolData* pTool, const Vector3& position, Simulator::SpaceToolHit hitType, int) override;

	int AddRef() override;
	int Release() override;
	void* Cast(uint32_t type) const override;
};
