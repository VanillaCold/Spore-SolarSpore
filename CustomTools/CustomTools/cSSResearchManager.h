#pragma once

#include <Spore\BasicIncludes.h>

#define cSSResearchManagerPtr intrusive_ptr<cSSResearchManager>
#define SSResearchManager (cSSResearchManager::Get())[0]

///
/// In your dllmain Initialize method, add the system like this:
/// ModAPI::AddSimulatorStrategy(new cSSResearchManager(), cSSResearchManager::NOUN_ID);
///

class cSSResearchManager
	: public Simulator::cStrategy
{
public:
	static const uint32_t TYPE = id("CustomTools::cSSResearchManager");
	static const uint32_t NOUN_ID = TYPE;

	int AddRef() override;
	int Release() override;
	void Initialize() override;
	void Dispose() override;
	const char* GetName() const override;
	bool Write(Simulator::ISerializerStream* stream) override;
	bool Read(Simulator::ISerializerStream* stream) override;
	void Update(int deltaTime, int deltaGameTime) override;
	bool WriteToXML(Simulator::XmlSerializer* writexml) override;

	//
	// You can add more methods here
	//

	static Simulator::Attribute ATTRIBUTES[];
	static cSSResearchManager* Get();

private:
	static cSSResearchManager* sInstance;
	//
	// You can add members here
	//
};