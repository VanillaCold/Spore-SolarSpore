#include "stdafx.h"
#include "GetResearchData.h"
#include "cSSResearchManager.h"

GetResearchData::GetResearchData()
{
	CheatManager.AddCheat("ssDevResearch", this);
}


GetResearchData::~GetResearchData()
{
}


void GetResearchData::ParseLine(const ArgScript::Line& line)
{
	if (auto arg = line.GetOption("data",1))
	{
		//auto arg = line.GetArguments(1);
		uint32_t id = mpFormatParser->ParseUInt(arg[0]);
		if (SSResearchManager.CheckResearchExists(id))
		{
			ResearchType research(id);
			App::ConsolePrintF("Research type is %x, tool given is %x, points required is %u", research.mResearchID, research.mToolID, research.mRequiredPoints);
		}
		return;
	}

	if (auto arg = line.GetOption("research",1))
	{
		//auto arg = line.GetArguments(1);
		uint32_t id = mpFormatParser->ParseUInt(arg[0]);
		if (SSResearchManager.CheckResearchExists(id))
		{
			string outError;
			SSResearchManager.ResearchItem(id, outError);
			App::ConsolePrintF(outError.c_str());
		}
		return;
	}

	if (auto arg = line.GetOption("check",1))
	{
		uint32_t id = mpFormatParser->ParseUInt(arg[0]);
		if (SSResearchManager.CheckResearchExists(id))
		{
			if (SSResearchManager.HasResearched(id))
			{
				App::ConsolePrintF("true");
			}
			else
			{
				App::ConsolePrintF("false");
			}
		}
		return;
	}

	if (auto arg = line.GetOption("setPoints", 1))
	{
		uint32_t points = mpFormatParser->ParseUInt(arg[0]);
		SSResearchManager.mResearchPoints = points;
		return;
	}

	if (line.HasFlag("getPoints"))
	{
		App::ConsolePrintF(to_string(SSResearchManager.mResearchPoints).c_str());
		return;
	}

	if (line.HasFlag("OpenUI"))
	{
		SSResearchManager.OpenResearchUI();
	}
	if (line.HasFlag("CloseUI"))
	{
		SSResearchManager.CloseResearchUI();
	}
}

const char* GetResearchData::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "This cheat does something.";
	}
	else {
		return "options are:\ndata\nresearch\ncheck\nsetPoints\ngetPoints";
	}
}
