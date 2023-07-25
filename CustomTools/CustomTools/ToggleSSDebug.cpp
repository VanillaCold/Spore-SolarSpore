#include "stdafx.h"
#include "ToggleSSDebug.h"
#include "cSSArchetypeToolManager.h"
#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cBadgeManager.h>

ToggleSSDebug::ToggleSSDebug()
{
	isDebug = false;
}


ToggleSSDebug::~ToggleSSDebug()
{
}


void ToggleSSDebug::ParseLine(const ArgScript::Line& line)
{
	if (isDebug == false)
	{
		AchievementsManager.mIsCheater = true;
		BadgeManager.AddToBadgeProgress(Simulator::BadgeManagerEvent::Joker, 1);
		isDebug = true;
	}
	else
	{
		isDebug = false;
	}

	SSConsequenceToolManager.isDebug = isDebug;
	// This method is called when your cheat is invoked.
	// Put your cheat code here.
}

const char* ToggleSSDebug::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "This cheat does something.";
	}
	else {
		return "ToggleSSDebug: Elaborate description of what this cheat does.";
	}
}
