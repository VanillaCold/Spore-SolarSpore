#include "stdafx.h"
#include "cSSArchetypeToolManager.h"
#include <stdexcept>

cSSArchetypeToolManager::cSSArchetypeToolManager()
{
	sInstance = this; //set sInstance
	currentArchetype = Simulator::Archetypes::kArchetypeGrob; //initialise current archetype.
	givenTool = false;
	toolInstances = {};
	isDebug = false;
}


cSSArchetypeToolManager::~cSSArchetypeToolManager()
{
}

// For internal use, do not modify.
int cSSArchetypeToolManager::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int cSSArchetypeToolManager::Release()
{
	return DefaultRefCounted::Release();
}

void cSSArchetypeToolManager::Update()
{
	if (Simulator::IsSpaceGame())
	{
		cEmpirePtr empire = Simulator::GetPlayerEmpire();
		if (currentArchetype == Simulator::kArchetypeGrob)
		{
			currentArchetype = empire->mArchetype;
			givenTool = false;
			return;
		}
		else if (currentArchetype != empire->mArchetype)
		{
			OnArchetypeUpdate();
			return;
		}

		else
		{
			if (givenTool == false && (empire->mStars.size() >= 60 || isDebug))
			{
				givenTool = true;
				for each (ArchetypeTool tooltype in toolInstances)
				{
					if (tooltype.archetype == empire->mArchetype)
					{
						cSpaceToolDataPtr tool;
						if (ToolManager.LoadTool(ResourceKey(tooltype.toolID, 0, 0), tool))
						{
							SimulatorSpaceGame.GetPlayerInventory()->AddItem(tool.get());
							if (tooltype.eventID != NULL)
							{
								uint32_t event = UIEventLog.ShowEvent(tooltype.eventID, GroupIDs::SpaceEvents);
							}
						}
					}
				}
			}
		}
	}
	else
	{
		if (!Simulator::IsScenarioMode())
		{
			currentArchetype = Simulator::Archetypes::kArchetypeGrob; //reset archetype to default value
		}
	}
}



void cSSArchetypeToolManager::OnArchetypeUpdate()
{
	auto inventory = SimulatorSpaceGame.GetPlayerInventory();
	for each (ArchetypeTool archetype in toolInstances)
	{
		if (auto item = inventory->GetTool(ResourceKey(archetype.toolID,0,0)))
		{
			inventory->RemoveItem(item);
		}
	}
	currentArchetype = Simulator::GetPlayerEmpire()->mArchetype;
	givenTool = false;

}



bool cSSArchetypeToolManager::AddArchetypeTool(ArchetypeTool tool)
{
	if (PropManager.HasPropertyList(tool.toolID, GroupIDs::SpaceTools))
	{
		if (tool.archetype > 8 && tool.archetype < 19)
		{
			if (PropManager.HasPropertyList(tool.eventID, GroupIDs::SpaceEvents) || tool.eventID == NULL)
			{
				toolInstances.push_back(tool);
			}
			else
			{
				throw std::invalid_argument("The event ID is neither an actual file nor NULL, and so is invalid.");
				return false;
			}
		}
		else
		{
			throw std::invalid_argument("The archetype provided is invalid");
			return false;
		}
	}
	else
	{
		throw std::invalid_argument("The tool ID provided does not exist.");
		return false;
	}
	return false;
}

// You can extend this function to return any other types your class implements.
void* cSSArchetypeToolManager::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(cSSArchetypeToolManager);
	return nullptr;
}

cSSArchetypeToolManager* cSSArchetypeToolManager::Get()
{
	return sInstance;
}

cSSArchetypeToolManager* cSSArchetypeToolManager::sInstance;
