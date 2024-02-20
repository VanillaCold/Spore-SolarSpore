#pragma once

#include <Spore\BasicIncludes.h>
#include "IStatusEffect.h"

#define cStunEffectPtr intrusive_ptr<cStunEffect>

class cStunEffect 
	: public IStatusEffect
{
public:
	static const uint32_t TYPE = id("cStunEffect");
	static const uint32_t STRATEGY_ID = id("Stun");
	
	cStunEffect();
	~cStunEffect();

	virtual void Update(float deltaTime) override;
	virtual void Instantiate(uint32_t ID, cCombatantPtr combatant, cCombatantPtr source = nullptr) override;
	virtual IStatusEffect* Clone() override;

	virtual void EndEffect() override;

	void* Cast(uint32_t type) const override;

private:
	cSpaceToolDataPtr mpNPCWeapon;
	cSpaceToolDataPtr mpNPCGroundWeapon;
	cSpaceToolDataPtr mpNPCNearAirWeapon;
	cSpaceToolDataPtr mpNPCMediumAirWeapon;
	cSpaceToolDataPtr mpNPCFarAirWeapon;
	cSpaceToolDataPtr mpNPCAbductWeapon;
};
