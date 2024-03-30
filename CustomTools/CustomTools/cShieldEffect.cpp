#include "stdafx.h"
#include "cShieldEffect.h"

cShieldEffect::cShieldEffect()// : IStatusEffect()
{
	mCurrentHealth = 0;
	mPercentageStrength = 0;
	mDestructionEffect = 0;
	mLastCombatantHealth = 0;
	mpDestroyEffect = nullptr;
}


cShieldEffect::~cShieldEffect()
{
}

void cShieldEffect::Update(float deltaTime)
{
	IStatusEffect::Update(deltaTime);

	if (Simulator::GetCurrentContext() != Simulator::SpaceContext::Planet)
	{
		mbIsFinished = true;
	}

	if (mCurrentHealth <= 0)
	{
		mbIsFinished = true;
		EffectsManager.CreateVisualEffect(mDestructionEffect, 0, mpDestroyEffect);
		mpDestroyEffect->SetRigidTransform(mpDestroyEffect->GetRigidTransform().SetOffset(mCombatantPos));
		mpDestroyEffect->SetSourceTransform(mpDestroyEffect->GetSourceTransform().SetOffset(mCombatantPos));
		mpDestroyEffect->Start();
	}
	else
	{
		float healthDiff = mLastCombatantHealth - mpCombatant->mHealthPoints;
		if (healthDiff > 0 && !mpCombatant->ToGameData()->mbIsDestroyed)
		{
			mCurrentHealth -= healthDiff;
			float increase = healthDiff * mPercentageStrength;
			mpCombatant->mHealthPoints += increase;
		}
	}

	mLastCombatantHealth = mpCombatant->mHealthPoints;
}

void cShieldEffect::Instantiate(uint32_t ID, cCombatantPtr combatant, cCombatantPtr source)
{
	IStatusEffect::Instantiate(ID, combatant, source);

	App::Property::GetFloat(mpPropList.get(), id("shieldHealth"), mCurrentHealth);
	App::Property::GetFloat(mpPropList.get(), id("shieldStrength"), mPercentageStrength);
	App::Property::GetUInt32(mpPropList.get(), id("shieldDestroyEffect"), mDestructionEffect);

	mLastCombatantHealth = combatant->mHealthPoints;
}

IStatusEffect* cShieldEffect::Clone()
{
	return new cShieldEffect(*this);
}

void cShieldEffect::EndEffect()
{
	if (mpDestroyEffect)
	{
		mpDestroyEffect->Stop(false);
	}
	if (mpToolObject)
	{
		ToolManager.GetStrategy(mpToolObject->mStrategy)->OnDeselect(mpToolObject.get());
		mpToolObject->mRechargeTimer.Stop();
		mpToolObject->mRechargeTimer.Start();
	}
	return IStatusEffect::EndEffect();
}

// You can extend this function to return any other types your class implements.
void* cShieldEffect::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(IStatusEffect);
	CLASS_CAST(cShieldEffect);
	return nullptr;
}
