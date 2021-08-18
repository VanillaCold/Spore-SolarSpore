// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <Spore\Swarm\cSwarmManager.h>
using namespace Swarm;

void Initialize()
{
	// This method is executed when the game starts, before the user interface is shown
	// Here you can do things such as:
	//  - Add new cheats
	//  - Add new simulator classes
	//  - Add new game modes
	//  - Add new space tools
	//  - Change materials
}

void Dispose()
{
	// This method is called when the game is closing
}

member_detour(RedirectEffectDetour, Swarm::cSwarmManager, int(uint32_t, uint32_t)) { //this detour's code was made by Mrs. White
	int detoured(uint32_t instanceID, uint32_t groupID) {
		// groupID appears to be always 0
		//SporeDebugPrint("Loading effect: %X from %X", instanceID, groupID);
		if (instanceID == 0x03D6EF40) {
			return original_function(this, 0x03D6EF7B, groupID); //0x096fa3a5
		}
		return original_function(this, instanceID, groupID);
	}
};

void AttachDetours()
{
	RedirectEffectDetour::attach(GetAddress(Swarm::cSwarmManager, GetDirectoryAndEffectIndex));
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

