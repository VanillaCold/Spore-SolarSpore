// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <Spore/Simulator/cGetOutOfUFOToolStrategy.h>
#include "SetupModStrategies.h"

#include <stdexcept>
#include "cSSArchetypeToolManager.h"
#include "cSSResearchManager.h"

void Initialize()
{
	// This method is executed when the game starts, before the user interface is shown
	// Here you can do things such as:
	//  - Add new cheats
	//  - Add new simulator classes
	//  - Add new game modes
	//  - Add new space tools
	//  - Change materials
	cSSArchetypeToolManager* manager = new cSSArchetypeToolManager();
	App::AddUpdateFunction(manager);
	SetupModStrategies::SetupStrategies();



	//SimulatorSystem.AddStrategy(new MySystem(), MySystem::NOUN_ID);
	//SimulatorSystem.AddStrategy(new CustomArchetypeTools(), CustomArchetypeTools::NOUN_ID);
	

	
	//SSConsequenceToolManager->AddArchetypeTool(ArchetypeTool(Simulator::Archetypes::kArchetypeBard, id("test")));
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

