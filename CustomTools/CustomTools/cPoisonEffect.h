#pragma once

#include <Spore\BasicIncludes.h>
#include "IStatusEffect.h"

#define cPoisonEffectPtr intrusive_ptr<cPoisonEffect>

class cPoisonEffect 
	: public IStatusEffect
{
public:
	static const uint32_t TYPE = id("cPoisonEffect");
	static const uint32_t STRATEGY_ID = id("Damage");

	cPoisonEffect();
	~cPoisonEffect();

	virtual void Update(float deltaTime) override;
	virtual void Instantiate(uint32_t ID, cCombatantPtr combatant, cCombatantPtr source = nullptr) override;
	virtual IStatusEffect* Clone() override;

	float damage;
	float mCostPerSecond;

	float mMoneyLost;


	virtual void EndEffect() override;

	void* Cast(uint32_t type) const override;
};
