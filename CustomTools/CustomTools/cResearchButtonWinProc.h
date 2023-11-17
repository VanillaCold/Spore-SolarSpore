#pragma once

#include <Spore\BasicIncludes.h>
#include "cSSResearchManager.h"

#define cResearchButtonWinProcPtr intrusive_ptr<cResearchButtonWinProc>

// To avoid repeating UTFWin:: all the time.
using namespace UTFWin;

class cResearchButtonWinProc 
	: public IWinProc
	, public DefaultRefCounted
{
public:
	static const uint32_t TYPE = id("cResearchButtonWinProc");
	
	cResearchButtonWinProc(UTFWin::IWindow* window, ResearchType research);
	~cResearchButtonWinProc();

	int AddRef() override;
	int Release() override;
	void* Cast(uint32_t type) const override;
	
	int GetEventFlags() const override;
	// This is the function you have to implement, called when a window you added this winproc to received an event
	bool HandleUIMessage(IWindow* pWindow, const Message& message) override;

private:
	ResearchType mResearchType;
	UTFWin::IWindow* mItemWindow;
	string16 mError;
	UTFWin::Tooltip* mpTooltip;


};
