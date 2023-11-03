#pragma once

#include <Spore\BasicIncludes.h>

#define OpenResearchMenuPtr intrusive_ptr<OpenResearchMenu>

// To avoid repeating UTFWin:: all the time.
using namespace UTFWin;

class OpenResearchMenu 
	: public IWinProc
	, public DefaultRefCounted
{
public:
	static const uint32_t TYPE = id("OpenResearchMenu");
	
	OpenResearchMenu();
	~OpenResearchMenu();

	int AddRef() override;
	int Release() override;
	void* Cast(uint32_t type) const override;
	
	int GetEventFlags() const override;
	// This is the function you have to implement, called when a window you added this winproc to received an event
	bool HandleUIMessage(IWindow* pWindow, const Message& message) override;
	
private:
};
