#pragma once

#include <Spore\BasicIncludes.h>

#define cSSArchetypeWeaponSystemPtr intrusive_ptr<cSSArchetypeWeaponSystem>

///
/// In your dllmain Initialize method, add the system like this:
/// ModAPI::AddSimulatorStrategy(new cSSArchetypeWeaponSystem(), cSSArchetypeWeaponSystem::NOUN_ID);
///

struct ArchetypeWeapons
{
	PropertyListPtr mpPropList;
	vector<ResourceKey> mToolKeys;
	Simulator::Archetypes mArchetype;

	ArchetypeWeapons(ResourceKey propKey);
	ArchetypeWeapons();
};

class cSSArchetypeWeaponSystem
	: public Simulator::cStrategy
{
public:
	static const uint32_t TYPE = id("CustomTools::cSSArchetypeWeaponSystem");
	static const uint32_t NOUN_ID = TYPE;

	int AddRef() override;
	int Release() override;
	void Initialize() override;
	void Dispose() override;
	const char* GetName() const override;
	bool Write(Simulator::ISerializerStream* stream) override;
	bool Read(Simulator::ISerializerStream* stream) override;
	void Update(int deltaTime, int deltaGameTime) override;
	virtual void OnModeEntered(uint32_t previousModeID,
		uint32_t newModeID) override;
	bool WriteToXML(Simulator::XmlSerializer* writexml) override;

	void RefreshTools();
	//
	// You can add more methods here
	//

	static Simulator::Attribute ATTRIBUTES[];

private:
	bool mbIsFirstLaunch;
	map<Simulator::Archetypes, ArchetypeWeapons> mWeaponMappings;
	//
	// You can add members here
	//
};
