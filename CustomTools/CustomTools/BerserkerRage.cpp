#include "stdafx.h"
#include "BerserkerRage.h"
#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cSpaceToolData.h>
#include <Spore\Simulator\cDefaultProjectileWeapon.h>
#include <Spore\Simulator\cPlaceColonyToolStrategy.h>
#include <Spore\Simulator\cSimulatorPlayerUFO.h>
#include "MySystem.h"

BerserkerRage::BerserkerRage()
{
}

BerserkerRage::~BerserkerRage()
{
}

bool BerserkerRage::Update(cSpaceToolData* pTool, bool showErrors, const char16_t** ppFailText)
{
	/*if (GetPlayerUFO()->GetWeapon() != nullptr)
	{
		App::ConsolePrintF("Current damage: %f", GetPlayerUFO()->GetWeapon()->mDamageMultiplier);
	}
	if (pTool->mbIsActive && GetPlayerUFO()->GetWeapon() != nullptr)
	{
		GetPlayerUFO()->ChangeEnergy(GetPlayerUFO()->mEnergy -= 0.125);
		GetPlayerUFO()->GetWeapon()->mDamageMultiplier = 2;
	}*/
	int multiplier = 0;
	auto propList = pTool->mpPropList;
	auto inventory = SimulatorSpaceGame.GetPlayerInventory();
	App::Property::GetInt32(propList.get(), id("rageMode-Multiplier"),multiplier);
	if (pTool->mbIsActive)
	{
		float reserve;
		auto ufo = GetPlayerUFO();
		App::Property::GetFloat(propList.get(), id("percentEnergyToNotReserve"), reserve);
		if (ufo->mEnergy > ufo->mMaxEnergy* reserve)
		{
			ufo->mEnergy = ufo->mMaxEnergy * reserve;
		}
		/*if (inventory->mpActiveTool != nullptr)
		{
			App::ConsolePrintF("Current damage multiplier: %f", inventory->mpActiveTool->mDamageMultiplier);
			inventory->mpActiveTool->mDamageMultiplier = multiplier;
		}*/
	}
	else
	{
		if (inventory->mpActiveTool != nullptr)
		{
			inventory->mpActiveTool->mDamageMultiplier = 1;
		}
	}
	return true;
}

bool BerserkerRage::OnSelect(cSpaceToolData* pTool)
{
	int multiplier = 0;
	auto propList = pTool->mpPropList;
	float reserve;
	auto ufo = GetPlayerUFO();
	App::Property::GetInt32(propList.get(), id("rageMode-Multiplier"), multiplier);
	App::Property::GetFloat(propList.get(), id("percentEnergyToNotReserve"), reserve);
	ufo->mEnergy *= reserve;
	auto system = MySystem::Get();
	system->rageModeMultiplier = multiplier;
	system->rageModeOn = true;
	return false;
}

bool BerserkerRage::OnDeselect(cSpaceToolData* pTool)
{
	auto system = MySystem::Get();
	system->rageModeMultiplier = 1;
	system->rageModeOn = false;
	return false;
}
