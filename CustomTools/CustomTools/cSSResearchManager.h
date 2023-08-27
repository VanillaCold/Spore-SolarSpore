#pragma once

#include <Spore\BasicIncludes.h>
#include <exception>
#include <stdexcept>

#define cSSResearchManagerPtr intrusive_ptr<cSSResearchManager>
#define SSResearchManager (cSSResearchManager::Get())[0]

///
/// In your dllmain Initialize method, add the system like this:
/// ModAPI::AddSimulatorStrategy(new cSSResearchManager(), cSSResearchManager::NOUN_ID);
///

struct ResearchType
{
public:
	ResearchType(uint32_t propID);
	ResearchType(PropertyListPtr propList, uint32_t toolID, vector<uint32_t> priorResearches, uint32_t requiredPoints, uint32_t researchID);
	
	bool operator==(const ResearchType other);
	bool operator!=(const ResearchType other);
	

	PropertyListPtr mpPropList;
	uint32_t mToolID;
	vector<uint32_t> mPriorResearches;
	uint32_t mRequiredPoints;
	uint32_t mResearchID;
};

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

	vector<ResearchType> mResearchTypes;

private:
	static cSSResearchManager* sInstance;
	bool SetupResearches();
	//
	// You can add members here
	//
};