#pragma once

#include <Spore\BasicIncludes.h>
#include "IStatusEffect.h"

#define cChargeEffectPtr intrusive_ptr<cChargeEffect>

class cChargeEffect 
	: public IStatusEffect
	, public DefaultRefCounted
{
public:
	static const uint32_t TYPE = id("cChargeEffect");
	static const uint32_t STRATEGY_ID = id("Charge");
	
	cChargeEffect();
	~cChargeEffect();


	virtual void Update(float deltaTime) override;
	virtual void Instantiate(uint32_t ID, cCombatantPtr combatant, cCombatantPtr source = nullptr) override;
	virtual IStatusEffect* Clone() override;

	float mMinDamage;
	float mMaxDamage;

	void* Cast(uint32_t type) const override;
};
