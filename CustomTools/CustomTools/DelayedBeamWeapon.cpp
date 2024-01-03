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

	if (!mFireTimer.IsRunning()) //If the timer's not running,
	{
		//start the timer.
		toReset = true;
		mFireTimer.Start();
	}
	else //Otherwise,
	{
		//if enough time has passed, then call the base function.
		if (mFireTimer.GetElapsedTime() > 1500)
		return Simulator::cDefaultBeamTool::OnMouseDown(pTool, playerPosition);
	}
}



bool DelayedBeamWeapon::Update(Simulator::cSpaceToolData* pTool, bool showErrors, const char16_t** ppFailText)
{
	//Just call the base function. maybe add more stuff here in future.
	return Simulator::cToolStrategy::Update(pTool, showErrors, ppFailText);
}

bool DelayedBeamWeapon::WhileFiring(Simulator::cSpaceToolData* pTool, const Vector3& aimPoint, int unk)
{
	//If the timer's not running,
	if (!mFireTimer.IsRunning())
	{
		//set the timer mode to milliseconds
		mFireTimer.SetMode(Clock::Mode::Milliseconds);
		//And then start the timer.
		toReset = true;
		mFireTimer.Start();
	}

	SporeDebugPrint("%i", mFireTimer.GetElapsedTime());
	//If the elapsed time is past 1.5 seconds,
	if (mFireTimer.GetElapsedTime() > 1500)
	{
		//Call the base function.
		Simulator::cDefaultBeamTool::WhileFiring(pTool, aimPoint, unk);
		if (toReset)
			//If it's the first time going past the 1.5 second limit,
		{
			//call the base function for OnMouseDown() as well.
			Simulator::cDefaultBeamTool::OnMouseDown(pTool, aimPoint);
			//And make sure we don't do this again.
			toReset = false;
		}
		//Return true to ensure that no weird shenanigans ensue.
		return true;
	}
	return false;
}

bool DelayedBeamWeapon::OnMouseUp(Simulator::cSpaceToolData* pTool)
{
	//Just stop the timer,
	mFireTimer.Reset();
	//set the value for if we've not yet gone past 1.5s before to true
	toReset = true;
	//and return the base function.
	return Simulator::cDefaultBeamTool::OnMouseUp(pTool);
}
