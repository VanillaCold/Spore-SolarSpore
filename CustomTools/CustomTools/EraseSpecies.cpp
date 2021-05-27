#include "stdafx.h"
#include "EraseSpecies.h"
#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cSpaceToolData.h>
#include <Spore\Simulator\cDefaultProjectileWeapon.h>
#include <Spore\Simulator\cPlaceColonyToolStrategy.h>
#include <Spore\Simulator\cSimulatorPlayerUFO.h>
using namespace Simulator;

EraseSpecies::EraseSpecies()
{
}

EraseSpecies::~EraseSpecies()
{
}

void EraseSpecies::SelectedUpdate(cSpaceToolData* pTool, const Vector3& position)
{
}

bool EraseSpecies::OnSelect(cSpaceToolData* pTool)
{
	//Sporepedia::ShopperRequest request(this);
	//request.shopperID = id("SpaceGameTemplate");
	//request.shopperID = id("ToPlanetShopper");
	//request.gameModeID = 8;
	//request.Show(request);

	auto Empire = StarManager.GetEmpireForStar(GetActiveStarRecord());
	for (auto i = 0; i < Empire->mStars.capacity()-1; i += 1)
	{
		Empire->mStars[i]->mEmpireID = GetPlayerEmpireID();
		GetPlayerEmpire()->mStars.push_back(Empire->mStars[i]);
		auto system = Empire->mStars[i];
		auto it = eastl::find(Empire->mStars.begin(), Empire->mStars.end(), system);
		if (it != Empire->mStars.end())
		{
			Empire->mStars.erase(it);
		}
	}
	//Empire->mStars.empty();
	App::ConsolePrintF(to_string(Empire->mPoliticalID).c_str());

	return false;
}

bool EraseSpecies::OnDeselect(cSpaceToolData* pTool)
{
	return false;
}

void EraseSpecies::OnShopperAccept(const ResourceKey& selection)
{
}
