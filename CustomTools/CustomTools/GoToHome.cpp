#include "stdafx.h"
#include "GoToHome.h"

GoToHome::GoToHome()
{
}


GoToHome::~GoToHome()
{
}


void GoToHome::ParseLine(const ArgScript::Line& line)
{
	Simulator::SpaceTeleportTo(Simulator::GetPlayerEmpire()->mStars[0].get());
}

const char* GoToHome::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "This cheat does something.";
	}
	else {
		return "GoToHome: Elaborate description of what this cheat does.";
	}
}
