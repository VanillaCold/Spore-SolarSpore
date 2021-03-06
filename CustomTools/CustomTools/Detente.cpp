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

	RelationshipManager.DeclarePeace((uint32_t)oldemp, (uint32_t)GetPlayerEmpire());
	RelationshipManager.ResetRelationship(oldemp->mPoliticalID, GetPlayerEmpire()->mPoliticalID);
	RelationshipManager.ApplyRelationship(oldemp->mPoliticalID, otheremp->mPoliticalID, RelationshipEvents::kRelationshipEventDeclaredWar, 0.5F);

	return false;
}
