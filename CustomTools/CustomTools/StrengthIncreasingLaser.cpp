#include "stdafx.h"
#include "StrengthIncreasingLaser.h"

StrengthIncreasingLaser::StrengthIncreasingLaser()
{
}


StrengthIncreasingLaser::~StrengthIncreasingLaser()
{
}

bool StrengthIncreasingLaser::OnHit(Simulator::cSpaceToolData* pTool, const Vector3& position, Simulator::SpaceToolHit hitType, int unk)
{
	//pTool->mMaxDamage += 5; //* GameTimeManager.GetSpeed();
	//pTool->mMinDamage += 5; //* GameTimeManager.GetSpeed();

	float powConstant = 1;
	float maxDPS = 9999;
	App::Property::GetFloat(pTool->mpPropList.get(), id("SS-maxToolDPS"), maxDPS);
	App::Property::GetFloat(pTool->mpPropList.get(), id("SS-msHp-PowConstant"), powConstant);

	if (pTool->mpBeam->mMsPerDamagePoint < maxDPS)
	{
		pTool->mEnergyCost *= 20 / 19;//* GameTimeManager.GetSpeed() / 16;
	}

	if (pTool->mpBeam)
	{
		pTool->mpBeam->mMsPerDamagePoint = pow(pTool->mpBeam->mMsPerDamagePoint, powConstant);
		//Apply a max DPS.
		pTool->mpBeam->mMsPerDamagePoint = max(pTool->mpBeam->mMsPerDamagePoint, int64_t(1000 / maxDPS));
	}

	return Simulator::cDefaultBeamTool::OnHit(pTool,position, hitType, unk);
}

bool StrengthIncreasingLaser::OnMouseUp(Simulator::cSpaceToolData* pTool)
{

	return Simulator::cDefaultBeamTool::OnMouseUp(pTool);
}

bool StrengthIncreasingLaser::WhileAiming(Simulator::cSpaceToolData* pTool, const Vector3& aimPoint, bool showErrors)
{
	if (pTool->mpBeam == nullptr)
	{
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
	//CLASS_CAST(Simulator::cDefaultBeamTool);
	CLASS_CAST(StrengthIncreasingLaser);
	return nullptr;
}
