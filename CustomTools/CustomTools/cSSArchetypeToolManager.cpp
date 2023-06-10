#include "stdafx.h"
#include "cSSArchetypeToolManager.h"
#include <stdexcept>

cSSArchetypeToolManager::cSSArchetypeToolManager()
{
	sInstance = this; //set sInstance
	currentArchetype = Simulator::Archetypes::kArchetypeGrob; //initialise current archetype.
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
}



void cSSArchetypeToolManager::OnArchetypeUpdate(Simulator::Archetypes oldArchetype)
{
}



bool cSSArchetypeToolManager::AddArchetypeTool(ArchetypeTool tool)
{
	if (PropManager.HasPropertyList(tool.toolID, GroupIDs::SpaceTools))
	{

	}
	else
	{
		throw std::invalid_argument("The tool provided does not exist.");
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
