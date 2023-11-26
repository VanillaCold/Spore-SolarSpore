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
	if (hitType == SpaceToolHit::kHitCombatant)
	{
		//auto test = (Simulator::cCombatant*)pTool->field_108.get();
		for (auto building : GetDataByCast<cBuilding>())
		{
			float distance = max(((building->mPosition - position).Length() - building->mBoundingRadius), 0.0f);
			
			if (distance <= 1.0f)
			{
				SporeDebugPrint(to_string(max(((building->mPosition - position).Length() - building->mBoundingRadius), 0.0f)).c_str());
				float localMultiplier;
				App::Property::GetFloat(pTool->mpPropList.get(), id("spaceToolBuildingDmgMultiplier"), localMultiplier);
				pTool->mDamageMultiplier *= localMultiplier;
				break;
			}
		}
	}

	bool base = cDefaultProjectileWeapon::OnHit(pTool, position, hitType,unk);
	return base;
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
