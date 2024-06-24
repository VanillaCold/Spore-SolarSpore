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

//FUN_00c720a0
static_detour(SpiceGenDetour, float(float, float, float, float, float, float, float))
{
	float detoured(float rawIncome, float a2, float a3, float a4, float a5, float a6, float a7)
	{

		if (PropManager.HasPropertyList(id("ss_logarithmiccolonies"), id("solarsporeconfig")))
		{
			float newIncome = 400 * log10f((rawIncome) / 40);
			newIncome = max(0.0f, newIncome);


			// SporeDebugPrint("%f, %f, %f, %x, %x, %x, %x", newIncome, a2, a3, a4, a5, a6, a7);
			auto a = original_function(newIncome, a2, a3, a4, a5, a6, a7);
			return a;
		}
		return original_function(rawIncome, a2, a3, a4, a5, a6, a7);
	}
};


void AttachDetours()
{
	//thingytofixparts::attach(0xFEA598); //0x4A0520
	// Call the attach() method on any detours you want to add
	// For example: cViewer_SetRenderType_detour::attach(GetAddress(cViewer, SetRenderType));
	AddResearchMenuButton::attach(GetAddress(UI::SpaceGameUI, Load));
	SpiceGenDetour::attach(Address(0x00c720a0));
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

