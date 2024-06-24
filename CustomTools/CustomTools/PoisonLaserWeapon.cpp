#include "stdafx.h"
#include "PoisonLaserWeapon.h"
#include "cSSStatusEffectManager.h"

PoisonLaserWeapon::PoisonLaserWeapon()
{
}


PoisonLaserWeapon::~PoisonLaserWeapon()
{
}

bool PoisonLaserWeapon::OnHit(Simulator::cSpaceToolData* pTool, const Vector3& position, Simulator::SpaceToolHit hitType, int unk)
{

	vector<cSpatialObjectPtr> test;
	Vector3 outPos{};

	if (GameViewManager.IntersectSphere(position, pTool->mDamageRadius * 4, test, true))
	{
		uint32_t* statusIDs;
		size_t size;
		App::Property::GetArrayUInt32(pTool->mpPropList.get(), id("SS-StatusEffect"), size, statusIDs);
		for each (cSpatialObjectPtr spatial in test)
		{
			cCombatantPtr a = object_cast<Simulator::cCombatant>(spatial);
			if (a && spatial != pTool->mpToolOwner)
			{

				for (int i = 0; i < size; i++)
				{
					SSStatusManager.AddStatusEffect(a, statusIDs[i], object_cast<Simulator::cCombatant>(pTool->mpToolOwner));
				}
			}
		}
	}

	uint32_t otherStatusID;
	if (App::Property::GetUInt32(pTool->mpPropList.get(), id("SS-ToolOwnerStatus"), otherStatusID))
	{
		if (pTool->mpToolOwner)
		{
			SSStatusManager.AddStatusEffect(object_cast<Simulator::cCombatant>(pTool->mpToolOwner), otherStatusID);
		}
	}

	return Simulator::cDefaultBeamTool::OnHit(pTool, position, hitType, unk);
}

// For internal use, do not modify.
int PoisonLaserWeapon::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int PoisonLaserWeapon::Release()
{
	return DefaultRefCounted::Release();
}

// You can extend this function to return any other types your class implements.
void* PoisonLaserWeapon::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(Simulator::cDefaultBeamTool);
	CLASS_CAST(PoisonLaserWeapon);
	return nullptr;
}
