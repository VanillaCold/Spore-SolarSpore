#include "stdafx.h"
#include "cChargeEffect.h"
#include "cSSStatusEffectManager.h"
#include "cInstantDamageEffect.h"

cChargeEffect::cChargeEffect()
{
	mMinDamage = 0;
	mMaxDamage = 0;
}


cChargeEffect::~cChargeEffect()
{
}

void cChargeEffect::Update(float deltaTime)
{
	IStatusEffect::Update(deltaTime);

	auto locomotiveOwner = object_cast<Simulator::cLocomotiveObject>(mpCombatant);
	auto sourceSpeed = locomotiveOwner->GetVelocity().Length();

	if (sourceSpeed == 0 || log2(sourceSpeed) < 0)
	{
		return;
	}

	SporeDebugPrint("%f", sourceSpeed);

	eastl::vector<cSpatialObjectPtr> collidedObjects;
	float diff = mMaxDamage - mMinDamage;
	float clampedDamage = clamp(mMinDamage, mMinDamage + (diff * log2(sourceSpeed) / 4), mMaxDamage);

	if (GameViewManager.IntersectSphere(locomotiveOwner->mPosition, locomotiveOwner->GetBoundingRadius()+4*(log2(sourceSpeed)), collidedObjects, true))
	{
		uint32_t statusID;
		App::Property::GetUInt32(mpPropList.get(), id("statusToGiveWhenRammed"), statusID);
		for each (cSpatialObjectPtr spatial in collidedObjects)
		{
			cCombatantPtr hitCombatant = object_cast<Simulator::cCombatant>(spatial);
			if (hitCombatant != mpCombatant)
			{
				auto effect = SSStatusManager.AddStatusEffect(hitCombatant, statusID, mpCombatant);
				auto damageEffect = object_cast<cInstantDamageEffect>(effect);
				if (damageEffect)
				{
					damageEffect->mDamage = clampedDamage;
				}
			}
		}
	}
}

void cChargeEffect::Instantiate(uint32_t ID, cCombatantPtr combatant, cCombatantPtr source)
{
	IStatusEffect::Instantiate(ID, combatant, source);
	App::Property::GetFloat(mpPropList.get(), id("statusMinDamage"), mMinDamage);
	App::Property::GetFloat(mpPropList.get(), id("statusMaxDamage"), mMaxDamage);

}

IStatusEffect* cChargeEffect::Clone()
{
	return new cChargeEffect(*this);
}




// You can extend this function to return any other types your class implements.
void* cChargeEffect::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(IStatusEffect);
	CLASS_CAST(cChargeEffect);
	return nullptr;
}
