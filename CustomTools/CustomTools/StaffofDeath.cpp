#include "stdafx.h"
#include "StaffofDeath.h"
#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cSpaceToolData.h>
#include "MySystem.h"
using namespace Simulator;

StaffofDeath::StaffofDeath()
{
}

StaffofDeath::~StaffofDeath()
{
}

bool StaffofDeath::OnHit(cSpaceToolData* pTool, const Vector3& position, cSpaceToolData::SpaceToolHit hitType, int)
{
	GetActivePlanetRecord()->mAtmosphereScore = -0.25;
	App::ConsolePrintF(to_string(GetActivePlanetRecord()->mAtmosphereScore).c_str());
	MySystem* System = MySystem::Get();
	System->deadplanets.push_back(GetActivePlanetRecord()->GetID());
	return false;
}