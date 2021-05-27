#include "stdafx.h"
#include "capacitor.h"
#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cSpaceToolData.h>
#include <Spore\Simulator\cDefaultProjectileWeapon.h>
#include <Spore\Simulator\cPlaceColonyToolStrategy.h>
#include <Spore\Simulator\cSimulatorPlayerUFO.h>
#include "MySystem.h"

capacitor::capacitor()
{
}

capacitor::~capacitor()
{
}

bool capacitor::Update(cSpaceToolData* pTool, bool showErrors, const char16_t** ppFailText)
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
		App::Property::GetFloat(pTool->mpPropList.get(), id("percentHealthToNotReserve"), reserve);
		if (ufo->mHealthPoints > ufo->mMaxHealthPoints * reserve)
		{
			ufo->mHealthPoints = ufo->mMaxHealthPoints * reserve;
		}
		/*if (inventory->mpActiveTool != nullptr)
		{
			App::ConsolePrintF("Current damage multiplier: %f", inventory->mpActiveTool->mDamageMultiplier);
			inventory->mpActiveTool->mDamageMultiplier = multiplier;
		}*/
	}
	else
	{
		MySystem::Get()->previousEnergy = 0;
		MySystem::Get()->capon = 0;
		MySystem::Get()->capefficiencyamount = 0;
	}
	return true;
}

bool capacitor::OnSelect(cSpaceToolData* pTool)
{
	float multiplier = 0;
	auto propList = pTool->mpPropList;
	float reserve;
	auto ufo = GetPlayerUFO();
	if (App::Property::GetFloat(propList.get(), id("cap-Multiplier"), multiplier)) { App::ConsolePrintF("Cool"); }
	else { multiplier = 1; }
	App::Property::GetFloat(propList.get(), id("percentHealthToNotReserve"), reserve);
	ufo->mHealthPoints *= reserve;
	auto system = MySystem::Get();
	system->capefficiencyamount = multiplier;
	system->capon = true;
	system->previousEnergy = ufo->mHealthPoints;
	return false;
}

bool capacitor::OnDeselect(cSpaceToolData* pTool)
{
	auto system = MySystem::Get();
	system->previousEnergy = 0;
	system->capon = false;
	system->capefficiencyamount = 0;
	return false;
}
