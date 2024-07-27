#include "stdafx.h"
#include "StrengthIncreasingLaser.h"

StrengthIncreasingLaser::StrengthIncreasingLaser()
{
}


StrengthIncreasingLaser::~StrengthIncreasingLaser()
{
}

bool StrengthIncreasingLaser::WhileFiring(Simulator::cSpaceToolData* pTool, const Vector3& aimPoint, int unk) 
{
	pTool->mMaxDamage *= 1.5; //* GameTimeManager.GetSpeed();
	pTool->mMinDamage *= 1.5; //* GameTimeManager.GetSpeed();
	pTool->mEnergyCost += 0.125;//* GameTimeManager.GetSpeed() / 16;
	SporeDebugPrint("b");
	
	return Simulator::cDefaultBeamTool::WhileFiring(pTool,aimPoint, unk);
}

bool StrengthIncreasingLaser::OnMouseUp(Simulator::cSpaceToolData* pTool)
{
	//max damage
	App::Property::GetFloat(pTool->mpPropList.get(), 0x51191D8B, pTool->mMaxDamage);
	//min damage
	App::Property::GetFloat(pTool->mpPropList.get(), 0x51191D87, pTool->mMinDamage);
	//energy usage
	App::Property::GetFloat(pTool->mpPropList.get(), 0x057B4EEC, pTool->mEnergyCost);

	return Simulator::cDefaultBeamTool::OnMouseUp(pTool);
}

bool StrengthIncreasingLaser::WhileAiming(Simulator::cSpaceToolData* pTool, const Vector3& aimPoint, bool showErrors)
{
	if (pTool->mpBeam == nullptr)
	{
		SporeDebugPrint("A");
		//max damage
		App::Property::GetFloat(pTool->mpPropList.get(), 0x51191D8B, pTool->mMaxDamage);
		//min damage
		App::Property::GetFloat(pTool->mpPropList.get(), 0x51191D87, pTool->mMinDamage);
		//energy usage
		App::Property::GetFloat(pTool->mpPropList.get(), 0x057B4EEC, pTool->mEnergyCost);
	}
	return Simulator::cDefaultBeamTool::WhileAiming(pTool, aimPoint, showErrors);
}

// For internal use, do not modify.
int StrengthIncreasingLaser::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int StrengthIncreasingLaser::Release()
{
	return DefaultRefCounted::Release();
}

// You can extend this function to return any other types your class implements.
void* StrengthIncreasingLaser::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(Simulator::cToolStrategy);
	CLASS_CAST(Simulator::cDefaultBeamTool);
	CLASS_CAST(StrengthIncreasingLaser);
	return nullptr;
}
