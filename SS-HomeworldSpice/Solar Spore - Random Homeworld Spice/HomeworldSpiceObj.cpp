#include "stdafx.h"
#include "HomeworldSpiceObj.h"

HomeworldSpiceObj::HomeworldSpiceObj()
{
}


HomeworldSpiceObj::~HomeworldSpiceObj()
{
}

void HomeworldSpiceObj::Update()
{
	if (Simulator::IsCreatureGame() || Simulator::IsTribeGame() || Simulator::IsCivGame() || Simulator::IsSpaceGame())
	{
	Simulator::cPlanetRecord* planet{};
	if (!Simulator::IsSpaceGame()) { planet = Simulator::GetActivePlanetRecord(); }
	else if (Simulator::GetPlayerEmpire()){ planet = StarManager.GetPlanetRecord(Simulator::GetPlayerEmpire()->mHomePlanet); }
		vector<uint32_t> itemIDs;
		PropManager.GetPropertyListIDs(GroupIDs::SpaceTrading, itemIDs);
		PropertyListPtr propList;
		if (spiceIDs.empty())
		{
			for (int i = 0; i < itemIDs.size(); i++)
			{
				PropManager.GetPropertyList(itemIDs[i], GroupIDs::SpaceTrading, propList);
				uint32_t spicecolour;
				bool isHomeworldSpice;
				if (!App::Property::GetBool(propList.get(), id("SS-UseSpiceOnHomeworld"), isHomeworldSpice))
				{
					isHomeworldSpice = 1;
				}
				if ((App::Property::GetUInt32(propList.get(), 0x058CBB75, spicecolour)) && isHomeworldSpice == 1)
				{
					spiceIDs.push_back(itemIDs[i]);
				}
			}
		}
		else
		{
			if (planet != nullptr)
			{
				cPlanetPtr planet2;
				StarManager.RecordToPlanet(planet, planet2);
				//SporeDebugPrint(to_string(planet2->field_1C4).c_str());
				
				RandomNumberGenerator rng(planet->GetID().internalValue);
				rng.seed = planet->GetID().internalValue;
				int chosenSpice = rng.RandomInt(spiceIDs.size());
				planet->mSpiceGen.instanceID = spiceIDs[chosenSpice];
				
				PropManager.GetPropertyList(spiceIDs[chosenSpice], GroupIDs::SpaceTrading, propList);
				uint32_t spicecolour;
				App::Property::GetUInt32(propList.get(), 0x058CBB75, spicecolour);
				//SporeDebugPrint(to_string(spicecolour).c_str());
				planet2->mSpaceEconomySpiceColor = spicecolour;
			}
		}
	}
}

// For internal use, do not modify.
int HomeworldSpiceObj::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int HomeworldSpiceObj::Release()
{
	return DefaultRefCounted::Release();
}

// You can extend this function to return any other types your class implements.
void* HomeworldSpiceObj::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(HomeworldSpiceObj);
	return nullptr;
}
