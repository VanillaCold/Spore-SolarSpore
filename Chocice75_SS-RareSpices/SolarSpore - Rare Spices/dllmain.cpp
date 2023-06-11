// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
//#include "SolarSpore_RareSpices.h"


void Initialize()
{
	
}

void Dispose()
{
	// This method is called when the game is closing
}

member_detour(SolarSpore_RareSpiceDetour, Simulator::cStarManager, void(Simulator::cStarRecord*, Simulator::StarRequestFilter*, bool))
{
	void detoured(Simulator::cStarRecord * pStarRecord, Simulator::StarRequestFilter * pFilter, bool useMaxPlanets)
	{
		original_function(this, pStarRecord, pFilter, useMaxPlanets); //Generate the planets before messing with them

		int planetIndex = GetRNG().RandomInt(pStarRecord->mPlanetCount); //Use the game's RNG function to randomly choose a planet

		PropertyListPtr propList; //Set up an empty property list
		PropManager.GetPropertyList(id("RareSpiceList"), id("SolarSporeConfig"), propList); //Find the rare spice property list, and store in the propList pointer
		ResourceKey* spiceArray; //Create empty ResourceKey array
		size_t spiceCount; //Set up empty size_t for count
		App::Property::GetArrayKey(propList.get(), id("rareSpiceIDs"), spiceCount, spiceArray); //Get the array of rare spices from the property list

		int spiceIndex = GetRNG().RandomInt(int(spiceCount)); //Use the RNG function to choose a random spice from the newly obtained array

		PropManager.GetPropertyList(spiceArray[spiceIndex].instanceID, GroupIDs::SpaceTrading, propList); //Get the spice's property list
		uint32_t spiceColour; 
		App::Property::GetUInt32(propList.get(), 0x058CBB75, spiceColour); //Find the spice's colour, and store in the spiceColour unsigned integer.

		cPlanetRecordPtr planetRec = pStarRecord->GetPlanetRecord(planetIndex); //Get the planet record of the target planet
		cPlanetPtr planet; //and set up a planetPtr too.
		StarManager.RecordToPlanet(planetRec.get(), planet); //Use StarManager to get the planet itself from its record

		planetRec->mSpiceGen = spiceArray[spiceIndex]; //Set the planet's spice to the previously chosen one
		planet->mSpaceEconomySpiceColor = spiceColour; //And change the colour of the planet's spice, too.

	}
};

void AttachDetours()
{
	//Attach the previously-made detour to the function that generates planets when a system is first loaded
	SolarSpore_RareSpiceDetour::attach(GetAddress(Simulator::cStarManager, GeneratePlanetsForStar)); 
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

