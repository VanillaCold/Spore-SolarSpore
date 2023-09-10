#include "stdafx.h"
#include "cResearchButtonWinProc.h"
#include "cSSResearchManager.h"

cResearchButtonWinProc::cResearchButtonWinProc(UTFWin::IWindow* window, ResearchType research)
{
	mItemWindow = window;
	mResearchType = research;

	string16 numPoints;
	numPoints.assign_convert(to_string(mResearchType.mRequiredPoints));
	mItemWindow->FindWindowByID(id("counter"))->SetCaption(numPoints.c_str());
}


cResearchButtonWinProc::~cResearchButtonWinProc()
{
}

// For internal use, do not modify.
int cResearchButtonWinProc::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int cResearchButtonWinProc::Release()
{
	return DefaultRefCounted::Release();
}

// You can extend this function to return any other types your class implements.
void* cResearchButtonWinProc::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(IWinProc);
	CLASS_CAST(cResearchButtonWinProc);
	return nullptr;
}

// This method returns a combinations of values in UTFWin::EventFlags.
// The combination determines what types of events (messages) this window procedure receives.
// By default, it receives mouse/keyboard input and advanced messages.
int cResearchButtonWinProc::GetEventFlags() const
{
	return kEventFlagBasicInput | kEventFlagAdvanced;
}

// The method that receives the message. The first thing you should do is probably
// checking what kind of message was sent...
bool cResearchButtonWinProc::HandleUIMessage(IWindow* window, const Message& message)
{
	if (message.IsType(MessageType::kMsgButtonClick))
	{
		for each (IWindow* deselWindow in SSResearchManager.mpItemUIs)
		{
			deselWindow->FindWindowByID(id("selected"))->SetVisible(false);
		}
		mItemWindow->FindWindowByID(id("selected"))->SetVisible(true);

		auto mainWin = WindowManager.GetMainWindow();

		mainWin->FindWindowByID(id("ResName"))->SetCaption(mResearchType.mResearchTitle.GetText());
		mainWin->FindWindowByID(id("ResDescr"))->SetCaption(mResearchType.mResearchDescription.GetText());
		mainWin->FindWindowByID(id("ResearchButton"))->SetCommandID(mResearchType.mResearchID);



		mainWin->FindWindowByID(id("ResearchIcon"))->SetDrawable(window->GetDrawable());

		return true;
	}

	if (message.IsType(MessageType::kMsgMouseEnter))
	{
		if (!mItemWindow->FindWindowByID(id("disabled"))->IsVisible())
		{
			mItemWindow->FindWindowByID(id("rollover"))->SetVisible(true);
		}
		return true;
	}

	if (message.IsType(MessageType::kMsgMouseLeave))
	{
		mItemWindow->FindWindowByID(id("rollover"))->SetVisible(false);
	}
	// Return true if the message was handled, and therefore no other window procedure should receive it.
	return false;
}
