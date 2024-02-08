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

	cGameDataPtr test;
	Vector3 outPos{};
	if (GameViewManager.Raycast(position, position + Vector3(0.01, 0, 0), nullptr, test, outPos))
	{
		SporeDebugPrint("we got em");
		cCombatantPtr a = object_cast<Simulator::cCombatant>(test);
		if (a)
		{
			uint32_t id = a->ToGameData()->mID;
			SporeDebugPrint("ooooo");
			if (id)
			{
				SSStatusManager.activeStatusEffects[a] = 55;
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
