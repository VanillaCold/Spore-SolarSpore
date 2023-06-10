#include "stdafx.h"
#include "GroxColony.h"
#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cSpaceToolData.h>
#include <Spore\Simulator\SubSystem\TerraformingManager.h>
#include <vector>
using namespace Simulator;

GroxColony::GroxColony()
{
}

GroxColony::~GroxColony()
{
}

bool GroxColony::OnDeselect(cSpaceToolData* pTool)
{
	auto grob = StarManager.GetEmpire(StarManager.GetGrobEmpireID());

	Simulator::cEmpire::CaptureSystem(GetActiveStarRecord(), StarManager.GetGrobEmpireID());
	return false;
}

bool GroxColony::OnHit(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int)
{
	/*auto oldid = GetActiveStarRecord()->mEmpireID;
	auto system = GetActiveStarRecord(); //cStarRecordPtr(GetActiveStarRecord());
	auto oldemp = StarManager.GetEmpire(oldid);

	auto it = eastl::find(oldemp->mStars.begin(), oldemp->mStars.end(), system);
	if (it != oldemp->mStars.end())
	{
		oldemp->mStars.erase(it);
	}*/

	auto grob = StarManager.GetEmpire(StarManager.GetGrobEmpireID());

	Simulator::cEmpire::CaptureSystem(GetActiveStarRecord(), StarManager.GetGrobEmpireID());

	//auto test = StarManager.GetEmpire(StarManager.GetGrobEmpireID());
	//GetActiveStarRecord()->mEmpireID = StarManager.GetGrobEmpireID();
	RelationshipManager.ApplyRelationship(StarManager.GetGrobEmpireID(), GetPlayerEmpireID(), kRelationshipEventSpaceMissionComplete, 20.0F);
	
	//test->mStars.push_back(GetActiveStarRecord());

	return false;
}

bool GroxColony::Update(cSpaceToolData* pTool, bool showErrors, const char16_t** ppFailText)
{
	/*int tScore = 3;
	if (Simulator::GetActivePlanetRecord())
	{
		tScore = TerraformingManager.GetTScore(Simulator::GetActivePlanetRecord());
	}*/
	if (true){//((SpacePlayerData::Get()->mCurrentContext == kSpaceContextPlanet || true) && pTool->mCurrentAmmoCount > 0 && tScore == 0) {
		return true;
	}
	return false;
}
