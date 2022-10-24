// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
//#include "SolarSpore_RareSpices.h"


void Initialize()
{
	//SimulatorSystem.AddStrategy(new SolarSpore_RareSpices, SolarSpore_RareSpices::NOUN_ID);
	// 
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

member_detour(SolarSpore_RareSpiceDetour, Simulator::cStarManager, void(Simulator::cStarRecord*, Simulator::StarRequestFilter*, bool))
{
	void detoured(Simulator::cStarRecord * pStarRecord, Simulator::StarRequestFilter * pFilter, bool useMaxPlanets)
	{
		original_function(this, pStarRecord, pFilter, useMaxPlanets);

		int planetIndex = GetRNG().RandomInt(pStarRecord->mPlanetCount);

		PropertyListPtr propList;
		//vector<uint32_t> props;
		PropManager.GetPropertyList(id("RareSpiceList"), id("SolarSporeConfig"), propList);
		ResourceKey* spiceArray;
		size_t spiceCount;
		App::Property::GetArrayKey(propList.get(), id("rareSpiceIDs"), spiceCount, spiceArray);

		int spiceIndex = GetRNG().RandomInt(int(spiceCount));

		PropManager.GetPropertyList(spiceArray[spiceIndex].instanceID, GroupIDs::SpaceTrading, propList);
		uint32_t spiceColour;
		App::Property::GetUInt32(propList.get(), 0x058CBB75, spiceColour);

		cPlanetRecordPtr planetRec = pStarRecord->GetPlanetRecord(planetIndex);
		cPlanetPtr planet;
		StarManager.RecordToPlanet(planetRec.get(), planet);

		planetRec->mSpiceGen = spiceArray[spiceIndex];
		planet->mSpaceEconomySpiceColor = spiceColour;

	}
};

void AttachDetours()
{
	SolarSpore_RareSpiceDetour::attach(GetAddress(Simulator::cStarManager, GeneratePlanetsForStar));
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

