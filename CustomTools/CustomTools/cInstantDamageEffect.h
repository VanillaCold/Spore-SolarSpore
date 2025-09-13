#pragma once

#include <Spore\BasicIncludes.h>
#include "IStatusEffect.h"

#define cInstantDamageEffectPtr intrusive_ptr<cInstantDamageEffect>

class cInstantDamageEffect 
	: public IStatusEffect
{
public:
	static const uint32_t TYPE = id("cInstantDamageEffect");
	static const uint32_t STRATEGY_ID = id("InstantDamage");
	
	cInstantDamageEffect();
	~cInstantDamageEffect();


	virtual void Update(float deltaTime) override;
	virtual void Instantiate(uint32_t ID, cCombatantPtr combatant, cCombatantPtr source = nullptr) override;
	virtual IStatusEffect* Clone() override;

	float mDamage;

	void* Cast(uint32_t type) const override;
};
