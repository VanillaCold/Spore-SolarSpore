#include "stdafx.h"
#include "SetupModStrategies.h"

#include "vehicletest.h"
#include "ToSol.h"
#include "SpawnVehicle.h"
#include "ChangeSpecies.h"
#include "EraseSpecies.h"
#include "MySystem.h"
#include "StaffofDeath.h"
#include "ConvertPlanet.h"
#include "GroxColony.h"
//#include "ChangeCaptain.h"
#include "SetPlanetType.h"
#include "infinitecolonies.h"
#include "PlanetDebuster.h"
//#include "SystemCount.h"
#include "RandomTool.h"
#include "ContactHomeworld.h"
#include "CustomArchetypeTools.h"
#include "WanderingPortal.h"
#include "LifeBurst.h"
#include "SpiceDye.h"
#include "BerserkerRage.h"
#include "IntergalacticDrive.h"
#include "Detente.h"
#include "Capacitor.h"
#include "RegalShield.h"
#include "AmmoCreator.h"
#include "ReturnPortal.h"
#include "StarKiller.h"
#include "cSSArchetypeToolManager.h"

void SetupModStrategies::SetupStrategies()
{
	//Add tools
	ToolManager.AddStrategy(new ToSol(), id("ToSol"));
	ToolManager.AddStrategy(new SpawnVehicle(), id("SpawnVehicle"));
	ToolManager.AddStrategy(new ChangeSpecies(), id("ChangeSpecies"));
	ToolManager.AddStrategy(new EraseSpecies(), id("EraseSpecies"));
	ToolManager.AddStrategy(new ConvertPlanet(), id("ConvertPlanet"));
	ToolManager.AddStrategy(new GroxColony(), id("GroxColony"));
	ToolManager.AddStrategy(new StaffofDeath(), id("StaffOfDeath"));
	ToolManager.AddStrategy(new infinitecolonies(), id("InfiniteColonies"));
	ToolManager.AddStrategy(new PlanetDebuster(), id("PlanetDebuster"));
	ToolManager.AddStrategy(new RandomTool(), id("RandomTool"));
	ToolManager.AddStrategy(new WanderingPortal(), id("WanderingPortal"));
	ToolManager.AddStrategy(new LifeBurst(), id("LifeBurst"));
	ToolManager.AddStrategy(new SpiceDye(), id("SpiceDye"));
	ToolManager.AddStrategy(new BerserkerRage(), id("BerserkerRage"));
	ToolManager.AddStrategy(new IntergalacticDrive(), id("IntergalacticDrive"));
	ToolManager.AddStrategy(new Detente(), id("Detente"));
	ToolManager.AddStrategy(new RegalShield(), id("RegalShield"));
	ToolManager.AddStrategy(new capacitor(), id("EnergyEfficiency"));
	ToolManager.AddStrategy(new AmmoCreator(), id("AmmoCreator"));
	ToolManager.AddStrategy(new ReturnPortal(), id("ReturnPortal"));
	ToolManager.AddStrategy(new StarKiller(), id("Starkiller"));


	//Add cheats
	CheatManager.AddCheat("spawnvehicle", new vehicletest());
	//CheatManager.AddCheat("changecaptain", new ChangeCaptain());
	CheatManager.AddCheat("setPlanetType", new SetPlanetType());
	//	CheatManager.AddCheat("empireInfo", new SystemCount());
	CheatManager.AddCheat("contactHomeworld", new ContactHomeworld());
	
	//Add archetype tools
	try
	{
		SSConsequenceToolManager->AddArchetypeTool(ArchetypeTool(
			Simulator::Archetypes::kArchetypePlayerShaman,
			id("purplespicedye")));

		SSConsequenceToolManager->AddArchetypeTool(ArchetypeTool(
			Simulator::Archetypes::kArchetypePlayerWarrior,
			id("ragemode")));

		SSConsequenceToolManager->AddArchetypeTool(ArchetypeTool(
			Simulator::Archetypes::kArchetypePlayerShaman,
			id("purplespicedie")));
	}
	catch (std::exception except)
	{
		const char* text = except.what();
		wstring report;
		report.assign_convert(text);
		MessageBox(NULL, report.c_str(), LPCWSTR(u"Error adding tool"), 0x00000010L);
	}
}
