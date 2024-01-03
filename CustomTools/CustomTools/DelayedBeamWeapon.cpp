#include "stdafx.h"
#include "DelayedBeamWeapon.h"

DelayedBeamWeapon::DelayedBeamWeapon()
{
	toReset = true;
	mFireTimer.SetMode(Clock::Mode::Milliseconds);
}


DelayedBeamWeapon::~DelayedBeamWeapon()
{
}

void DelayedBeamWeapon::OnMouseDown(Simulator::cSpaceToolData* pTool, const Vector3& playerPosition)
{

	if (!mFireTimer.IsRunning())
	{
		toReset = true;
		mFireTimer.Start();
	}
	else
	{
		if (mFireTimer.GetElapsedTime() > 1500)
		return Simulator::cDefaultBeamTool::OnMouseDown(pTool, playerPosition);
	}
}



bool DelayedBeamWeapon::Update(Simulator::cSpaceToolData* pTool, bool showErrors, const char16_t** ppFailText)
{
	return Simulator::cToolStrategy::Update(pTool, showErrors, ppFailText);
}

bool DelayedBeamWeapon::WhileFiring(Simulator::cSpaceToolData* pTool, const Vector3& aimPoint, int unk)
{
	if (!mFireTimer.IsRunning())
	{
		mFireTimer.SetMode(Clock::Mode::Milliseconds);
		toReset = true;
		mFireTimer.Start();
	}

	App::ConsolePrintF("%i", mFireTimer.GetElapsedTime());
	if (mFireTimer.GetElapsedTime() > 1500)
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
	mFireTimer.Reset();
	toReset = true;
	return Simulator::cDefaultBeamTool::OnMouseUp(pTool);
}
