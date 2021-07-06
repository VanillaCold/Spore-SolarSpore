// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <Spore/Simulator/cGetOutOfUFOToolStrategy.h>
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

void Initialize()
{
	// This method is executed when the game starts, before the user interface is shown
	// Here you can do things such as:
	//  - Add new cheats
	//  - Add new simulator classes
	//  - Add new game modes
	//  - Add new space tools
	//  - Change materials
	CheatManager.AddCheat("spawnvehicle", new vehicletest());
	//CheatManager.AddCheat("changecaptain", new ChangeCaptain());
	CheatManager.AddCheat("setPlanetType", new SetPlanetType());
//	CheatManager.AddCheat("empireInfo", new SystemCount());
	CheatManager.AddCheat("contactHomeworld", new ContactHomeworld());

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

	SimulatorSystem.AddStrategy(new MySystem(), MySystem::NOUN_ID);
	SimulatorSystem.AddStrategy(new CustomArchetypeTools(), CustomArchetypeTools::NOUN_ID);
}

/*virtual_detour(thingytofixparts, Editors::cEditor, Editors::cEditor, void()) {
	void detoured()
	{
		if (this->mbInitSpine == true) { original_function(this); }
		else {
			return;
		}
	}
};*/

void Dispose()
{
	
	// This method is called when the game is closing
}

void AttachDetours()
{
	//thingytofixparts::attach(0xFEA598); //0x4A0520
	// Call the attach() method on any detours you want to add
	// For example: cViewer_SetRenderType_detour::attach(GetAddress(cViewer, SetRenderType));
}


// Generally, you don't need to touch any code here
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		ModAPI::AddPostInitFunction(Initialize);
		ModAPI::AddDisposeFunction(Dispose);

		PrepareDetours(hModule);
		AttachDetours();
		CommitDetours();
		break;

	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}

