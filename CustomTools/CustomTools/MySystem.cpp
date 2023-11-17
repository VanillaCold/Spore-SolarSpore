#include "stdafx.h"
#include "MySystem.h"
#include <Spore/Simulator/Serialization.h>
#include "cSSResearchManager.h"

MySystem* MySystem::sInstance;

/// AUTOGENERATED METHODS ///

int MySystem::AddRef() {
	return Simulator::cStrategy::AddRef();
}
int MySystem::Release() {
	return Simulator::cStrategy::Release();
}

const char* MySystem::GetName() const {
	return "CustomTools::SavingSpecies+PermaDeterraform";
}

bool MySystem::Write(Simulator::ISerializerStream* stream)
{
	return Simulator::ClassSerializer(this, ATTRIBUTES).Write(stream);
}
bool MySystem::Read(Simulator::ISerializerStream* stream)
{
	return Simulator::ClassSerializer(this, ATTRIBUTES).Read(stream);
}

/// END OF AUTOGENERATED METHODS ///
////////////////////////////////////

Simulator::Attribute MySystem::ATTRIBUTES[] = {
	// Add more attributes here
	// This one must always be at the end
	//SimAttribute(MySystem,Selection,1),
	//SimAttribute(MySystem,deadplanets,2),
	Simulator::Attribute()
};

void MySystem::Initialize() {
	deadplanets.begin();
	sInstance = this;
}

void MySystem::Dispose() {
	sInstance = nullptr;
	App::ConsolePrintF("Simulator should be over now. >:)");
}

void MySystem::Update(int deltaTime, int deltaGameTime) {

	if (Simulator::IsSpaceGame() == 1) {
		auto inventory = SimulatorSpaceGame.GetPlayerInventory();
		auto first = deadplanets.begin();
		if (deadplanets.size() > 0)
		{
			for (int i = 0; i < deadplanets.size(); i += 1)
			{
				auto record = StarManager.GetPlanetRecord(deadplanets[i]);
				/*if (i > 0) {std::advance(first, 1); }
				auto planet = *first;*/
				record->mAtmosphereScore = -0.25;
				if (record->mTechLevel == Simulator::TechLevel(1)) { record->mTechLevel = Simulator::TechLevel(0); }
			}
		}
		//std::copy(deadplanets.begin(), deadplanets.end(), std::back_inserter(dp_vec));
		if (Selection != ResourceKey{ 0,0,0 }) {
			if (Simulator::IsSpaceGame()) {
				if (SpeciesManager.GetSpeciesProfile(Selection)) {
					;
					auto SelectedSpecies = SpeciesManager.GetSpeciesProfile(Selection);
					GetPlayerEmpire()->SetSpeciesProfile(SelectedSpecies);
				}
				else {
					Selection = { 0,0,0 };
				}
			}
		}

		if (rageModeOn && inventory->mpActiveTool != nullptr)
		{

			//App::ConsolePrintF("Current damage multiplier: %f", inventory->mpActiveTool->mDamageMultiplier);
			inventory->mpActiveTool->mDamageMultiplier = rageModeMultiplier;
		}


		if (shieldon)
		{
			auto ufo = GetPlayerUFO();
			if (previousHealth == 0)
			{
				previousHealth = GetPlayerUFO()->mHealthPoints;
			}

			if (ufo->mHealthPoints < previousHealth && ufo->mHealthPoints > 0)
			{
				ufo->SetHealthPoints(ufo->mHealthPoints + ((previousHealth - ufo->mHealthPoints) * shieldprotectionamount));
			}
			previousHealth = ufo->mHealthPoints;
		}
		if (capon)
		{
			auto ufo = GetPlayerUFO();
			if (previousEnergy == 0 && ufo->mEnergy > 0)
			{
				previousEnergy = GetPlayerUFO()->mEnergy;
			}

			if (ufo->mEnergy < previousEnergy && ufo->mEnergy > 0)
			{
				ufo->mEnergy += ((previousEnergy - ufo->mEnergy) * capefficiencyamount);
			}
			previousEnergy = ufo->mEnergy;
		}
	}
}

bool MySystem::WriteToXML(Simulator::XmlSerializer* writexml)
{
	
	return false;
}

void MySystem::OnModeEntered(uint32_t previousModeID, uint32_t newModeID)
{
	/*if (!Simulator::IsSpaceGame() && !Simulator::IsLoadingGameMode())
	{
		deadplanets.clear();
	}*/
}

MySystem* MySystem::Get()
{
	return sInstance;
}
