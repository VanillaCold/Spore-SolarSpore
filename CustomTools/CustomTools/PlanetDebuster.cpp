//25608
#include "stdafx.h"
#include "PlanetDebuster.h"
#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cSpaceToolData.h>
#include <Spore\Simulator\cDefaultProjectileWeapon.h>
#include <Spore\Simulator\cPlaceColonyToolStrategy.h>
#include <Spore\Simulator\cSimulatorPlayerUFO.h>
#include "MySystem.h"
using namespace Simulator;

PlanetDebuster::PlanetDebuster()
{
}

PlanetDebuster::~PlanetDebuster()
{
}

bool PlanetDebuster::WhileAiming(cSpaceToolData* pTool, const Vector3& aimPoint, bool showErrors)
{
	return false;
}

void PlanetDebuster::SelectedUpdate(cSpaceToolData* pTool, const Vector3& position)
{
}

bool PlanetDebuster::OnHit(cSpaceToolData* pTool, const Vector3& position, cSpaceToolData::SpaceToolHit hitType, int)
{
	return false;
}

bool PlanetDebuster::OnSelect(cSpaceToolData* pTool)
{
	GetActivePlanetRecord()->mFlags -= 256;
	SporeDebugPrint("Planet flags: %i", GetActivePlanetRecord()->mFlags);
	pTool->ConsumeAmmo();
	pTool->mbIsActive = false;
	pTool->mbIsInUse = false;
	return true;
}

bool PlanetDebuster::Update(cSpaceToolData* pTool, bool showErrors, const char16_t** ppFailText)
{
	if (GetCurrentContext() == kSpaceContextSolarSystem)
	{
		if (GetActivePlanetRecord()->mFlags & 256)
		{
			return true;
		}
	}
	return false;
}

bool PlanetDebuster::OnDeselect(cSpaceToolData* pTool)
{
	return false;
}