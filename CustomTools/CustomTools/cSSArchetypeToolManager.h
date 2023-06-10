#pragma once

#include <Spore\BasicIncludes.h>

#define cSSArchetypeToolManagerPtr intrusive_ptr<cSSArchetypeToolManager>
#define SSConsequenceToolManager (cSSArchetypeToolManager::Get())

struct ArchetypeTool
{
	ArchetypeTool(Simulator::Archetypes targetArchetype, uint32_t tool, uint32_t evID = NULL)
	{
		toolID = tool;
		archetype = targetArchetype;
		eventID = evID;
	}
	Simulator::Archetypes archetype;
	uint32_t toolID;
	uint32_t eventID;
};

class cSSArchetypeToolManager 
	: public Object
	, public DefaultRefCounted
	, public App::IUpdatable
{

public:


	static const uint32_t TYPE = id("cSSArchetypeToolManager");
	
	cSSArchetypeToolManager();
	~cSSArchetypeToolManager();

	int AddRef() override;
	int Release() override;
	void Update() override;
	bool isDebug;

	void OnArchetypeUpdate();
	bool AddArchetypeTool(ArchetypeTool tool);

	void* Cast(uint32_t type) const override;


	static cSSArchetypeToolManager* Get();
	static cSSArchetypeToolManager* sInstance;
private:

	Simulator::Archetypes currentArchetype;
	vector<ArchetypeTool> toolInstances;
	bool givenTool;
};
