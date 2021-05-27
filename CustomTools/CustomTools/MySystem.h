#pragma once

#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\Serialization.h>
#include "ChangeSpecies.h"
#include <vector>
#include <set>

#define MySystemPtr intrusive_ptr<MySystem>

///
/// In your dllmain Initialize method, add the system like this:
/// ModAPI::AddSimulatorStrategy(new MySystem(), MySystem::NOUN_ID);
///

class MySystem
	: public Simulator::cStrategy
{
public:
	bool rageModeOn = false;
	bool shieldon = false;
	bool capon = false;
	float capefficiencyamount = 0;
	float previousEnergy;
	float shieldprotectionamount = 0;
	int rageModeMultiplier = 1;
	float previousHealth;
	ResourceKey Selection = { 0,0,0 };
	ResourceKey defRes = { 0,0,0 };
	vector<uint32_t> deadplanets;
	static const uint32_t TYPE = id("SolarSpore::CustomToolSystem");
	static const uint32_t NOUN_ID = TYPE;

	int AddRef() override;
	int Release() override;
	void Initialize() override;
	void Dispose() override;
	const char* GetName() const override;
	virtual bool Write(Simulator::ISerializerStream* stream) override;
	virtual bool Read(Simulator::ISerializerStream* stream) override;
	void Update(int deltaTime, int deltaGameTime) override;
	virtual bool WriteToXML( Simulator::XmlSerializer* writexml);
	virtual void OnModeEntered(uint32_t previousModeID,
		uint32_t newModeID) override;

	//
	// You can add more methods here
	//
	static MySystem* Get();
	static Simulator::Attribute ATTRIBUTES[];

private:
	static MySystem* sInstance;
	// 
	// You can add members here
	//
};