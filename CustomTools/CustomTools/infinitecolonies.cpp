#include "stdafx.h"
#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cSpaceToolData.h>
#include "infinitecolonies.h"
#include <Spore/Simulator/SubSystem/TerraformingManager.h>
using namespace Simulator;

infinitecolonies::infinitecolonies()
{
}

infinitecolonies::~infinitecolonies()
{
}

bool infinitecolonies::Update(cSpaceToolData* pTool, bool showErrors, const char16_t** ppFailText)
{
	bool result = Simulator::cToolStrategy::Update(pTool, showErrors, ppFailText);
	//return true;
	if (GetActivePlanetRecord())
	{
		auto planet = GetActivePlanetRecord();
		auto planet2 = GetActivePlanet();
		auto colonykey = planet->mGeneratedTerrainKey;
		planet2->mpGameDataOwner = planet2->mpGameDataOwner;
		//App::ConsolePrintF(to_string(planet->mPlanetKey).c_str());
		//terrainModelFootprints = 0x043B29E1
		//citystyles_models~ = 0x40828100
		int numcolonies = 999;
		PropertyListPtr propList;
		bool check = true;
		bool check2 = false;
		int increaseby = 0;
		int tries = 0;
		size_t count = 0;
		ResourceKey* ray{};
		vector<ResourceKey> props;
		check = PropManager.GetPropertyList(colonykey.instanceID, colonykey.groupID, propList);
		//if (check == true){ check = App::Property::GetArrayKey(propList.get(), 0x043B29E1, count, ray); }
		SporeDebugPrint(to_string(check).c_str());
		if (check == true)
		{

			SporeDebugPrint(to_string(App::Property::GetArrayKey(propList.get(), 0x043B29E1, count, ray)).c_str());
			for (int i = 0; i < count; i += 1)
			{
				if (ray[i].groupID == 0x40828100) { props.push_back(ray[i]); }
			}
			auto num = props.size();
			numcolonies = num;
			SporeDebugPrint(to_string(num).c_str());
		}

		int tScore = 3;
		if (Simulator::GetActivePlanetRecord())
		{
			tScore = TerraformingManager.GetTScore(Simulator::GetActivePlanetRecord());
		}
		if (numcolonies < 7 && tScore == 3) { return result; }
		else { return false; }
	}
	return false;
}

bool infinitecolonies::WhileAiming(cSpaceToolData* pTool, const Vector3& aimPoint, bool showErrors)
{
	return true;
}
