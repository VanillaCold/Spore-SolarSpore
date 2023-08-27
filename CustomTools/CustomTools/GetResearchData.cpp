#include "stdafx.h"
#include "GetResearchData.h"
#include "cSSResearchManager.h"

GetResearchData::GetResearchData()
{
	CheatManager.AddCheat("SSGetResearchData", this);
}


GetResearchData::~GetResearchData()
{
}


void GetResearchData::ParseLine(const ArgScript::Line& line)
{
	auto arg = line.GetArguments(1);
	uint32_t id = mpFormatParser->ParseUInt(arg[0]);
	auto rTypes = SSResearchManager.mResearchTypes;
	int index = -1;

	for(int i = 0; i<rTypes.size(); i++)
	{
		auto type = rTypes[i];
		if (type.mResearchID == id)
		{
			index = i;
			break;
		}
	}

	if (index != -1)
	{
		ResearchType research(id);
		App::ConsolePrintF("Research type is %x, tool given is %x, points required is %u", research.mResearchID, research.mToolID, research.mRequiredPoints);
	}
}

const char* GetResearchData::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "This cheat does something.";
	}
	else {
		return "GetResearchData: Elaborate description of what this cheat does.";
	}
}
