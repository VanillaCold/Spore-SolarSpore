#include "stdafx.h"
#include "PoisonProjectileWeapon.h"
#include "cSSStatusEffectManager.h"

PoisonProjectileWeapon::PoisonProjectileWeapon()
{
}


PoisonProjectileWeapon::~PoisonProjectileWeapon()
{
}

bool PoisonProjectileWeapon::OnHit(Simulator::cSpaceToolData* pTool, const Vector3& position, Simulator::SpaceToolHit hitType, int unk)
{

	vector<cSpatialObjectPtr> test;
	Vector3 outPos{};

	if (GameViewManager.IntersectSphere(position, pTool->mDamageRadius*4,test,true))
	{

		for each (cSpatialObjectPtr spatial in test)
		{
			cCombatantPtr a = object_cast<Simulator::cCombatant>(spatial);
			if (a && spatial != pTool->mpToolOwner)
			{
				uint32_t statusID;
				App::Property::GetUInt32(pTool->mpPropList.get(), id("SS-StatusEffect"), statusID);
				SSStatusManager.AddStatusEffect(a, statusID, object_cast<Simulator::cCombatant>(pTool->mpToolOwner));
			}
		}
	}

	return Simulator::cDefaultProjectileWeapon::OnHit(pTool, position, hitType, unk);
}

// For internal use, do not modify.
int PoisonProjectileWeapon::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int PoisonProjectileWeapon::Release()
{
	return DefaultRefCounted::Release();
}

// You can extend this function to return any other types your class implements.
void* PoisonProjectileWeapon::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(PoisonProjectileWeapon);
	CLASS_CAST(Simulator::cDefaultProjectileWeapon);
	return nullptr;
}
