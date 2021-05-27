#pragma once

#include <Spore\BasicIncludes.h>

#define CustomArchetypeToolsPtr intrusive_ptr<CustomArchetypeTools>

///
/// In your dllmain Initialize method, add the system like this:
/// ModAPI::AddSimulatorStrategy(new CustomArchetypeTools(), CustomArchetypeTools::NOUN_ID);
///

class CustomArchetypeTools
	: public Simulator::cStrategy
{
	bool giventool = false;
	bool tradertool = false;
	bool ecotool = false;
	bool wanderertool2 = false;
	bool warriortool = false;
	bool scientisttool = false;
	bool knighttool = false;
	bool shamantool = false;

public:
	static const uint32_t TYPE = id("CustomTools::CustomArchetypeTools");
	static const uint32_t NOUN_ID = TYPE;

	int AddRef() override;
	int Release() override;
	void Initialize() override;
	void Dispose() override;
	const char* GetName() const override;
	bool Write(Simulator::ISerializerStream* stream) override;
	bool Read(Simulator::ISerializerStream* stream) override;
	void Update(int deltaTime, int deltaGameTime) override;
	virtual bool WriteToXML(Simulator::XmlSerializer* writexml);
	virtual void OnModeEntered(uint32_t previousModeID,
		uint32_t newModeID) override;

	void purpleSpiceDye();
	void berserkerRage();
	void intergalacticDrive();
	void wanderAround();
	void lifeBurst();
	void acgenerator();
	void regalshield();
	void returnportal();


	//
	// You can add more methods here
	//

	static Simulator::Attribute ATTRIBUTES[];

private:
	//
	// You can add members here
	//
};