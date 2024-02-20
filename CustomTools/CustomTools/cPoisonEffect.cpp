#include "stdafx.h"
#include "cPoisonEffect.h"

cPoisonEffect::cPoisonEffect()
{
	mbIsExample = true;
	mStatusType = 0;
	mpCombatant = nullptr;
	mCombatantPos = Vector3();
	mCombatantRot = Quaternion();
	mpPropList = nullptr;
	mTimer = 0;
	visualEffect = nullptr;
	mbIsFinished = false;
	mStatusEffectID = 0;
	damage = 0;
	mCostPerSecond = 0;
	mMoneyLost = 0;
}

cPoisonEffect::~cPoisonEffect()
{
}

void cPoisonEffect::Update(float deltaTime)
{
	IStatusEffect::Update(deltaTime);

	if (mpCombatant->mHealthPoints >= (damage*deltaTime))
	{
		uint32_t polID = 0;
		if (mpSource)
		{
			polID = mpSource->GetPoliticalID();
		}

		mpCombatant->func18h(damage * deltaTime, polID, 0, Vector3(0, 0, 0), nullptr);
		mMoneyLost += mCostPerSecond * deltaTime;

		if (abs(mMoneyLost) >= 50 && mpSource && StarManager.GetEmpire(mpSource->GetPoliticalID()))
		{
			auto empire = StarManager.GetEmpire(mpSource->GetPoliticalID());
			empire->mEmpireMoney -= mMoneyLost;
			empire->mEmpireMoney = Math::clamp(0, empire->mEmpireMoney, 999999999);
			mMoneyLost = 0;
		}
	}
	else
	{
		mbIsFinished = true;
	}
}

void cPoisonEffect::Instantiate(uint32_t ID, cCombatantPtr combatant, cCombatantPtr source)
{
	IStatusEffect::Instantiate(ID, combatant, source);
	App::Property::GetFloat(mpPropList.get(), id("statusDamage"), damage);
	if (!App::Property::GetFloat(mpPropList.get(), id("statusCost"), mCostPerSecond))
	{
		if (object_cast<Simulator::cCreatureBase>(combatant) || !mpSource || (StarManager.GetEmpire(combatant->GetPoliticalID()) == StarManager.GetEmpire(mpSource->GetPoliticalID())))
		{
			mCostPerSecond = 0;
		}
	}
}

IStatusEffect* cPoisonEffect::Clone()
{
	return new cPoisonEffect(*this);
}

void cPoisonEffect::EndEffect()
{
	if (mpSource && StarManager.GetEmpire(mpSource->GetPoliticalID()))
	{
		auto empire = StarManager.GetEmpire(mpSource->GetPoliticalID());
		empire->mEmpireMoney -= mMoneyLost;
		empire->mEmpireMoney = Math::clamp(0,empire->mEmpireMoney, 999999999);
	}
	return IStatusEffect::EndEffect();
}

// You can extend this function to return any other types your class implements.
void* cPoisonEffect::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(IStatusEffect);
	CLASS_CAST(cPoisonEffect);
	return nullptr;
}
