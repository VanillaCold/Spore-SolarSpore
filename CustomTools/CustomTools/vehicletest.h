#pragma once

#include <Spore\BasicIncludes.h>

class vehicletest 
	: public ArgScript::ICommand
	, public Sporepedia::IShopperListener
{
	string arg1 = "0";
	string arg2 = "0";
public:
	vehicletest();
	~vehicletest();

	// Called when the cheat is invoked
	void ParseLine(const ArgScript::Line& line) override;
	void OnShopperAccept(const ResourceKey& selection) override;

	
	// Returns a string containing the description. If mode != DescriptionMode::Basic, return a more elaborated description
	const char* GetDescription(ArgScript::DescriptionMode mode) const override;
};

