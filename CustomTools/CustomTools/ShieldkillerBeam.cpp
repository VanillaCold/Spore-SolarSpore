#include "stdafx.h"
#include "ShieldkillerBeam.h"

ShieldkillerBeam::ShieldkillerBeam()
{
	playerDamage = 0;
}


ShieldkillerBeam::~ShieldkillerBeam()
{
}

bool ShieldkillerBeam::OnHit(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int target)
{
	if (auto player = object_cast<Simulator::cGameDataUFO>(pTool->mpToolTarget))
	{
		if (player == Simulator::GetPlayerUFO())
		{
			auto playerCombatant = object_cast<Simulator::cCombatant>(player);
			if (playerCombatant->field_80 == true)
			{
				playerDamage += pTool->mMaxDamage;
				if (playerDamage > 300)
				{
					playerDamage = 0;
					playerCombatant->field_80 = false;
				}
			}
		}
	}
	else
	{
	}
	return cDefaultBeamTool::OnHit(pTool,position,hitType,target);
}

// For internal use, do not modify.
int ShieldkillerBeam::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int ShieldkillerBeam::Release()
{
	return DefaultRefCounted::Release();
}

// You can extend this function to return any other types your class implements.
void* ShieldkillerBeam::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(ShieldkillerBeam);
	return nullptr;
}
