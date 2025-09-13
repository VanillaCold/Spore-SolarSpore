#pragma once

#include <Spore\BasicIncludes.h>
#include "IStatusEffect.h"

#define cShieldEffectPtr intrusive_ptr<cShieldEffect>

class cShieldEffect 
	: public IStatusEffect
{
public:
	static const uint32_t TYPE = id("cShieldEffect");
	static const uint32_t STRATEGY_ID = id("Shield");

	cShieldEffect();
	~cShieldEffect();

	virtual void Update(float deltaTime) override;
	virtual void Instantiate(uint32_t ID, cCombatantPtr combatant, cCombatantPtr source = nullptr) override;
	virtual IStatusEffect* Clone() override;

	float mCurrentHealth;
	float mPercentageStrength;
	uint32_t mDestructionEffect;
	float mLastCombatantHealth;

	IVisualEffectPtr mpDestroyEffect;

	virtual void EndEffect() override;

	void* Cast(uint32_t type) const override;
};
