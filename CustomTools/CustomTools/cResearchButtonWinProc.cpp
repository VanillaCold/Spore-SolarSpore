#include "stdafx.h"
#include "cResearchButtonWinProc.h"
#include "cSSResearchManager.h"

cResearchButtonWinProc::cResearchButtonWinProc(UTFWin::IWindow* window, ResearchType research)
{
	mItemWindow = window;
	mResearchType = research;
	mError = u"";

	string16 numPoints;
	numPoints.assign_convert(to_string(mResearchType.mRequiredPoints));
	numPoints = u"\u268C " + numPoints;
	mItemWindow->FindWindowByID(id("counter"))->SetCaption(numPoints.c_str());

	if (SSResearchManager.mResearchPoints < mResearchType.mRequiredPoints)
	{
		mError = LocalizedString(id("SS_Research"), 0x04).GetText();

	}
	for each (uint32_t priorID in mResearchType.mPriorResearches)
	{
		if (!SSResearchManager.HasResearched(priorID))
		{
			mError = LocalizedString(id("SS_Research"), 0x04).GetText();
		}
	}

	if (mError != u"")
	{
		mpTooltip = UTFWin::CreateTooltip(mError.c_str());
		window->FindWindowByID(id("itembutton"))->AddWinProc(mpTooltip);

		window->FindWindowByID(id("disabled"))->SetVisible(true);
	}

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
	return kEventFlagBasicInput | kEventFlagAdvanced | kEventFlagUpdate;
}

// The method that receives the message. The first thing you should do is probably
// checking what kind of message was sent...
bool cResearchButtonWinProc::HandleUIMessage(IWindow* window, const Message& message)
{
	auto disabledWindow = mItemWindow->FindWindowByID(id("disabled")); //Check if the window's disabled.
	//if (!disabledWindow->IsVisible()) //if it isn't...
	//{
		if (message.IsType(MessageType::kMsgButtonClick)) //Check if clicked.
		{
			for each (IWindow * deselWindow in SSResearchManager.mpItemUIs) //For each selection window
			{
				deselWindow->FindWindowByID(id("selected"))->SetVisible(false); //Make it invisible
			}
			mItemWindow->FindWindowByID(id("selected"))->SetVisible(true); //and make this selection window visible.

			auto mainWin = WindowManager.GetMainWindow();

			mainWin->FindWindowByID(id("ResName"))->SetCaption(mResearchType.mResearchTitle.GetText());
			mainWin->FindWindowByID(id("ResDescr"))->SetCaption(mResearchType.mResearchDescription.GetText());
			mainWin->FindWindowByID(id("ResearchButton"))->SetCommandID(mResearchType.mResearchID);
			SSResearchManager.mpPointsCaption->SetCaption(mItemWindow->FindWindowByID(id("counter"))->GetCaption());

			auto iconWindow = mainWin->FindWindowByID(id("ResearchItemIcon"));
			ImagePtr img;
			ResourceKey imgKey;

			//iconWindow->SetDrawable(mItemWindow->FindWindowByID(id("ItemIcon"))->GetDrawable());

			if (App::Property::GetKey(mResearchType.mpPropList.get(), id("ResearchImage"), imgKey))
			{
				ImagePtr img;
				if (Image::GetImage(imgKey, img))
				{
					iconWindow->SetVisible(false);
					ImageDrawable* drawable = new ImageDrawable();
					drawable->SetImage(img.get());
					iconWindow->SetDrawable(drawable);

					iconWindow->SetVisible(true);

					
				}
				
			}

			return true;
		}

		if (message.IsType(MessageType::kMsgMouseEnter))
		{
			mItemWindow->FindWindowByID(id("rollover"))->SetVisible(true);
			return true;
		}

		if (message.IsType(MessageType::kMsgMouseLeave))
		{
			mItemWindow->FindWindowByID(id("rollover"))->SetVisible(false);
		}
	//}
	if (disabledWindow->IsVisible())
	{
		if (message.IsType(MessageType::kMsgUpdate))
		{
			if (mError == u"Not enough research points." && !(SSResearchManager.mResearchPoints < mResearchType.mRequiredPoints))
			{
				disabledWindow->SetVisible(false);
				mError = u"";
				window->RemoveWinProc(mpTooltip);
			}
		}
	}
	// Return true if the message was handled, and therefore no other window procedure should receive it.
	return false;
}
