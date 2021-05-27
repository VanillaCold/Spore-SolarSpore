#include "stdafx.h"
#include "SystemCount.h"

SystemCount::SystemCount()
{
}


SystemCount::~SystemCount()
{
}


void SystemCount::ParseLine(const ArgScript::Line& line)
{
	// This method is called when your cheat is invoked.
	// Put your cheat code here.
	Simulator::cStarRecord* star{};
	if (Simulator::IsSpaceGame() || Simulator::IsScenarioMode()) 
	{
		if (Simulator::IsScenarioMode) { star = StarManager.GetScenarioStar(); }
		else { star = StarManager.GetSol(); }
		if (star == StarManager.GetSol() || star->mKey != 0)
		{
			auto test = Simulator::GetPlayerEmpire()->mStars.size();
			App::ConsolePrintF("Number of systems: %u", test);
			App::ConsolePrintF("Number of allies: %u", Simulator::GetPlayerEmpire()->mAllies.size());
			App::ConsolePrintF("Number of enemies: %u", Simulator::GetPlayerEmpire()->mEnemies.size());
		}
		else { App::ConsolePrintF("This command only works in the Space Stage."); }
	}
	else { App::ConsolePrintF("This command only works in the Space Stage."); }
}

const char* SystemCount::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "This cheat does something.";
	}
	else {
		return "SystemCount: Elaborate description of what this cheat does.";
	}
}
