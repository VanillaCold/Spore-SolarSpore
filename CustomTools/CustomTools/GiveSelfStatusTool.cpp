#include "stdafx.h"
#include "GiveSelfStatusTool.h"


//using Simulator::cToolStrategy;
GiveSelfStatusTool::GiveSelfStatusTool()// : Simulator::cDefaultProjectileWeapon()
{

}

GiveSelfStatusTool::~GiveSelfStatusTool()
{
}

bool GiveSelfStatusTool::OnSelect(Simulator::cSpaceToolData* pTool)
{
	//auto orig = Simulator::cToggleToolStrategy::OnSelect(pTool);
	//if (orig)
	{
		if (Simulator::GetCurrentContext() == Simulator::SpaceContext::Planet)
		{
			uint32_t statusID;
			App::Property::GetUInt32(pTool->mpPropList.get(), id("SS-StatusEffect"), statusID);
			SSStatusManager.AddStatusEffect(object_cast<Simulator::cCombatant>(pTool->mpToolOwner), statusID, object_cast<Simulator::cCombatant>(pTool->mpToolOwner), pTool);
		}
		else
		{
			return false;
		}
	}
	return false;
}

bool GiveSelfStatusTool::OnDeselect(Simulator::cSpaceToolData* pTool)
{
	//Get the original return value.
	auto orig = Simulator::cToggleToolStrategy::OnDeselect(pTool);

	bool startTimer = Simulator::GetCurrentContext() == Simulator::SpaceContext::Planet;

	//If the tool owner exists,
	if (pTool->mpToolOwner)
	{
		if (!pTool->mbIsActive && !pTool->mbIsInUse)
		{
			startTimer = false;
		}

		//get the status effect ID.
		uint32_t statusID;
		App::Property::GetUInt32(pTool->mpPropList.get(), id("SS-StatusEffect"), statusID);
		//Set the tool to be not in use.
		pTool->mbIsInUse = false;
		pTool->mbIsActive = false;
		//If the status effect exists,
		IStatusEffect* statusEffect = SSStatusManager.FindStatusEffect(object_cast<Simulator::cCombatant>(pTool->mpToolOwner), statusID);
		if (statusEffect != nullptr && !statusEffect->mbIsFinished)
		{
			startTimer = false;
		}
		//and remove the status effect that corresponds to the ID.
		SSStatusManager.RemoveStatusEffect(object_cast<Simulator::cCombatant>(pTool->mpToolOwner), statusID);

		//Reset the recharge timer
		if (startTimer)
		{
			pTool->mRechargeTimer.Stop();
			pTool->mRechargeTimer.Start();
		}
		else
		{
			pTool->mRechargeTimer.Stop();
		}
	}
	return orig;
}

bool GiveSelfStatusTool::Update(Simulator::cSpaceToolData* pTool, bool showErrors, const char16_t** ppFailText)
{
	/*bool removeTimer = false;
	if (Simulator::GetCurrentContext() != Simulator::SpaceContext::Planet)
	{
		removeTimer = true;
	}*/

	uint32_t context = pTool->mContext;
	pTool->mContext = id("planet");
	bool a = Simulator::cToggleToolStrategy::Update(pTool,showErrors,ppFailText);
	pTool->mContext = context;
	return a;
}

// For internal use, do not modify.
int GiveSelfStatusTool::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int GiveSelfStatusTool::Release()
{
	return DefaultRefCounted::Release();
}

// You can extend this function to return any other types your class implements.
void* GiveSelfStatusTool::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	//CLASS_CAST(Simulator::cToolStrategy);
	CLASS_CAST(Simulator::cToolStrategy);
	CLASS_CAST(GiveSelfStatusTool);
	return nullptr;
}
