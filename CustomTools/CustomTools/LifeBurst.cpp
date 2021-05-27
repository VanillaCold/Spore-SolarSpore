#include "stdafx.h"
#include "LifeBurst.h"
#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cSpaceToolData.h>
#include "MySystem.h"
using namespace Simulator;

LifeBurst::LifeBurst()
{
}

LifeBurst::~LifeBurst()
{
}

bool LifeBurst::OnHit(cSpaceToolData* pTool, const Vector3& position, cSpaceToolData::SpaceToolHit hitType, int)
{
	MySystem* System = MySystem::Get();
	auto propList = pTool->mpPropList;
	float atmo = 0;
	float temp = 0;
	bool neworold = false;
	if (App::Property::GetFloat(propList.get(), id("LifeBurst-TargetAtmosphere"), atmo) && App::Property::GetFloat(propList.get(), id("LifeBurst-TargetTemperature"), temp))
	{
		neworold = true;
	}
	auto it = eastl::find(System->deadplanets.begin(), System->deadplanets.end(), GetActivePlanetRecord()->GetID());
	if (it != System->deadplanets.end())
	{
		System->deadplanets.erase(it);
	}
	if (neworold == false)
	{
		GetActivePlanetRecord()->mAtmosphereScore = 0.5;
		GetActivePlanetRecord()->mTemperatureScore = 0.5;
	}
	else
	{
		GetActivePlanetRecord()->mAtmosphereScore = atmo;
		GetActivePlanetRecord()->mTemperatureScore = temp;
	}
	App::ConsolePrintF(to_string(GetActivePlanetRecord()->mAtmosphereScore).c_str());
	if (GetActivePlanetRecord()->mTechLevel == TechLevel(0)) { GetActivePlanetRecord()->mTechLevel = TechLevel(1); }
	return false;
}