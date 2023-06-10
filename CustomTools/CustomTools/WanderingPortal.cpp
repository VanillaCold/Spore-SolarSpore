#include "stdafx.h"
#include "WanderingPortal.h"
#include <Spore\Simulator\cSimulatorPlayerUFO.h>

WanderingPortal::WanderingPortal()
{
}

WanderingPortal::~WanderingPortal()
{
}


bool WanderingPortal::OnSelect(cSpaceToolData* pTool)
{

	auto PlayerCoords = GetPlayerUFO()->GetPosition();
	auto propList = pTool->mpPropList;
	float radius;
	auto Star = StarManager.FindClosestStar({ PlayerCoords.x + Math::randf(-20,20),PlayerCoords.y + Math::randf(-20,20),PlayerCoords.y + Math::randf(-5,5) });
	if (App::Property::GetFloat(propList.get(), id("WanderingPortal-Radius"), radius))
	{
		auto diam = radius / 2;
		Star = StarManager.FindClosestStar({ PlayerCoords.x + Math::randf(-diam,diam),PlayerCoords.y + Math::randf(-diam,diam),PlayerCoords.y + Math::randf(-5,5) });
	}

	Simulator::SpaceTeleportTo(Star);
	pTool->mRechargeTimer.Start();
	pTool->mbIsActive = false;
	if (pTool->mAmmoUsedPerShot != 0)
	{
		pTool->ConsumeAmmo();
		cSpaceToolDataPtr t;
		auto inventory = SimulatorSpaceGame.GetPlayerInventory();
		if (ToolManager.LoadTool({ pTool->mpPropList->GetResourceKey().instanceID, 0, 0 }, t)) { t->mCurrentAmmoCount = 0; inventory->AddItem(t.get()); }
	}
	return false;
}

bool WanderingPortal::Update(cSpaceToolData* pTool, bool showErrors, const char16_t** ppFailText)
{
	showErrors = true;
	auto enoughammo = true;
	if (pTool->mRechargeTimer.IsRunning() == true)
	{
		if (pTool->mRechargeTimer.GetElapsed().LowPart >= pTool->mRechargeRate * 1000)
		{
			pTool->mRechargeTimer.Stop();
		}
	}
	if (pTool->mAmmoUsedPerShot != 0) { if (pTool->mCurrentAmmoCount < pTool->mAmmoUsedPerShot) { enoughammo = false; } }
	if (GetCurrentContext() == SpaceContext::Galaxy && pTool->mRechargeTimer.IsRunning() == false && enoughammo == true) { return true; }
	else { return false; }
}

bool WanderingPortal::WhileAiming(cSpaceToolData* pTool, const Vector3& aimPoint, bool showErrors)
{
	return false;
}

void WanderingPortal::SelectedUpdate(cSpaceToolData* pTool, const Vector3& position)
{
}

bool WanderingPortal::OnHit(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int)
{
	return false;
}
