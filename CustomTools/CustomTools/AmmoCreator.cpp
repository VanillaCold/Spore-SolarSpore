#include "stdafx.h"
#include "AmmoCreator.h"
#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cSpaceToolData.h>
#include <Spore\Simulator\cDefaultProjectileWeapon.h>
#include <Spore\Simulator\cPlaceColonyToolStrategy.h>
#include <Spore\Simulator\cSimulatorPlayerUFO.h>
//#include "MySystem.h"
using namespace Simulator;

AmmoCreator::AmmoCreator()
{
}

AmmoCreator::~AmmoCreator()
{
}

void AmmoCreator::SelectedUpdate(cSpaceToolData* pTool, const Vector3& position)
{
}

bool AmmoCreator::OnSelect(cSpaceToolData* pTool)
{
	auto inventory = SimulatorSpaceGame.GetPlayerInventory();
	int cost = 0;
	//if (inventory->mpActiveTool != nullptr)
	for (int i = 0; i < inventory->mInventoryItems.size(); i += 1)
	{
		auto& tool = inventory->mInventoryItems[i];
		PropertyListPtr propList;
		vector<uint32_t> ray1;
		ray1.push_back(0);
		vector<uint32_t>& ray = ray1;
		//PropManager.GetAllListIDs(GroupIDs::SpaceTrading, ray);
		//for (int j = 0; j < ray.size(); j += 1)
		//{
		auto money = GetPlayerEmpire()->mEmpireMoney;
		//P/ropManager.GetPropertyList(GroupIDs::SpaceTrading, ray[j], propList);
		//ResourceKey& propthingy = ResourceKey(0,0,0);
		//App::Property::GetKey(propList.get(), 0x035D5CB4, propthingy);
		//if (App::Property::GetInt32(propList.get(), 0x034F1A4A, cost) && tool->mItemCount < 1 && money >= cost * 5 && tool->IsCargoType() == false && tool->mpPropList != pTool->mpPropList && propthingy.instanceID == tool->GetItemInstanceID())
		//tool->IsCargoType() == false && 
		if (tool->IsCargoType() == false && tool->mpPropList != nullptr)
		{
			//tool->mItemCount
			cSpaceToolDataPtr tool2;
			bool test;
			App::Property::GetBool(tool->mpPropList.get(), 0xF0609ED3, test);
			if (ToolManager.LoadTool({ tool->mpPropList->GetResourceKey().instanceID,0,0 }, tool2) && test == true && tool->mpPropList != pTool->mpPropList && GetPlayerEmpire()->mEmpireMoney >= 750000)
			{
				tool2->mCurrentAmmoCount = 5;
				inventory->AddItem(tool2.get());
				GetPlayerEmpire()->mEmpireMoney -= 750000;
			}
			//j = ray.size() + 1;
		}

		//}
	}

	pTool->ConsumeAmmo();
	pTool->mbIsActive = false;
	pTool->mbIsInUse = false;
	cSpaceToolDataPtr t;
	if (ToolManager.LoadTool({ pTool->mpPropList->GetResourceKey().instanceID, 0, 0 }, t)) { t->mCurrentAmmoCount = 0; inventory->AddItem(t.get()); }
	return true;
}

bool AmmoCreator::OnDeselect(cSpaceToolData* pTool)
{
	return false;
}

bool AmmoCreator::Update(cSpaceToolData* pTool, bool showErrors, const char16_t** ppFailText)
{
	bool result = Simulator::cToolStrategy::Update(pTool, showErrors, ppFailText);
	auto inventory = SimulatorSpaceGame.GetPlayerInventory();
	int cost = 0;
	//if (inventory->mpActiveTool != nullptr)
	for (int i = 0; i < inventory->mInventoryItems.size(); i += 1)
	{
		auto& tool = inventory->mInventoryItems[i];
		PropertyListPtr propList;
		if (tool->IsCargoType() == false && tool->mpPropList != nullptr)
		{
			//tool->mItemCount
			cSpaceToolDataPtr tool2;
			bool test;
			App::Property::GetBool(tool->mpPropList.get(), 0xF0609ED3, test);
			if (/*ToolManager.LoadTool({ tool->mpPropList->GetResourceKey().instanceID,0,0 }, tool2) && */test == true && tool->mpPropList != pTool->mpPropList)
			{
				//tool2->mCurrentAmmoCount = 5;
				//inventory->AddItem(tool2.get());
				cost += 750000;
			}
			//j = ray.size() + 1;
		}
		//}
	}
	if (cost <= GetPlayerEmpire()->mEmpireMoney && pTool->mCurrentAmmoCount >= pTool->mAmmoUsedPerShot)
	{
		return true;
	}
	return result;
}

/*void AmmoCreator::OnShopperAccept(const ResourceKey& selection)
{
	auto syst = MySystem::Get();
	syst->Selection = selection;
	auto SelectedSpecies = SpeciesManager.GetSpeciesProfile(selection);
	auto name = GetPlayerEmpire()->mEmpireName;
	GetPlayerEmpire()->SetSpeciesProfile(SelectedSpecies);
	auto pos = GetPlayerUFO()->GetPosition();
	if (EffectsManager.CreateVisualEffect(tool->mMuzzleEffectID, 0, effect)) {
		effect->SetTransform(Transform()
			.SetOffset(pos));
		effect->Start();
	}
	auto captain = GetPlayerEmpire()->mCaptainKey;
	GetPlayerEmpire()->mCaptainKey = captain;
	//	GetPlayerEmpire()->mEmpireName = name;
}*/