#include "stdafx.h"
#include "cStunEffect.h"

cStunEffect::cStunEffect()
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
}


cStunEffect::~cStunEffect()
{
}

void cStunEffect::Update(float deltaTime)
{
	IStatusEffect::Update(deltaTime);

	if (mpCombatant)
	{
		auto locoCombatant = object_cast<Simulator::cLocomotiveObject>(mpCombatant);
		if (locoCombatant)
		{
			locoCombatant->StopMovement();
			locoCombatant->Teleport(mCombatantPos, mCombatantRot);

			locoCombatant->MoveTo(mCombatantPos, 0, 0, false);
			locoCombatant->mbFixed = true;

			Simulator::cGameDataUFO* ufoObj = object_cast<Simulator::cGameDataUFO>(mpCombatant);
			if (ufoObj)
			{
				ufoObj->Teleport(mCombatantPos, mCombatantRot);

				ufoObj->mNextPosition = mCombatantPos;
				ufoObj->mPosition = mCombatantPos;
				ufoObj->Teleport(mCombatantPos, Math::Quaternion());
				ufoObj->MoveTo(mCombatantPos, 0);
			}
			mpCombatant->mpTarget = nullptr;
			
			if (ufoObj->mpNPCWeapon)
			{
				ufoObj->mpNPCWeapon->mRechargeTimer.Start();
			}

			if (mTimer <= 0)
			{
				locoCombatant->mbFixed = false;
			}
		}
		else
		{
			auto test = mpCombatant->ToSpatialObject();
			if (test)
			{
				test->Teleport(mCombatantPos, mCombatantRot);
				test->mbFixed = true;

				if (mTimer <= 0)
				{
					test->mbFixed = false;
				}
			}

		}
	}
}

void cStunEffect::Instantiate(uint32_t ID, cCombatantPtr combatant)
{
	IStatusEffect::Instantiate(ID, combatant);
}

IStatusEffect* cStunEffect::Clone()
{
	return new cStunEffect(*this);
}

void cStunEffect::EndEffect()
{
	IStatusEffect::EndEffect();
}

// You can extend this function to return any other types your class implements.
void* cStunEffect::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(IStatusEffect);
	CLASS_CAST(cStunEffect);
	return nullptr;
}
