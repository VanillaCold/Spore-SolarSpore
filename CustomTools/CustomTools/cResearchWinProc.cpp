#include "stdafx.h"
#include "cResearchWinProc.h"
#include "cSSResearchManager.h"

cResearchWinProc::cResearchWinProc()
{
}


cResearchWinProc::~cResearchWinProc()
{
}

// For internal use, do not modify.
int cResearchWinProc::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int cResearchWinProc::Release()
{
	return DefaultRefCounted::Release();
}

// You can extend this function to return any other types your class implements.
void* cResearchWinProc::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(IWinProc);
	CLASS_CAST(cResearchWinProc);
	return nullptr;
}

// This method returns a combinations of values in UTFWin::EventFlags.
// The combination determines what types of events (messages) this window procedure receives.
// By default, it receives mouse/keyboard input and advanced messages.
int cResearchWinProc::GetEventFlags() const
{
	return kEventFlagBasicInput | kEventFlagAdvanced;
}

// The method that receives the message. The first thing you should do is probably
// checking what kind of message was sent...
bool cResearchWinProc::HandleUIMessage(IWindow* window, const Message& message)
{
	if (message.eventType == MessageType::kMsgButtonClick)
	{
		if (window->GetCommandID() != 0)
		{
			string error;
			if (!SSResearchManager.ResearchItem(window->GetCommandID(), error))
			{
				App::ConsolePrintF(error.c_str());
				return false;
			}
			else
			{
				SSResearchManager.CloseResearchUI(false);
				SSResearchManager.OpenResearchUI(false);
				return true;
			}
			
		}
		return false;
	}
	// Return true if the message was handled, and therefore no other window procedure should receive it.
	return false;
}
