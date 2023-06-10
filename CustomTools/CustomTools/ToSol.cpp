#include "stdafx.h"
#include "ToSol.h"

ToSol::ToSol()
{
}

ToSol::~ToSol()
{
}


bool ToSol::OnSelect(cSpaceToolData* pTool)
{
	//if (test == SpaceContext::Galaxy)
	//{
		Sporepedia::ShopperRequest request(this);
		request.shopperID = id("ToPlanetShopper");
		request.gameModeID = 8;
		//request.Show(request);
		Simulator::SpaceTeleportTo(StarManager.GetSol());
	//}
	pTool->mbIsActive = false;
	return false;
}

bool ToSol::Update(cSpaceToolData* pTool, bool showErrors, const char16_t** ppFailText )
{
	showErrors = true;
	if (GetCurrentContext() == SpaceContext::Galaxy && GetActiveStarRecord() != StarManager.GetSol()) { return true; }
	else { return false; }
}

bool ToSol::WhileAiming(cSpaceToolData* pTool, const Vector3& aimPoint, bool showErrors)
{
	return false;
}

void ToSol::SelectedUpdate(cSpaceToolData* pTool, const Vector3& position)
{
	SpaceContext test;
	test = GetCurrentContext();
	if (test != SpaceContext::Galaxy) { pTool->mbIsInUse = 0; }
}

bool ToSol::OnHit(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int)
{
	return false;
}

void ToSol::OnShopperAccept(const ResourceKey& selection)
{
	App::ConsolePrintF(to_string(selection.instanceID).c_str());
	
	//auto star = GetPlayerEmpire()->GetHomeStarRecord();
	//Simulator::SpaceTeleportTo(star);

	//	StarManager.GetPlanetRecord((PlanetIndex)thingy);
//	auto planet = StarManager.GetPlanetRecord(planetindex);
//	auto star = StarManager.GetStarRecord(planet->GetStarIndex());
//	Simulator::SpaceTeleportTo(star); 
}
