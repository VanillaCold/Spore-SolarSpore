#include "stdafx.h"
#include "TerraLaser.h"

TerraLaser::TerraLaser()
{
	sTerraActive = 0;
}


TerraLaser::~TerraLaser()
{
}


void TerraLaser::OnMouseDown(cSpaceToolData* pTool, const Vector3& playerPosition)
{
	sTerraActive = Simulator::GetPlayerEmpire()->mPoliticalID;
	return cDefaultBeamTool::OnMouseDown(pTool, playerPosition);

}

bool TerraLaser::OnHit(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int unk)
{
	
	float terraformDelta;
	App::Property::GetFloat(pTool->mpPropList.get(), id("ss_terraformDelta"), terraformDelta);

	float& rTempScore = Simulator::GetActivePlanetRecord()->mTemperatureScore;
	if (rTempScore < 0.49)
	{
		rTempScore += terraformDelta / (pTool->mpBeam->mMsPerDamagePoint);
	}
	else if (rTempScore > 0.51)
	{
		rTempScore -= terraformDelta / (pTool->mpBeam->mMsPerDamagePoint);
	}


	float& rAtmoScore = Simulator::GetActivePlanetRecord()->mAtmosphereScore;
	if (rAtmoScore < 0.49)
	{
		rAtmoScore += terraformDelta / (pTool->mpBeam->mMsPerDamagePoint);
	}
	else if (rAtmoScore > 0.51)
	{
		rAtmoScore -= terraformDelta / (pTool->mpBeam->mMsPerDamagePoint);
	}
	
	
	bool bSuccess = cDefaultBeamTool::OnHit(pTool, position, hitType, unk);
	return bSuccess;
}

bool TerraLaser::WhileFiring(cSpaceToolData* pTool, const Vector3& aimPoint, int unk)
{
	bool bSuccess = cDefaultBeamTool::WhileFiring(pTool, aimPoint, unk);
	return bSuccess;
}

bool TerraLaser::OnMouseUp(cSpaceToolData* pTool)
{
	sTerraActive = 0;
	SporeDebugPrint("based");
	return cDefaultBeamTool::OnMouseUp(pTool);
}

uint32_t TerraLaser::sTerraActive = 0;

// You can extend this function to return any other types your class implements.
void* TerraLaser::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(cToolStrategy);
	CLASS_CAST(cDefaultBeamTool);
	CLASS_CAST(TerraLaser);
	return nullptr;
}
