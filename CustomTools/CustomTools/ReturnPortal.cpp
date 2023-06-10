#include "stdafx.h"
#include "ReturnPortal.h"

ReturnPortal::ReturnPortal()
{
}

ReturnPortal::~ReturnPortal()
{
}


bool ReturnPortal::OnSelect(cSpaceToolData* pTool)
{
	//if (test == SpaceContext::Galaxy)
	//{
	//Sporepedia::ShopperRequest request(this);
	//request.shopperID = id("ToPlanetShopper");
	//request.gameModeID = 8;
	//request.Show(request);
	
	auto currentPos = GetActiveStarRecord()->mPosition;
	auto empire = GetPlayerEmpire();
	float closestdist = 9999999;
	auto closeststar = GetPlayerEmpire()->mHomeStar;
	for (int i = 0; i < empire->mStars.size(); i += 1)
	{
		Vector3 pos1 = currentPos; 
		Vector3 pos2 = empire->mStars[i]->mPosition;

		float dist = Math::distance(pos1, pos2);

		/*if (currentPos.x < 0) { pos1.x *= -1; }
		if (currentPos.y < 0) { pos1.y *= -1; }
		if (currentPos.z < 0) { pos1.z *= -1; }
		if (pos2.x < 0) { pos2.x *= -1; }
		if (pos2.y < 0) { pos2.y *= -1; }
		if (pos2.z < 0) { pos2.z *= -1; }

		Vector3 vecdist = { (max(pos1.x, pos2.x) - min(pos1.x,pos2.x)),(max(pos1.y, pos2.y) - min(pos1.y,pos2.y)),(max(pos1.z, pos2.z) - min(pos1.x,pos2.z)) };
		float dist = max(vecdist.x, vecdist.y) - min(vecdist.x, vecdist.y);*/

		if (dist < closestdist)
		{
			closeststar = empire->mStars[i]->mKey;
			closestdist = dist;
		}
	}
	if (closeststar.internalValue != GetActiveStarRecord()->mKey.internalValue)
	{
		SpaceTeleportTo(StarManager.GetStarRecord(closeststar));
	}
	//Simulator::SpaceTeleportTo(StarManager.GetSol());
	//}
	pTool->mbIsActive = false;
	return false;
}

bool ReturnPortal::Update(cSpaceToolData* pTool, bool showErrors, const char16_t** ppFailText)
{
	bool result = Simulator::cToolStrategy::Update(pTool, showErrors, ppFailText);
	showErrors = true;
	auto it = eastl::find(GetPlayerEmpire()->mStars.begin(), GetPlayerEmpire()->mStars.end(), GetActiveStarRecord());
	if (GetCurrentContext() == SpaceContext::Galaxy && it == GetPlayerEmpire()->mStars.end() && GetActiveStarRecord() != nullptr) { return result; }
	else { return false; }
}

bool ReturnPortal::WhileAiming(cSpaceToolData* pTool, const Vector3& aimPoint, bool showErrors)
{
	return false;
}

void ReturnPortal::SelectedUpdate(cSpaceToolData* pTool, const Vector3& position)
{
	SpaceContext test;
	test = GetCurrentContext();
	if (test != SpaceContext::Galaxy) { pTool->mbIsInUse = 0; }
}

bool ReturnPortal::OnHit(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int)
{
	return false;
}

//void ReturnPortal::OnShopperAccept(const ResourceKey& selection)
//{
	//App::ConsolePrintF(to_string(selection.instanceID).c_str());

	//auto star = GetPlayerEmpire()->GetHomeStarRecord();
	//Simulator::SpaceTeleportTo(star);

	//	StarManager.GetPlanetRecord((PlanetIndex)thingy);
//	auto planet = StarManager.GetPlanetRecord(planetindex);
//	auto star = StarManager.GetStarRecord(planet->GetStarIndex());
//	Simulator::SpaceTeleportTo(star); 
//}
