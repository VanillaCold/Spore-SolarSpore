//int32 GrobAirVehicleInstance 0x065cb66f
//int32 GrobCityHallInstance 0x06576db9
//int32 GrobEntertainmentInstance 0x06576dbf
//int32 GrobFactoryInstance 0x06576dbd
//int32 GrobGroundVehicleInstance 0x06576db7
//int32 GrobHouseInstance 0x06576dbb
//int32 GrobWaterVehicleInstance 0x065ce473
//int32 grobUFOInstance 0x06576dbd
#include "stdafx.h"
#include "SpawnVehicle.h"
#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cSpaceToolData.h>
using namespace Simulator;

SpawnVehicle::SpawnVehicle()
{
}

SpawnVehicle::~SpawnVehicle()
{
}

void SpawnVehicle::OnMouseDown(cSpaceToolData* pTool, const Vector3& playerPosition)
{
	playpos = playerPosition;
	cDefaultBeamTool::OnMouseDown(pTool, playerPosition);
}

bool SpawnVehicle::WhileFiring(cSpaceToolData* pTool, const Vector3& aimPoint, int)
{
	if (vehicle == nullptr) {
		vehicle = simulator_new<cGameDataUFO>();
		//vehicle->(kVehicleLand, kVehicleMilitary, { 0x06576db7, TypeIDs::vcl, GroupIDs::VehicleModels });
	}
	vehicle->SetPosition(aimPoint);
	if (beameffect != nullptr) {
		beameffect->SetRigidTransform(Transform()
			.SetOffset(playpos));
	}
	if (hiteffect != nullptr) {
		hiteffect->SetRigidTransform(Transform()
			.SetOffset(aimPoint));
	}


	if (hiteffect == nullptr)
	{
		if (EffectsManager.CreateVisualEffect(id("SG_laser_lvl_1_beam_impact"), 0, hiteffect)) {
			hiteffect->SetRigidTransform(Transform()
				.SetOffset(aimPoint));
			hiteffect->Start();
		}
	}
	if (beameffect == nullptr)
	{
		if (EffectsManager.CreateVisualEffect(id("SG_laser_lvl_1_beam"), 0, beameffect))
		{
			beameffect->SetRigidTransform(Transform()
				.SetOffset(playpos));
			beameffect->Start();
		}
	}
	//cDefaultBeamTool::WhileFiring(pTool, aimPoint, 0);

	return false;
}

bool SpawnVehicle::OnMouseUp(cSpaceToolData* pTool)
{
	hiteffect->Stop();
	beameffect->Stop();
	cDefaultBeamTool::OnMouseUp(pTool);
	return false;
}
