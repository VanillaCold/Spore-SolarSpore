#include "stdafx.h"
#include "OpenResearchMenu.h"
#include "cSSResearchManager.h"

OpenResearchMenu::OpenResearchMenu()
{
}


OpenResearchMenu::~OpenResearchMenu()
{
}

// For internal use, do not modify.
int OpenResearchMenu::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int OpenResearchMenu::Release()
{
	return DefaultRefCounted::Release();
}

// You can extend this function to return any other types your class implements.
void* OpenResearchMenu::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(IWinProc);
	CLASS_CAST(OpenResearchMenu);
	return nullptr;
}

// This method returns a combinations of values in UTFWin::EventFlags.
// The combination determines what types of events (messages) this window procedure receives.
// By default, it receives mouse/keyboard input and advanced messages.
int OpenResearchMenu::GetEventFlags() const
{
	return kEventFlagBasicInput | kEventFlagAdvanced;
}

// The method that receives the message. The first thing you should do is probably
// checking what kind of message was sent...
bool OpenResearchMenu::HandleUIMessage(IWindow* window, const Message& message)
{
	App::ConsolePrintF(to_string(window->GetState()).c_str());
	if (message.eventType == MessageType::kMsgButtonSelect)
	{
		if (window->GetTextFontID() != 55)
		{
			window->SetTextFontID(55);
			SSResearchManager.OpenResearchUI();
			window->SetState(29);
			return true;
		}
		else
		{
			window->SetTextFontID(0);
			SSResearchManager.CloseResearchUI();
			return true;
		}
		return true;
	}


	// Return true if the message was handled, and therefore no other window procedure should receive it.
	return false;
}
