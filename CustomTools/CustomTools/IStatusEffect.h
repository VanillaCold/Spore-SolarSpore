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

	virtual void Instantiate(uint32_t ID, cCombatantPtr combatant, cCombatantPtr source = nullptr);

	~IStatusEffect();

	uint32_t mStatusType;

	bool mbIsExample;
	bool mbIsFinished;

	cCombatantPtr mpSource;
	cCombatantPtr mpCombatant;
	cSpaceToolDataPtr mpToolObject;
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