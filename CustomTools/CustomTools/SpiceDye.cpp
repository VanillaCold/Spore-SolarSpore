#include "stdafx.h"
#include "SpiceDye.h"
#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cSpaceToolData.h>
#include "MySystem.h"
using namespace Simulator;

SpiceDye::SpiceDye()
{
}

SpiceDye::~SpiceDye()
{
}

bool SpiceDye::OnHit(cSpaceToolData* pTool, const Vector3& position, cSpaceToolData::SpaceToolHit hitType, int)
{
	//MessageManager.PostMSG(0x6527EAF, nullptr);
	//MessageManager.PostMSG(0x6527EAD, nullptr);
	return false;
}

bool SpiceDye::Update(cSpaceToolData* pTool, bool showErrors, const char16_t** ppFailText)
{
	auto mulah = GetPlayerEmpire()->mEmpireMoney;
	
	int cost;
	App::Property::GetInt32(pTool->mpPropList.get(), 0x10609EDF, cost);
	if (pTool->mRechargeTimer.IsRunning() == true)
	{
		if (pTool->mRechargeTimer.GetElapsed().LowPart >= pTool->mRechargeRate*1000)
		{
			pTool->mRechargeTimer.Stop();
		}
	}
	if (GetCurrentContext() == kSpaceContextSolarSystem && pTool->mRechargeTimer.IsRunning() == false && mulah >= cost) { return true; }
	else { return false; }
}

bool SpiceDye::OnSelect(cSpaceToolData* pTool)
{
	ResourceKey& Spice = ResourceKey(0,0,0);
	PropertyListPtr propList = pTool->mpPropList;
	App::Property::GetKey(propList.get(),id("SpiceDye-SpiceFile"),Spice);
	App::ConsolePrintF(to_string(GetActivePlanetRecord()->mSpiceGen.instanceID).c_str());
	GetActivePlanetRecord()->mSpiceGen.instanceID = Spice.instanceID;
	int cost;
	App::Property::GetInt32(pTool->mpPropList.get(), 0x10609EDF, cost);
	GetPlayerEmpire()->mEmpireMoney -= cost;


	PropManager.GetPropertyList(Spice.instanceID, GroupIDs::SpaceTrading, propList);
	uint32_t spicecolour;
	App::Property::GetUInt32(propList.get(), 0x058CBB75, spicecolour);

	auto planet = GetActivePlanet();
	planet->field_1C4 = spicecolour;

	pTool->mbIsActive = false;
	pTool->mbIsInUse = false;
	pTool->mRechargeTimer.Start();
	//pTool->mChargeTimer.Start();
	return false;
}
