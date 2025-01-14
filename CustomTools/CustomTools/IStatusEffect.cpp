#include "stdafx.h"
#include "IStatusEffect.h"

IStatusEffect::IStatusEffect()
{
	mbIsExample = true;
	mStatusType = 0;
	mpCombatant = nullptr;
	mCombatantPos = Vector3();
	mCombatantRot = Quaternion();
	mpPropList = nullptr;
	mTimer = 0;
	visualEffect = nullptr;
	mbIsFinished = false;
	mStatusEffectID = 0;
	mInternalID = 0;
	mpSource = nullptr;
}

void IStatusEffect::Instantiate(uint32_t ID, cCombatantPtr combatant, cCombatantPtr source)
{

	mbIsExample = false;
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


	if (combatant == nullptr)
	{
		mbIsFinished = true;
		return;
	}
	
	mCombatantPos = combatant->ToSpatialObject()->mPosition;
	mCombatantRot = combatant->ToSpatialObject()->mOrientation;

	mStatusEffectID = ID;
	mbIsFinished = false;
	mpSource = source;
}


IStatusEffect::~IStatusEffect()
{
}

void IStatusEffect::Update(float deltaTime)
{
	mTimer -= deltaTime;
	//SporeDebugPrint("%f", deltaTime);
	if (visualEffect)
	{
		visualEffect->SetSourceTransform(visualEffect->GetSourceTransform().SetOffset(mpCombatant->ToSpatialObject()->mPosition));
	}

	if (mTimer <= 0 || !mpCombatant || mpCombatant->ToGameData()->mbIsDestroyed)
	{
		mbIsFinished = true;
	}
}

void IStatusEffect::EndEffect()
{
	if (visualEffect)
	{
		visualEffect->Stop(0);
	}
	delete this;
}

// For internal use, do not modify.
int IStatusEffect::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int IStatusEffect::Release()
{
	return DefaultRefCounted::Release();
}

// You can extend this function to return any other types your class implements.
void* IStatusEffect::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(IStatusEffect);
	return nullptr;
}
