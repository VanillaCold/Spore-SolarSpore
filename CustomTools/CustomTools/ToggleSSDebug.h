#pragma once

#include <Spore\BasicIncludes.h>

class ToggleSSDebug 
	: public ArgScript::ICommand
{
public:
	ToggleSSDebug();
	~ToggleSSDebug();

	// Called when the cheat is invoked
	void ParseLine(const ArgScript::Line& line) override;
	bool isDebug;
	
	// Returns a string containing the description. If mode != DescriptionMode::Basic, return a more elaborated description
	const char* GetDescription(ArgScript::DescriptionMode mode) const override;
};

