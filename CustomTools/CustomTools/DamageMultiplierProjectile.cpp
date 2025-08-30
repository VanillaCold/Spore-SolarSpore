#include "stdafx.h"
#include "DamageMultiplierProjectile.h"

DamageMultiplierProjectile::DamageMultiplierProjectile()
{
}


DamageMultiplierProjectile::~DamageMultiplierProjectile()
{
}

bool DamageMultiplierProjectile::OnHit(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int unk)
{

	pTool->mDamageMultiplier = 1;
	// Get the combatant
	eastl::vector <cSpatialObjectPtr> combatantsCaught;
	bool objFound = GameViewManager.IntersectSphere(position, pTool->mDamageRadius * 4, combatantsCaught, true);


	if (objFound)
	{

		uint32_t propertyID = id("spaceToolDefaultDmgMultiplier");
		for (auto targetObject : combatantsCaught)
		{
			if (object_cast<Simulator::cBuilding>(targetObject))
			{
				SporeDebugPrint("building");
				propertyID = id("spaceToolBuildingDmgMultiplier");
				break;
			}

			else if (object_cast<Simulator::cGameDataUFO>(targetObject))
			{
				SporeDebugPrint("ufo");
				propertyID = id("spaceToolUFODmgMultiplier");
				break;
			}

			else if (object_cast<Simulator::cVehicle>(targetObject))
			{
				SporeDebugPrint("vehicle");
				propertyID = id("spaceToolVehicleDmgMultiplier");
				break;
			}

		}

		float localMultiplier;
		if (App::Property::GetFloat(pTool->mpPropList.get(), propertyID, localMultiplier))
		{
			pTool->mDamageMultiplier = localMultiplier;
		}

		bool base = cDefaultProjectileWeapon::OnHit(pTool, position, hitType, unk);
		return base;
	}
}

// For internal use, do not modify.
int DamageMultiplierProjectile::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int DamageMultiplierProjectile::Release()
{
	return DefaultRefCounted::Release();
}

// You can extend this function to return any other types your class implements.
void* DamageMultiplierProjectile::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(DamageMultiplierProjectile);
	return nullptr;
}
