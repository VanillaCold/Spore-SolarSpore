// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <Spore/Simulator/cGetOutOfUFOToolStrategy.h>
#include "SetupModStrategies.h"

#include <stdexcept>
#include "cSSArchetypeToolManager.h"
#include "cSSResearchManager.h"
#include "ResearchPointCaptionWinProc.h";
#include "OpenResearchMenu.h";
#include "TerraLaser.h"

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
	
	//virtual int TakeDamage(float damage, uint32_t attackerPoliticalID, int, const Vector3&, cCombatant * pAttacker);
	//Simulator::cCombatant::TakeDamage



	//SimulatorSystem.AddStrategy(new MySystem(), MySystem::NOUN_ID);
	//SimulatorSystem.AddStrategy(new CustomArchetypeTools(), CustomArchetypeTools::NOUN_ID);
	

	
	//SSConsequenceToolManager->AddArchetypeTool(ArchetypeTool(Simulator::Archetypes::kArchetypeBard, id("test")));
}

virtual_detour(CombatDetour, Simulator::cCreatureBase, Simulator::cCombatant, int(float, uint32_t, int, const Vector3&, Simulator::cCombatant*))
{
	int detoured(float damage, uint32_t attackerPoliticalID, int unk, const Vector3& pos, cCombatant * pAttacker)
	{
		SporeDebugPrint("a");
		if (Simulator::IsSpaceGame())
		{
			SporeDebugPrint("ab");
			if (pAttacker && pAttacker->GetPoliticalID() == TerraLaser::sTerraActive)
			{
				SporeDebugPrint("b");
				auto animal = object_cast<Simulator::cCreatureAnimal>(((Simulator::cCombatant*)this)->ToGameData());
				if (animal != nullptr)
				{
					SporeDebugPrint("c");
					if (!animal->mbIsDiseased)
					{
						SporeDebugPrint("d");
						return original_function(this, 0, attackerPoliticalID, unk, pos, pAttacker);
					}
				}
			}
		}

		return original_function(this, damage, attackerPoliticalID, unk, pos, pAttacker);
	}
};

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

member_detour(AddResearchMenuButton, UI::SpaceGameUI, void()) {
	void detoured()
	{
		//First, let the actual UI load in.
		original_function(this);

		//Get the property list of research, to confirm that research is enabled.
		PropertyListPtr list;
		if (PropManager.GetPropertyList(id("ss_enableresearch"), id("solarsporeconfig"), list))
		{
			//Find the parent window,
			IWindowPtr parentWindow = WindowManager.GetMainWindow()->FindWindowByID(0x07CE6631);
			//and initialise a new SPUI layout.
			UTFWin::UILayout* layout = new UTFWin::UILayout();

			//Load the research button
			layout->LoadByID(id("buttonspui"));
			//Set the parent of the research button SPUI.
			layout->SetParentWindow(parentWindow.get());
			//Add window procedures.
			layout->FindWindowByID(id("OpenResearchButton"))->AddWinProc(new OpenResearchMenu());
			layout->FindWindowByID(id("RPCaptionHolder"))->AddWinProc(new ResearchPointCaptionWinProc());
			//Find the OpenResearch window,
			auto main = layout->FindWindowByID(id("OpenResearch"));
			//and set the relative position.
			main->SetLocation(0, -35.0f);

			//Make the SPUI layout visible.
			layout->SetVisible(true);
		}
	}
};

//FUN_00c720a0
static_detour(SpiceGenDetour, float(float, float, float, bool, bool, bool, float, int, bool))
{
	float detoured(float rawIncome, float maxOutput, float extraFactor, bool isHomeWorld,
		bool useSuperpowerMultiplier, bool useStorageMultiplier, float finalFactor, int numCities, bool limitOutput)
	{
		//If the feature's enabled,
		if (PropManager.HasPropertyList(id("ss_logarithmiccolonies"), id("solarsporeconfig")))
		{
			//Calculate the new income using logarithms.
			float newIncome = 400 * log10f((rawIncome*numCities) / 40) / numCities;
			//And make sure it's non-negative, as log(0) is undefined and equates to negative infinity here.  
			newIncome = max(0.0f, newIncome);
			//Return the original function, using the new raw income.
			return original_function(newIncome, maxOutput, extraFactor, false, useSuperpowerMultiplier, useStorageMultiplier, finalFactor, numCities, limitOutput);
		}
		//If it's disabled, just return the original function.
		return original_function(rawIncome, maxOutput, extraFactor, isHomeWorld, useSuperpowerMultiplier, useStorageMultiplier, finalFactor, numCities, limitOutput);
	}
};

member_detour(OverrideRandomToolDetour, Simulator::cToolManager, bool(const ResourceKey&, cSpaceToolDataPtr&))
{
	bool detoured(const ResourceKey& toolId, cSpaceToolDataPtr& dst)
	{
		PropertyListPtr propList;
		if (PropManager.GetPropertyList(toolId.instanceID, GroupIDs::SpaceTools, propList))
		{
			bool isPlaceholder;

			if (App::Property::GetBool(propList.get(), id("SS_IsPlaceholderTool"), isPlaceholder)  && isPlaceholder)
			{
				size_t overrideCount;
				uint32_t* overrideIDs;
				App::Property::GetArrayUInt32(propList.get(), id("SS_ToolOverrides"),overrideCount,overrideIDs);
				int index = GetRNG().RandomInt(overrideCount);
				ResourceKey& newTool = ResourceKey(overrideIDs[index],0,0);
				return original_function(this, newTool, dst);
			}
			else
			{
				return original_function(this, toolId, dst);
			}
		}
		else
		{
			return original_function(this,toolId,dst);
		}
	}
};


void AttachDetours()
{
	OverrideRandomToolDetour::attach(GetAddress(Simulator::cToolManager, LoadTool));
	//thingytofixparts::attach(0xFEA598); //0x4A0520
	// Call the attach() method on any detours you want to add
	// For example: cViewer_SetRenderType_detour::attach(GetAddress(cViewer, SetRenderType));
	CombatDetour::attach(GetAddress(Simulator::cCombatant, TakeDamage));
	//Simulator::cPlanetRecord::CalculateDeltaSpiceProduction
	AddResearchMenuButton::attach(GetAddress(UI::SpaceGameUI, Load));
	SpiceGenDetour::attach(GetAddress(Simulator::cPlanetRecord, CalculateDeltaSpiceProduction)); //ModAPI::ChooseAddress(Address(0x00c71200),Address(0x00c720a0)));
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

