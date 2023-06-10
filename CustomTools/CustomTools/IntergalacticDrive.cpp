#include "stdafx.h"
#include "IntergalacticDrive.h"
#include <Spore\App\cViewer.h>

IntergalacticDrive::IntergalacticDrive()
{
	//point = {};
	//oldcam = id("TopdownGalaxy");
}

IntergalacticDrive::~IntergalacticDrive()
{
}


bool IntergalacticDrive::OnSelect(cSpaceToolData* pTool)
{
	oldcam = CameraManager.GetActiveCameraID();
	//CameraManager.SetActiveCameraByID(id("TopdownGalaxy3"));
	//LPPOINT point{};
	return false;
}

bool StarModelFilter(Graphics::Model* model)
{
	if (object_cast<cStar>(model->GetOwner())) return true;
	else return false;
}

bool IntergalacticDrive::Update(cSpaceToolData* pTool, bool showErrors, const char16_t** ppFailText)
{
	showErrors = true;
	SpaceContext test;
	test = GetCurrentContext();
	if (pTool->mbIsActive == true)
	{
		//GameInput mInput;
		//GetCursorPos(point);
		//if (point != nullptr) {
		if (mInput.IsMouseButtonDown(MouseButton::kMouseButtonLeft))
		{
			Vector3 cameraPosition, mouseDir;
			App::GetViewer()->GetCameraToMouse(cameraPosition, mouseDir);
			auto viewDir = CameraManager.GetViewer()->GetViewTransform().GetRotation().Row(1);
			cGameDataPtr object;
			Vector3 intersection;
			auto test = Math::PlaneEquation({ 0,0,100000000 }, { 0,0,0 });
			Math::Vector3 starpos{};
			Math::PlaneEquation::Intersection thingy = test.IntersectRay(cameraPosition, mouseDir, starpos);
			//auto star = StarManager.FindClosestStar(Vector3(mInput.clickPosition.x, mInput.clickPosition.y, 0));
			//if (GameViewManager.Raycast(cameraPosition, cameraPosition + mouseDir * 1000.0f, nullptr, object, intersection,true))
			if(thingy == Math::PlaneEquation::Intersection::Point)
			{
				auto star = StarManager.FindClosestStar(starpos);
				App::ConsolePrintF(to_string(mInput.clickPosition.x).c_str());
				App::ConsolePrintF(to_string(mInput.clickPosition.y).c_str());
				Simulator::SpaceTeleportTo(star);
				CameraManager.SetActiveCameraByID(oldcam);
				pTool->mbIsActive = 0;
				pTool->mbIsInUse = 0;
				pTool->mRechargeTimer.Start();
			}
		}
	}

	//App::Property::GetInt32(pTool->mpPropList.get(), 0x10609EDF, cost);
	if (pTool->mRechargeTimer.IsRunning() == true)
	{
		if (pTool->mRechargeTimer.GetElapsed().LowPart >= pTool->mRechargeRate * 1000)
		{
			pTool->mRechargeTimer.Stop();
		}
	}
	if (GetCurrentContext() == SpaceContext::Galaxy && pTool->mRechargeTimer.IsRunning() == false && pTool->mEnergyCost/10 < GetPlayerUFO()->mEnergy) { return true; }
	else { pTool->mbIsInUse = false; return false; }
	//}
}

bool IntergalacticDrive::WhileAiming(cSpaceToolData* pTool, const Vector3& aimPoint, bool showErrors)
{
	return false;
}

void IntergalacticDrive::SelectedUpdate(cSpaceToolData* pTool, const Vector3& position)
{
	GetCursorPos(point);
	auto star = StarManager.FindClosestStar(Vector3(point->x, point->y, 0));
	SpaceContext test;
	test = GetCurrentContext();
	GameInput mInput;
	App::ConsolePrintF(to_string(point->x).c_str());
	App::ConsolePrintF(to_string(point->y).c_str());
	if (mInput.IsMouseButtonDown(MouseButton::kMouseButtonRight)) 
		{
		Simulator::SpaceTeleportTo(star);
		CameraManager.SetActiveCameraByID(oldcam);
		}

	if (test != SpaceContext::Galaxy) { pTool->mbIsInUse = 0; }
	//pTool->mbIsActive = false;
}

bool IntergalacticDrive::OnHit(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int)
{
	return false;
}

void IntergalacticDrive::OnShopperAccept(const ResourceKey& selection)
{
	App::ConsolePrintF(to_string(selection.instanceID).c_str());

	//auto star = GetPlayerEmpire()->GetHomeStarRecord();
	//Simulator::SpaceTeleportTo(star);

	//	StarManager.GetPlanetRecord((PlanetIndex)thingy);
//	auto planet = StarManager.GetPlanetRecord(planetindex);
//	auto star = StarManager.GetStarRecord(planet->GetStarIndex());
//	Simulator::SpaceTeleportTo(star); 
}
