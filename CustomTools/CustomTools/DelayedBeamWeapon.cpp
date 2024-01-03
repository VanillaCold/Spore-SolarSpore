#include "stdafx.h"
#include "DelayedBeamWeapon.h"

DelayedBeamWeapon::DelayedBeamWeapon()
{
	mFireTimer = new Simulator::cGonzagoTimer();
}


DelayedBeamWeapon::~DelayedBeamWeapon()
{
}

void DelayedBeamWeapon::OnMouseDown(Simulator::cSpaceToolData* pTool, const Vector3& playerPosition)
{

	if (!mFireTimer->IsRunning())
	{
		toReset = true;
		mFireTimer->Start();
	}
	else
	{
		if (mFireTimer->GetElapsed().LowPart > 2*100)
		return Simulator::cDefaultBeamTool::OnMouseDown(pTool, playerPosition);
	}
}



bool DelayedBeamWeapon::Update(Simulator::cSpaceToolData* pTool, bool showErrors, const char16_t** ppFailText)
{
	return Simulator::cToolStrategy::Update(pTool, showErrors, ppFailText);
}

bool DelayedBeamWeapon::WhileFiring(Simulator::cSpaceToolData* pTool, const Vector3& aimPoint, int unk)
{
	if (!mFireTimer->IsRunning())
	{
		App::ConsolePrintF("a");
		mFireTimer->Start();
	}
	App::ConsolePrintF("%i", mFireTimer->GetElapsed().LowPart);
	if (mFireTimer->GetElapsed().LowPart > 2*100)
	{
		Simulator::cDefaultBeamTool::WhileFiring(pTool, aimPoint, unk);
		if (toReset)
		{
			Simulator::cDefaultBeamTool::OnMouseDown(pTool, aimPoint);
			toReset = false;
		}
		return true;
	}
	return false;
}

bool DelayedBeamWeapon::OnMouseUp(Simulator::cSpaceToolData* pTool)
{
	if (toReset == false && mFireTimer->GetElapsed().LowPart > 2*100)
	{
		mFireTimer->Stop();
		toReset = true;
	}
	return Simulator::cDefaultBeamTool::OnMouseUp(pTool);
}
