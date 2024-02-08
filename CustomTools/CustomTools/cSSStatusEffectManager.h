#pragma once

#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cCombatSimulator.h>

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

	struct SSStatusEffect
	{
		uint32_t mStatusType;
		
		cCombatantPtr mpCombatant;
		Vector3 mCombatantPos;
		Math::Quaternion mCombatantRot;

		PropertyListPtr mpPropList;
		float mTimer;
		IVisualEffectPtr visualEffect;

		SSStatusEffect()
		{
			mStatusType = 0;
			mpCombatant = nullptr;
			mCombatantPos = Vector3();
			mCombatantRot = Quaternion();
			mpPropList = nullptr;
			mTimer = 0;
			visualEffect = nullptr;
		}
		
		SSStatusEffect(uint32_t ID, cCombatantPtr combatant)
		{
			mStatusType = 0;
			PropManager.GetPropertyList(ID, id("SS-StatusEffects"), mpPropList);
			App::Property::GetFloat(mpPropList.get(), id("statusEffectTimer"), mTimer);
			ResourceKey effectKey;

			App::Property::GetKey(mpPropList.get(), id("statusVisualEffect"), effectKey);
			if (EffectsManager.CreateVisualEffect(effectKey.instanceID, effectKey.groupID, visualEffect))
			{
				visualEffect->Start();
			}

			App::Property::GetUInt32(mpPropList.get(), id("statusEffectType"), mStatusType);
		
			mpCombatant = combatant;
			mCombatantPos = combatant->ToSpatialObject()->mPosition;
			mCombatantRot = combatant->ToSpatialObject()->mOrientation;
		}

		void Update(float deltaTime)
		{
			mTimer -= deltaTime;
			SporeDebugPrint("%f", deltaTime);
			visualEffect->SetSourceTransform(visualEffect->GetSourceTransform().SetOffset(mCombatantPos));

			switch (mStatusType)
			{
			case id("Stun"):
				mpCombatant->ToSpatialObject()->Teleport(mCombatantPos, mCombatantRot);
				break;

			case id("Damage"):
				float damage;
				App::Property::GetFloat(mpPropList.get(), id("statusDamage"), damage);
				
				if (mpCombatant->mHealthPoints >= damage)
				{
					mpCombatant->func18h(-(damage/ 1000)*deltaTime / 1000, 0, 0, Vector3(0, 0, 0), nullptr);
				}
				break;

			default:
				break;
			}
		}

		void End()
		{
			visualEffect->Stop();
			delete this;
		}
	};

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
	map < cCombatantPtr, SSStatusEffect*> activeStatusEffects;

	void AddStatusEffect(cCombatantPtr, uint32_t instanceID);


private:
	//
	// You can add members here
	//
	static cSSStatusEffectManager* sInstance;
};