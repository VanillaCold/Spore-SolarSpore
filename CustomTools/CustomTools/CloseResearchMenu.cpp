#include "stdafx.h"
#include "CloseResearchMenu.h"
#include "cSSResearchManager.h"

CloseResearchMenu::CloseResearchMenu()
{
}


CloseResearchMenu::~CloseResearchMenu()
{
}

// For internal use, do not modify.
int CloseResearchMenu::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int CloseResearchMenu::Release()
{
	return DefaultRefCounted::Release();
}

// You can extend this function to return any other types your class implements.
void* CloseResearchMenu::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(IWinProc);
	CLASS_CAST(CloseResearchMenu);
	return nullptr;
}

// This method returns a combinations of values in UTFWin::EventFlags.
// The combination determines what types of events (messages) this window procedure receives.
// By default, it receives mouse/keyboard input and advanced messages.
int CloseResearchMenu::GetEventFlags() const
{
	return kEventFlagBasicInput | kEventFlagAdvanced;
}

// The method that receives the message. The first thing you should do is probably
// checking what kind of message was sent...
bool CloseResearchMenu::HandleUIMessage(IWindow* window, const Message& message)
{
	if (message.eventType == MessageType::kMsgButtonClick)
	{
		SSResearchManager.CloseResearchUI();
	}
	// Return true if the message was handled, and therefore no other window procedure should receive it.
	return false;
}
