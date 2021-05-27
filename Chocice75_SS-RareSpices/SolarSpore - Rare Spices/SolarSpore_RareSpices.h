#pragma once

#include <Spore\BasicIncludes.h>

#define SolarSpore_RareSpicesPtr intrusive_ptr<SolarSpore_RareSpices>

///
/// In your dllmain Initialize method, add the system like this:
/// ModAPI::AddSimulatorStrategy(new SolarSpore_RareSpices(), SolarSpore_RareSpices::NOUN_ID);
///

class SolarSpore_RareSpices
	: public Simulator::cStrategy
{
public:
	static const uint32_t TYPE = id("SolarSpore_Rare_Spices::SolarSpore_RareSpices");
	static const uint32_t NOUN_ID = TYPE;

	int AddRef() override;
	int Release() override;
	void Initialize() override;
	void Dispose() override;
	const char* GetName() const override;
	bool Write(Simulator::ISerializerStream* stream) override;
	bool Read(Simulator::ISerializerStream* stream) override;
	void Update(int deltaTime, int deltaGameTime) override;

	//
	// You can add more methods here
	//
	virtual bool WriteToXML(Simulator::XmlSerializer* writexml);
	virtual void OnModeEntered(uint32_t previousModeID,
		uint32_t newModeID) override;

	static Simulator::Attribute ATTRIBUTES[];
	vector<uint32_t> generatedstars;

private:
	//
	// You can add members here
	//
};