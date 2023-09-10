#pragma once

#include <Spore\BasicIncludes.h>
#include <exception>
#include <stdexcept>
#include <Spore\App\cJob.h>
#include <Spore\App\JobManager.h>

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
	ResearchType();
	//ResearchType(PropertyListPtr propList, uint32_t toolID, vector<uint32_t> priorResearches, uint32_t requiredPoints, uint32_t researchID);
	
	const bool operator==(const ResearchType other);
	const bool operator!=(const ResearchType other);
	explicit operator bool() const;
	

	PropertyListPtr mpPropList;
	uint32_t mToolID;
	vector<uint32_t> mPriorResearches;
	uint32_t mRequiredPoints;
	uint32_t mResearchID;
	LocalizedString mResearchTitle;
	LocalizedString mResearchDescription;
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
	bool CheckResearchExists(uint32_t resID);
	bool HasResearched(uint32_t resID);
	bool ResearchItem(uint32_t resID, string& outError); //outError is the output if it returns false
	ResearchType& GetResearch(uint32_t resID);
	
	vector<ResearchType> mResearchTypes;
	float mResearchPoints;

	bool OpenResearchUI(bool animation = true);
	bool CloseResearchUI(bool animation = true);

	void LoadUIItems();

	vector<UTFWin::IWindow*> mpItemUIs;

private:
	static cSSResearchManager* sInstance;
	bool SetupResearches();

	UTFWin::UILayout* mpUIlayout;
	UTFWin::IWindow* mpPointsCaption;
	float mWindowOffset;
	
	//map<uint32_t, uint32_t> mResearchTools; // <Research, tool> Research IDs that correspond with each tool.
	
	
	//
	// You can add members here
	//
};