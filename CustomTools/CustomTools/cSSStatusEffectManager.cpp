#include "stdafx.h"
#include "cSSStatusEffectManager.h"

/// AUTOGENERATED METHODS ///

int cSSStatusEffectManager::AddRef() {
	return Simulator::cStrategy::AddRef();
}
int cSSStatusEffectManager::Release() {
	return Simulator::cStrategy::Release();
}

const char* cSSStatusEffectManager::GetName() const {
	return "CustomTools::cSSStatusEffectManager";
}

bool cSSStatusEffectManager::Write(Simulator::ISerializerStream* stream)
{
	return Simulator::ClassSerializer(this, ATTRIBUTES).Write(stream);
}
bool cSSStatusEffectManager::Read(Simulator::ISerializerStream* stream)
{
	return Simulator::ClassSerializer(this, ATTRIBUTES).Read(stream);
}

/// END OF AUTOGENERATED METHODS ///
////////////////////////////////////

Simulator::Attribute cSSStatusEffectManager::ATTRIBUTES[] = {
	// Add more attributes here
	// This one must always be at the end
	Simulator::Attribute()
};

void cSSStatusEffectManager::Initialize() {
	sInstance = this;
	activeStatusEffects = map < uint32_t, IStatusEffect*> ();
}

void cSSStatusEffectManager::Dispose() {
	
}

void cSSStatusEffectManager::Update(int deltaTime, int deltaGameTime) {
	vector<uint32_t> invalidStatuses{};
	for(auto i = activeStatusEffects.begin(); i != activeStatusEffects.end();i++)
	{
		auto statusID = i.mpNode->mValue.first;
		auto status = i.mpNode->mValue.second;
		if (status == nullptr)
		{
			SporeDebugPrint("well the effect died.");
			invalidStatuses.push_back(statusID);
		}

		else if (status->mbIsFinished)
		{
			SporeDebugPrint("wooeeoo");
			invalidStatuses.push_back(statusID);
		}
		else
		{
			status->Update(deltaGameTime / 1000.0f);
		}
	}

	for each (uint32_t removal in invalidStatuses)
	{
		if (activeStatusEffects[removal] != nullptr)
		{
			activeStatusEffects[removal]->EndEffect();
		}
		activeStatusEffects.erase(removal);
	}
}

bool cSSStatusEffectManager::WriteToXML(Simulator::XmlSerializer* writexml)
{
	return false;
}

cSSStatusEffectManager* cSSStatusEffectManager::Get()
{
	return sInstance;
}

void cSSStatusEffectManager::AddStatusEffect(cCombatantPtr combatant, uint32_t instanceID)
{
	PropertyListPtr propList;
	PropManager.GetPropertyList(instanceID, id("SS-StatusEffects"), propList);
	uint32_t statusType;
	App::Property::GetUInt32(propList.get(), id("statusEffectType"), statusType);
	
	ModAPI::Log("Adding status effect with strat. ID %x", statusType);

	if (statusTypes[statusType] != nullptr)
	{
		ModAPI::Log("Strategy does indeed exist");

		for each (auto effect in activeStatusEffects)
		{
			if (effect.second->mpCombatant == combatant && instanceID == effect.second->mStatusEffectID)
			{
				effect.second->mTimer = 0;
				App::Property::GetFloat(propList.get(), id("statusEffectTimer"), effect.second->mTimer);
				return;
			}
		}

		IStatusEffect* status = statusTypes[statusType]->Clone();
		status->Instantiate(instanceID, combatant);

		uint32_t index = 0;
		
		//I have no idea why this works because everything else I tried made the status object despawn.
		for each (auto thingy in activeStatusEffects)
		{
			index++;
		}


		status->mInternalID = index;
		SporeDebugPrint("%x", index);
		activeStatusEffects.emplace(status->mInternalID, status);
	}
}

void cSSStatusEffectManager::AddStatusType(IStatusEffect* type, uint32_t typeID)
{
	ModAPI::Log("Added strategy with ID %x", typeID);
	type->mbIsExample = true;
	statusTypes.emplace(typeID, type);
}

cSSStatusEffectManager* cSSStatusEffectManager::sInstance;