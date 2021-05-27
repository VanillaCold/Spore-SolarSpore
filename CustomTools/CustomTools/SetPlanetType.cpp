#include "stdafx.h"
#include "SetPlanetType.h"

SetPlanetType::SetPlanetType()
{
}


SetPlanetType::~SetPlanetType()
{
}


void SetPlanetType::ParseLine(const ArgScript::Line& line)
{
	// This method is called when your cheat is invoked.
	// Put your cheat code here.
	using namespace Simulator;
	//17451
	auto args = line.GetArguments(3);
	
	App::ConsolePrintF(to_string(GetActivePlanetRecord()->mType).c_str());
	//PlanetIndex Index = mpFormatParser->ParseUInt(args[0]);
	App::ConsolePrintF(to_string(GetActivePlanetRecord()->mFlags).c_str());
	App::ConsolePrintF(to_string(int(GetActivePlanetRecord()->mTechLevel)).c_str());
	//cPlanetRecord* Record = StarManager.GetPlanetRecord(Index);
	GetActivePlanetRecord()->mType = mpFormatParser->ParseInt(args[0]);
	GetActivePlanetRecord()->mFlags = mpFormatParser->ParseInt(args[1]);
	GetActivePlanetRecord()->mTechLevel = Simulator::TechLevel(mpFormatParser->ParseInt(args[2]));
}

const char* SetPlanetType::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "This cheat does something.";
	}
	else {
		return "SetPlanetType: Elaborate description of what this cheat does.";
	}
}
