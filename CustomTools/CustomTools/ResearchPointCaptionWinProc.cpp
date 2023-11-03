#include "stdafx.h"
#include "ResearchPointCaptionWinProc.h"
#include "cSSResearchManager.h"

ResearchPointCaptionWinProc::ResearchPointCaptionWinProc()
{
}


ResearchPointCaptionWinProc::~ResearchPointCaptionWinProc()
{
}

// For internal use, do not modify.
int ResearchPointCaptionWinProc::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int ResearchPointCaptionWinProc::Release()
{
	return DefaultRefCounted::Release();
}

// You can extend this function to return any other types your class implements.
void* ResearchPointCaptionWinProc::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(IWinProc);
	CLASS_CAST(ResearchPointCaptionWinProc);
	return nullptr;
}

// This method returns a combinations of values in UTFWin::EventFlags.
// The combination determines what types of events (messages) this window procedure receives.
// By default, it receives mouse/keyboard input and advanced messages.
int ResearchPointCaptionWinProc::GetEventFlags() const
{
	return kEventFlagBasicInput | kEventFlagAdvanced | kEventFlagUpdate;
}

// The method that receives the message. The first thing you should do is probably
// checking what kind of message was sent...
bool ResearchPointCaptionWinProc::HandleUIMessage(IWindow* window, const Message& message)
{
	if (message.eventType == MessageType::kMsgUpdate)
	{
		float points = SSResearchManager.mResearchPoints;
		string16 cap;
		cap.assign_convert(to_string(int(floor(points))));
		window->FindWindowByID(id("RPCaption"))->SetCaption(cap.c_str());
		return true;
	}
	// Return true if the message was handled, and therefore no other window procedure should receive it.
	return false;
}
