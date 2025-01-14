#pragma once

#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cCombatSimulator.h>
#include "IStatusEffect.h"
#include <stack>

#define cSSStatusEffectManagerPtr intrusive_ptr<cSSStatusEffectManager>
#define SSStatusManager (cSSStatusEffectManager::Get())[0]

///
/// In your dllmain Initialize method, add the system like this:
/// ModAPI::AddSimulatorStrategy(new cSSStatusEffectManager(), cSSStatusEffectManager::NOUN_ID);
///

class cSSStatusEffectManager
	: public Simulator::cStrategy
{
public:



	static const uint32_t TYPE = id("CustomTools::cSSStatusEffectManager");
	static const uint32_t NOUN_ID = TYPE;

	int AddRef() override;
	int Release() override;
	void Initialize() override;
	void Dispose() override;
	const char* GetName() const override;
	bool Write(Simulator::ISerializerStream* stream) override;
	bool Read(Simulator::ISerializerStream* stream) override;
	void Update(int deltaTime, int deltaGameTime) override;

	virtual bool WriteToXML(Simulator::XmlSerializer* writexml) override;

	static cSSStatusEffectManager* Get();

	//
	// You can add more methods here
	//

	static Simulator::Attribute ATTRIBUTES[];
	map <uint32_t, IStatusEffect*> activeStatusEffects;
	std::stack<IStatusEffect*> mpEffectsToRemove;

	IStatusEffect* AddStatusEffect(cCombatantPtr, uint32_t instanceID, cCombatantPtr source = nullptr, cSpaceToolDataPtr pTool = nullptr);
	IStatusEffect* FindStatusEffect(cCombatantPtr pTarget, uint32_t effID);
	vector<IStatusEffect*> FindStatusEffectByClass(cCombatantPtr pTarget, uint32_t pClassID, uint32_t pWhitelistType);
	void RemoveStatusEffect(cCombatantPtr pTarget, uint32_t effID);
	void AddStatusType(IStatusEffect* type, uint32_t typeID);


private:
	//
	// You can add members here
	//
	map<uint32_t, IStatusEffect*> statusTypes;

	static cSSStatusEffectManager* sInstance;
};