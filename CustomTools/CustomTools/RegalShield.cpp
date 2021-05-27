#include "stdafx.h"
#include "RegalShield.h"
#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cSpaceToolData.h>
#include <Spore\Simulator\cDefaultProjectileWeapon.h>
#include <Spore\Simulator\cPlaceColonyToolStrategy.h>
#include <Spore\Simulator\cSimulatorPlayerUFO.h>
#include "MySystem.h"

RegalShield::RegalShield()
{
}

RegalShield::~RegalShield()
{
}

bool RegalShield::Update(cSpaceToolData* pTool, bool showErrors, const char16_t** ppFailText)
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
	/*int multiplier = 0;
	auto propList = pTool->mpPropList;
	auto inventory = SimulatorSpaceGame.GetPlayerInventory();
	App::Property::GetInt32(propList.get(), id("rageMode-Multiplier"), multiplier);*/
	if (pTool->mbIsActive)
	{
		float reserve;
		auto ufo = GetPlayerUFO();
		App::Property::GetFloat(pTool->mpPropList.get(), id("percentEnergyToNotReserve"), reserve);
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
		MySystem::Get()->previousHealth = 0;
		MySystem::Get()->shieldon = 0;
		MySystem::Get()->shieldprotectionamount = 0;
	}
	return true;
}

bool RegalShield::OnSelect(cSpaceToolData* pTool)
{
	float multiplier = 0;
	auto propList = pTool->mpPropList;
	float reserve;
	auto ufo = GetPlayerUFO();
	if (App::Property::GetFloat(propList.get(), id("shield-Multiplier"), multiplier)) { App::ConsolePrintF("Cool"); }
	else { multiplier = 1; }
	App::Property::GetFloat(propList.get(), id("percentEnergyToNotReserve"), reserve);
	ufo->mEnergy *= reserve;
	auto system = MySystem::Get();
	system->shieldprotectionamount = multiplier;
	system->shieldon = true;
	system->previousHealth = ufo->mHealthPoints;
	return false;
}

bool RegalShield::OnDeselect(cSpaceToolData* pTool)
{
	auto system = MySystem::Get();
	system->previousHealth = 0;
	system->shieldon = false;
	system->shieldprotectionamount = 0;
	return false;
}
