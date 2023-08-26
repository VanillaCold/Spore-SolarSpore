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
	ResearchType(uint32_t propID)
	{
		if (PropManager.GetPropertyList(propID, id("SS-research"), mpPropList))
		{
			App::Property::GetUInt32(mpPropList.get(), id("ResearchTool"), mToolID);

			size_t count;
			uint32_t* ids;
			App::Property::GetArrayUInt32(mpPropList.get(), id("ResearchDependancies"), count, ids);
			if (count != 0)
			{
				for (int i = 0; i < count; i++)
				{
					mPriorResearches.push_back(ids[i]);
				}
			}

			if (!App::Property::GetUInt32(mpPropList.get(), id("ResearchPointsRequired"), mRequiredPoints))
			{
				string error = "Research property list " + to_string(propID) + " has no required point count!";
				throw std::invalid_argument(error.c_str());
			}
		}
		else
		{
			string error = "Research property list "+to_string(propID)+" is not valid!";
			throw std::invalid_argument(error.c_str());
		}
	}

	PropertyListPtr mpPropList;
	uint32_t mToolID;
	vector<uint32_t> mPriorResearches;
	uint32_t mRequiredPoints;
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

	vector<ResearchType> researches;

private:
	static cSSResearchManager* sInstance;
	//
	// You can add members here
	//
};