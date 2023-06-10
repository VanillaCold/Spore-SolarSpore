#include "stdafx.h"
#include "ConvertPlanet.h"
#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cSpaceToolData.h>
using namespace Simulator;

ConvertPlanet::ConvertPlanet()
{
}

ConvertPlanet::~ConvertPlanet()
{
}

bool ConvertPlanet::OnHit(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int)
{
	auto oldid = GetActiveStarRecord()->mEmpireID;
	auto system = GetActiveStarRecord(); //cStarRecordPtr(GetActiveStarRecord());
	auto oldemp = StarManager.GetEmpire(oldid);

	auto it = eastl::find(oldemp->mStars.begin(), oldemp->mStars.end(), system);
	if (it != oldemp->mStars.end())
	{
		oldemp->mStars.erase(it);
	}

	auto test = GetPlayerEmpire();
	GetActiveStarRecord()->mEmpireID = GetPlayerEmpireID();
	RelationshipManager.ApplyRelationship(oldid, GetPlayerEmpireID(), kRelationshipEventSpaceBadToolUse, 20.0F);

	test->mStars.push_back(GetActiveStarRecord());
	return false;
}
