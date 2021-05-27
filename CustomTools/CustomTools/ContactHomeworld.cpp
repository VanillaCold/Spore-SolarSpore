#include "stdafx.h"
#include "ContactHomeworld.h"
#include <Spore\Simulator\SubSystem\CommManager.h>

ContactHomeworld::ContactHomeworld()
{
}


ContactHomeworld::~ContactHomeworld()
{
}


void ContactHomeworld::ParseLine(const ArgScript::Line& line)
{
	auto planet = Simulator::GetActivePlanetRecord();
	planet->field_10C = planet->field_10C;
	auto planet2 = Simulator::GetActivePlanet();
	planet2->field_10C = planet2->field_10C;
	//#auto temp = planet->mTemperatureScore;
	//auto atmo = planet->mAtmosphereScore;
	//auto spec = planet->GetStarRecord()->mEmpireID;
	////auto home = planet->mbHomeWorld;
	//auto tech = planet->mTechLevel;
	//auto flags = planet->mFlags;

	//planet->mFlags = StarManager.GetPlanetRecord(Simulator::GetPlayerEmpire()->mHomePlanet)->mFlags;
	//planet->mTemperatureScore = 0.5;
	//planet->mAtmosphereScore = 0.5;
	//planet->mbHomeWorld = 1;
	//planet->GetStarRecord()->mEmpireID = Simulator::GetPlayerEmpireID();
	//planet->mTechLevel = Simulator::TechLevel(5);

	auto PlayerEmpire = Simulator::GetPlayerEmpire();
	auto ev = CommManager.CreateSpaceCommEvent(Simulator::GetPlayerEmpireID(), PlayerEmpire->mHomePlanet, 0xC8FBF7D7, id("greetings"));
	CommManager.ShowCommEvent(ev);

	//planet->mTemperatureScore = temp;
	//planet->mAtmosphereScore = atmo;
	//planet->mbHomeWorld = home;
	//planet->GetStarRecord()->mEmpireID = spec;
	//planet->mTechLevel = tech;
	//planet->mFlags = flags;

	// This method is called when your cheat is invoked.
	// Put your cheat code here.
}

const char* ContactHomeworld::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "This cheat does something.";
	}
	else {
		return "ContactHomeworld: Elaborate description of what this cheat does.";
	}
}
