#include "stdafx.h"
#include "cInstantDamageEffect.h"

cInstantDamageEffect::cInstantDamageEffect()
{
	mDamage = 0;
}


cInstantDamageEffect::~cInstantDamageEffect()
{
}

void cInstantDamageEffect::Update(float deltaTime)
{
	mbIsFinished = true;
	if (mpCombatant)
	{
		mpCombatant->TakeDamage(mDamage, mpSource->GetPoliticalID(), 0, mpCombatant->ToSpatialObject()->GetPosition(), mpSource.get());
	}
	IStatusEffect::Update(deltaTime);
}

void cInstantDamageEffect::Instantiate(uint32_t ID, cCombatantPtr combatant, cCombatantPtr source)
{
	IStatusEffect::Instantiate(ID, combatant, source);
	App::Property::GetFloat(mpPropList.get(), id("statusDamage"), mDamage);
}

IStatusEffect* cInstantDamageEffect::Clone()
{
	return new cInstantDamageEffect(*this);
}



// You can extend this function to return any other types your class implements.
void* cInstantDamageEffect::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(IStatusEffect);
	CLASS_CAST(cInstantDamageEffect);
	return nullptr;
}
