#pragma once

#include <Spore\BasicIncludes.h>

#define IStatusEffectPtr intrusive_ptr<IStatusEffect>

class IStatusEffect 
	: public Object
	, public DefaultRefCounted
{
public:
	static const uint32_t TYPE = id("IStatusEffect");
	static const uint32_t STRATEGY_ID = 0;
	
	IStatusEffect();

	virtual void Instantiate(uint32_t ID, cCombatantPtr combatant);

	~IStatusEffect();

	uint32_t mStatusType;

	bool mbIsExample;
	bool mbIsFinished;

	cCombatantPtr mpCombatant;
	Vector3 mCombatantPos;
	Math::Quaternion mCombatantRot;

	PropertyListPtr mpPropList;
	uint32_t mStatusEffectID;
	float mTimer;
	IVisualEffectPtr visualEffect;

	uint32_t mInternalID;

	virtual void Update(float deltaTime);
	virtual IStatusEffect* Clone() = 0;
	virtual void EndEffect();

	int AddRef() override;
	int Release() override;
	void* Cast(uint32_t type) const override;

};

/*	struct SSStatusEffect
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
	};*/