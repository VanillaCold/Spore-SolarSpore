#include "stdafx.h"
#include "RandomTool.h"
#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cSpaceToolData.h>
#include <Spore\Simulator\cDefaultProjectileWeapon.h>
#include <Spore\Simulator\cPlaceColonyToolStrategy.h>
#include <Spore\Simulator\cSimulatorPlayerUFO.h>
#include <EASTL\array.h>

RandomTool::RandomTool()
{
}

RandomTool::~RandomTool()
{
}

void RandomTool::SelectedUpdate(cSpaceToolData* pTool, const Vector3& position)
{
}

bool RandomTool::OnSelect(cSpaceToolData* pTool)
{
	cSpaceToolDataPtr tool;

	size_t count;
	ResourceKey* listofparts;
	PropertyListPtr propList;
	ResourceKey selectedtool = { 0, 0, 0 };

	/*PropManager.GetPropertyList(id("ToolConfig"), 0x30608F0B, propList);
	App::Property::GetArrayKey(propList.get(), 0x02C08E1E, count, listofparts);
	uint32_t gen = Math::rand(count);
	ResourceKey selectedtool = { listofparts[gen].instanceID,0,0 };*/

	auto test = pTool->mpPropList;
	
	ResourceKey* property;
	bool isList = false;
	bool successful = App::Property::GetBool(test.get(), id("RandomTool-isList"), isList);
	
	propList = test;
	int ammo = 1;
	eastl::vector<uint32_t> props;

	if (isList == false)
	{
		PropManager.GetAllListIDs(GroupIDs::SpaceTools, props);
	}
	else
	{
		uint32_t* ray;
		size_t count = 0;
		App::Property::GetArrayUInt32(test.get(), id("RandomTool-List"), count, ray);
		//auto num = sizeof(ray);
		for (int i = 0; i < count; i += 1)
		{
			props.push_back(ray[i]);
		}

		/*		uint32_t* value;
		uint32_t* tmpAr; // buffer
		size_t count = 0;
		if (App::Property::GetArrayUInt32(propList.get(), aUintDef, count, tmpAr)) {
			value = tmpAr;
		}*/

	}

	//uint32_t gen = Math::rand(props.size());
	while (propList == test)
		{
		uint32_t gen = Math::rand(props.size());
		PropManager.GetPropertyList(props[gen], GroupIDs::SpaceTools, propList);
		selectedtool = { props[gen],0,0 };
		}
	ToolManager.LoadTool(selectedtool, tool);
	tool->mCurrentAmmoCount = ammo;
	auto inventory = SimulatorSpaceGame.GetPlayerInventory();
	inventory->AddItem(tool.get());
	//0xa91269af
	auto pos = GetPlayerUFO()->GetPosition();
	pTool->ConsumeAmmo();
	pTool->mbIsActive = false;
	pTool->mbIsInUse = false;
	pTool->mRechargeTimer.Start();
	cSpaceToolDataPtr t;
	//auto inventory = SimulatorSpaceGame.GetPlayerInventory();
	if (ToolManager.LoadTool({ pTool->mpPropList->GetResourceKey().instanceID, 0, 0 }, t)) { t->mCurrentAmmoCount = 0; inventory->AddItem(t.get()); }
	IEffectPtr effect;
	if (SwarmManager.CreateEffect(pTool->mMuzzleEffectID, 0, effect)) {
		effect->SetTransform(Transform()
			.SetOffset(pos));
		effect->Start();
	}
	return true;
}

bool RandomTool::OnDeselect(cSpaceToolData* pTool)
{
	return false;
}