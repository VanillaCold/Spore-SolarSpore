#include "stdafx.h"
#include "ChangeSpecies.h"
#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cSpaceToolData.h>
#include <Spore\Simulator\cDefaultProjectileWeapon.h>
#include <Spore\Simulator\cPlaceColonyToolStrategy.h>
#include <Spore\Simulator\cSimulatorPlayerUFO.h>
#include "MySystem.h"
using namespace Simulator;

ChangeSpecies::ChangeSpecies()
{
}

ChangeSpecies::~ChangeSpecies()
{
}

void ChangeSpecies::SelectedUpdate(cSpaceToolData* pTool, const Vector3& position)
{
}

bool ChangeSpecies::OnSelect(cSpaceToolData* pTool)
{
	tool = pTool;
	pTool->ConsumeAmmo();
	cSpaceToolDataPtr t;
	auto inventory = SimulatorSpaceGame.GetPlayerInventory();
	if (ToolManager.LoadTool({ pTool->mpPropList->GetResourceKey().instanceID, 0, 0 }, t)) { t->mCurrentAmmoCount = 0; inventory->AddItem(t.get()); }
	Sporepedia::ShopperRequest request(this);
	request.shopperID = id("OnlySpaceShopper");
	request.Show(request);
	pTool->mbIsActive = false;
	pTool->mbIsInUse = false;
	return true;
}

bool ChangeSpecies::OnDeselect(cSpaceToolData* pTool)
{
	return false;
}

void ChangeSpecies::OnShopperAccept(const ResourceKey& selection)
{
	auto syst = MySystem::Get();
	syst->Selection = selection;
	auto SelectedSpecies = SpeciesManager.GetSpeciesProfile(selection);
	auto name = GetPlayerEmpire()->mEmpireName;
	GetPlayerEmpire()->SetSpeciesProfile(SelectedSpecies);
	auto pos = GetPlayerUFO()->GetPosition();
	if (SwarmManager.CreateEffect(tool->mMuzzleEffectID, 0, effect)) {
		effect->SetTransform(Transform()
			.SetOffset(pos));
		effect->Start();
	}
	auto captain = GetPlayerEmpire()->mCaptainKey;
	GetPlayerEmpire()->mCaptainKey = captain;
//	GetPlayerEmpire()->mEmpireName = name;
}
