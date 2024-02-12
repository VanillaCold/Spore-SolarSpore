#include "stdafx.h"
#include "cPoisonEffect.h"

cPoisonEffect::cPoisonEffect()
{
	damage = 0;
}

cPoisonEffect::~cPoisonEffect()
{
}

void cPoisonEffect::Update(float deltaTime)
{
	IStatusEffect::Update(deltaTime);

	if (mpCombatant->mHealthPoints >= (damage*deltaTime))
	{
		mpCombatant->func18h(damage * deltaTime, 0, 0, Vector3(0, 0, 0), nullptr);
	}
}

void cPoisonEffect::Instantiate(uint32_t ID, cCombatantPtr combatant)
{
	IStatusEffect::Instantiate(ID, combatant);
	App::Property::GetFloat(mpPropList.get(), id("statusDamage"), damage);
}

IStatusEffect* cPoisonEffect::Clone()
{
	return new cPoisonEffect();
}

// You can extend this function to return any other types your class implements.
void* cPoisonEffect::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(IStatusEffect);
	CLASS_CAST(cPoisonEffect);
	return nullptr;
}
