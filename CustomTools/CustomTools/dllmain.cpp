// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <Spore/Simulator/cGetOutOfUFOToolStrategy.h>
#include "SetupModStrategies.h"

#include <stdexcept>
#include "cSSArchetypeToolManager.h"
#include "cSSResearchManager.h"
#include "ResearchPointCaptionWinProc.h";
#include "OpenResearchMenu.h";

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

member_detour(AddResearchMenuButton, UI::SpaceGameUI, void()) {
	void detoured()
	{
		original_function(this);
		PropertyListPtr list;
		if (PropManager.GetPropertyList(id("ss_enableresearch"), id("solarsporeconfig"), list))
		{
			IWindowPtr parentWindow = WindowManager.GetMainWindow()->FindWindowByID(0x07CE6631);
			UTFWin::UILayout* layout = new UTFWin::UILayout();

			layout->LoadByID(id("buttonspui"));
			layout->SetParentWindow(parentWindow.get());
			layout->FindWindowByID(id("OpenResearchButton"))->AddWinProc(new OpenResearchMenu());
			layout->FindWindowByID(id("RPCaptionHolder"))->AddWinProc(new ResearchPointCaptionWinProc());
			auto main = layout->FindWindowByID(id("OpenResearch"));
			main->SetLocation(0, -35.0f);

			layout->SetVisible(true);
		}
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
	AddResearchMenuButton::attach(GetAddress(UI::SpaceGameUI, Load));
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

