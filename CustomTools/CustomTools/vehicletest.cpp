#include "stdafx.h"
#include "vehicletest.h"

vehicletest::vehicletest()
{
}


vehicletest::~vehicletest()
{
}


void vehicletest::ParseLine(const ArgScript::Line& line)
{
	// This method is called when your cheat is invoked.
	// Put your cheat code here.

	//cVehiclePtr vehicle = simulator_new<cVehicle>();
	//vehicle->Load(kVehicleLand, kVehicleMilitary, { 0x19A3A9AC, TypeIDs::vcl, GroupIDs::VehicleModels });

	// If you are on civ/space stage, you can spawn a vehicle that belongs to a city
	// The last argument is whether you are on space stage

	/*auto starr = Simulator::GetActiveStarRecord();
	auto star = Simulator::GetActiveStar();
	auto planetr = Simulator::GetActivePlanetRecord();
	auto planet = Simulator::GetActivePlanet();*/

	//App::ConsolePrintF("test");
	/*if (Simulator::GetPlayerEmpire()->mArchetype != Simulator::kArchetypePlayerWanderer)
	{
		auto inventory = SimulatorSpaceGame.GetPlayerInventory();
		if (auto test = inventory->GetItem(id("cashinfusion"))) { inventory->RemoveItem(test); }
		if (auto test = inventory->GetItem(id("gravitationwave"))) { inventory->RemoveItem(test); }
		if (auto test = inventory->GetItem(id("peacebomb"))) { inventory->RemoveItem(test); }
		if (auto test = inventory->GetItem(id("portal"))) { inventory->RemoveItem(test); }
		if (auto test = inventory->GetItem(id("raiderrally"))) { inventory->RemoveItem(test); }
		if (auto test = inventory->GetItem(id("safarivacuum"))) { inventory->RemoveItem(test); }
		if (auto test = inventory->GetItem(id("soothingsong"))) { inventory->RemoveItem(test); }
		if (auto test = inventory->GetItem(id("callforbackup"))) { inventory->RemoveItem(test); }
	}
	App::ConsolePrintF(to_string(Simulator::GetPlayerEmpire()->mArchetype).c_str());
	//App::ConsolePrintF(to_string(Simulator::GetPlayerEmpire()->mCultureSet).c_str());
	Simulator::GetPlayerEmpire()->mArchetype = Simulator::kArchetypePlayerDiplomat;*/
	
	auto argz = line.GetArguments(2);
	
	arg1 = argz[0] ;
	arg2 = argz[1] ;
	Sporepedia::ShopperRequest request(this);
	request.shopperID = id("GlobalTemplate");
	request.Show(request);
}

void vehicletest::OnShopperAccept(const ResourceKey& selection)
{
	App::ConsolePrintF(arg1.c_str());
	App::ConsolePrintF(arg2.c_str());
	using namespace Simulator;
	VehicleLocomotion vehicleloco{};
	VehiclePurpose vehiclepurp{};
	if (arg1 == "0") {vehicleloco = VehicleLocomotion(0); }
	if (arg1 == "1") {vehicleloco = VehicleLocomotion(1); }
	if (arg1 == "2") {vehicleloco = VehicleLocomotion(2); }


	if (arg2 == "0") {vehiclepurp = VehiclePurpose(0); }
	if (arg2 == "1") {vehiclepurp = VehiclePurpose(1); }
	if (arg2 == "2") {vehiclepurp = VehiclePurpose(2); }
	if (arg2 == "3") {vehiclepurp = VehiclePurpose(3); }
	
	Vector3 position = { 0, 0, 180 };
	cCity* city = PlanetModel.GetNearestCity(position);
	cVehiclePtr vehicle2 = city->SpawnVehicle(vehiclepurp, vehicleloco, selection, false);
}

const char* vehicletest::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "This cheat does something.";
	}
	else {
		return "vehicletest: Elaborate description of what this cheat does.";
	}
}
