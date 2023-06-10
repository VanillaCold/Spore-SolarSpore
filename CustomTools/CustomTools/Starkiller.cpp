//25608
#include "stdafx.h"
#include "StarKiller.h"
#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cSpaceToolData.h>
#include <Spore\Simulator\cDefaultProjectileWeapon.h>
#include <Spore\Simulator\cPlaceColonyToolStrategy.h>
#include <Spore\Simulator\cSimulatorPlayerUFO.h>
#include "MySystem.h"
using namespace Simulator;

StarKiller::StarKiller()
{
}

StarKiller::~StarKiller()
{
}

bool StarKiller::WhileAiming(cSpaceToolData* pTool, const Vector3& aimPoint, bool showErrors)
{
	return false;
}

void StarKiller::SelectedUpdate(cSpaceToolData* pTool, const Vector3& position)
{
}

bool StarKiller::OnHit(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int)
{
	return false;
}

bool StarKiller::OnSelect(cSpaceToolData* pTool)
{
	auto star = GetActiveStarRecord();
	star->mType = StarType::ProtoPlanetary;
	
	if (EffectsManager.CreateVisualEffect(pTool->mMuzzleEffectID, 0, effect)) {
		effect->SetRigidTransform(Transform()
			.SetOffset(GetPlayerUFO()->GetPosition()));
		effect->Start();
	}

	for (int i = 0; i < star->mPlanets.size(); i++)
	{
		star->mPlanets[i]->mOrbit.mEccentricity = 10000000000;
		star->mPlanets[i]->mOrbit.mPerihelion = Vector3(10000000000, 10000000000, 10000000000);
		star->mPlanets[i]->mOrbit.mPlaneNormal = Vector3(10000000000, 10000000000, 10000000000);
		star->mPlanets[i]->mOrbit.mPeriod = 10000000000;
		if (!(star->mPlanets[i]->mFlags & 256))
		{
			star->mPlanets[i]->mFlags += 256;
		}
		star->mPlanets[i]->mTechLevel = TechLevel::None;
		star->mPlanets[i]->mbHomeWorld = 0;
		cPlanetPtr planet;
		StarManager.RecordToPlanet(star->mPlanets[i].get(),planet);
		if (planet != nullptr)
		{
			//planet->RemoveOwner();
			//planet->SetPoliticalID(0);
			planet->mPlanetScale = 0;
			if (star->mEmpireID != -1 && (planet->mpPlanetRecord->mTechLevel == Simulator::TechLevel::Empire ||
			planet->mpPlanetRecord->mTechLevel == Simulator::TechLevel::Civilization || planet->mpPlanetRecord->mTechLevel == Simulator::TechLevel::Tribe));
			//planet->SetPosition(Vector3(10000000, 1000000000, 10000000));
		}
	}
	/*auto empire = StarManager.GetEmpire(star->mEmpireID);
	if (empire != nullptr)
	{
		auto it = eastl::find(empire->mStars.begin(), empire->mStars.end(), star);
		if (it != empire->mStars.end())
		{
			empire->mStars.erase(it);
		}
		if (empire->mHomeStar = star->mKey && empire->mNextStarTowardsHome.begin() != empire->mNextStarTowardsHome.end())
		{
			empire->mHomeStar = empire->mNextStarTowardsHome[0]->mKey;
			empire->mHomePlanet = empire->mHomePlanet = empire->mNextStarTowardsHome[0]->mPlanets[0]->GetID();
		}
	}*/

	//star->mEmpireID = -1;
	//star->mPlanetCount = 0;
	//star->mPlanets.erase(star->mPlanets.begin(), star->mPlanets.end());
	auto star2 = GetActiveStar(); 
	star2->mbIsDestroyed = 1;
	star2->mPrimaryType = StarType::BlackHole;
	star2->mSecondaryType = StarType::BlackHole;

	/*auto& emps = StarManager.GetEmpires();
	int nullemps = 0;
	for (int i = 0; i < emps.mnSize; i++)
	{

		if (emps[i] != nullptr)
		{
			if (emps[i]->mPoliticalID != GetPlayerEmpireID())
				RelationshipManager.ApplyRelationship(emps[i]->mPoliticalID, GetPlayerEmpireID(), RelationshipEvents::kRelationshipEventSpaceBadToolUse, 50);
		}
		else nullemps++;
		if (nullemps > 10000) { break; }
	}*/
	
	pTool->ConsumeAmmo();
	pTool->mbIsActive = false;
	pTool->mbIsInUse = false;
	auto inventory = SimulatorSpaceGame.GetPlayerInventory();
	cSpaceToolDataPtr t;
	if (ToolManager.LoadTool({ pTool->mpPropList->GetResourceKey().instanceID, 0, 0 }, t)) { t->mCurrentAmmoCount = 0; inventory->AddItem(t.get()); }
	return true;
}

bool StarKiller::Update(cSpaceToolData* pTool, bool showErrors, const char16_t** ppFailText)
{
	bool result = Simulator::cToolStrategy::Update(pTool, showErrors, ppFailText);
	if (GetCurrentContext() == SpaceContext::Galaxy)
	{
		if (GetActiveStarRecord()->mType != StarType::GalacticCore && GetActiveStarRecord()->mType != StarType::BlackHole && GetActiveStarRecord()->mType != StarType::ProtoPlanetary && GetActiveStarRecord()->mEmpireID == -1)
		{
			return result;
		}
	}
	return false;
}

bool StarKiller::OnDeselect(cSpaceToolData* pTool)
{
	return false;
}