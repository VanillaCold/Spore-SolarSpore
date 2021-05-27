#include "stdafx.h"
#include "Detente.h"
#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cSpaceToolData.h>
using namespace Simulator;

Detente::Detente()
{
}

Detente::~Detente()
{
}

bool Detente::OnHit(cSpaceToolData* pTool, const Vector3& position, cSpaceToolData::SpaceToolHit hitType, int)
{
	auto oldid = GetActiveStarRecord()->mEmpireID;
	auto system = GetActiveStarRecord(); //cStarRecordPtr(GetActiveStarRecord());
	auto oldemp = StarManager.GetEmpire(oldid);
	auto otheremp = GetPlayerEmpire();

	if (oldemp != StarManager.GetEmpire(StarManager.GetGrobEmpireID()))
	{
		auto it = eastl::find(oldemp->mEnemies.begin(), oldemp->mEnemies.end(), GetPlayerEmpire());
		if (it != oldemp->mEnemies.end())
		{
			oldemp->mEnemies.erase(it);
		}

		auto it2 = eastl::find(otheremp->mEnemies.begin(), otheremp->mEnemies.end(), oldemp);
		if (it2 != otheremp->mEnemies.end())
		{
			otheremp->mEnemies.erase(it2);
		}


		//auto test = GetPlayerEmpire();
		//GetActiveStarRecord()->mEmpireID = GetPlayerEmpireID();
		//RelationshipManager.ApplyRelationship(oldid, GetPlayerEmpireID(), RelationshipEvents::kRelationshipEventSpaceTerraformImproved, 5.0F);
		//oldemp->
		RelationshipManager.ApplyRelationship(oldid, GetPlayerEmpireID(), RelationshipEvents::kRelationshipEventSpaceBadToolUse, -10.0F);
		RelationshipManager.ApplyRelationship(oldid, GetPlayerEmpireID(), RelationshipEvents::kRelationshipEventSpaceBreakAlliance, -10.0F);
		RelationshipManager.ApplyRelationship(oldid, GetPlayerEmpireID(), RelationshipEvents::kRelationshipEventDeclaredWar, -10.0F);
		RelationshipManager.ApplyRelationship(oldid, GetPlayerEmpireID(), RelationshipEvents::kRelationshipEventSpaceTerraformWorsened, -10.0F);
		RelationshipManager.ApplyRelationship(oldid, GetPlayerEmpireID(), RelationshipEvents::kRelationshipEventSpaceAbductCitizen, -10.0F);
		RelationshipManager.ApplyRelationship(oldid, GetPlayerEmpireID(), RelationshipEvents::kRelationshipEventSpaceTerraformExtinction, -10.0F);
		RelationshipManager.ApplyRelationship(oldid, GetPlayerEmpireID(), RelationshipEvents::kRelationshipEventSpaceCityPanicked, -10.0F);
		RelationshipManager.ApplyRelationship(oldid, GetPlayerEmpireID(), RelationshipEvents::kRelationshipEventSpaceDestroyAllyUFO, -10.0F);
		RelationshipManager.ApplyRelationship(oldid, GetPlayerEmpireID(), RelationshipEvents::kRelationshipEventSpaceDestroyBuilding, -10.0F);
		RelationshipManager.ApplyRelationship(oldid, GetPlayerEmpireID(), RelationshipEvents::kRelationshipEventSpaceFloodCity, -10.0F);
		//test->mStars.push_back(GetActiveStarRecord());*/
	}
	return false;
}
