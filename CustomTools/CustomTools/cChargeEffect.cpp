#include "stdafx.h"
#include "cChargeEffect.h"
#include "cSSStatusEffectManager.h"

cChargeEffect::cChargeEffect()
{
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

	eastl::vector<cSpatialObjectPtr> collidedObjects;

	if (GameViewManager.IntersectSphere(locomotiveOwner->mPosition, locomotiveOwner->GetBoundingRadius()+4*(log2(sourceSpeed)), collidedObjects, true))
	{
		uint32_t statusID;
		App::Property::GetUInt32(mpPropList.get(), id("SS-RamInflictedStatus"), statusID);
		for each (cSpatialObjectPtr spatial in collidedObjects)
		{
			cCombatantPtr hitCombatant = object_cast<Simulator::cCombatant>(spatial);
			if (hitCombatant != mpCombatant)
			{
				SSStatusManager.AddStatusEffect(hitCombatant, statusID, mpCombatant);
			}
		}
	}
}

void cChargeEffect::Instantiate(uint32_t ID, cCombatantPtr combatant, cCombatantPtr source)
{
	return IStatusEffect::Instantiate(ID, combatant, source);
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
