#include "stdafx.h"
#include "ChangeCaptain.h"

ChangeCaptain::ChangeCaptain()
{
}


ChangeCaptain::~ChangeCaptain()
{
}


void ChangeCaptain::ParseLine(const ArgScript::Line& line)
{
	// This method is called when your cheat is invoked.
	// Put your cheat code here.	Simulator::GetPlayerEmpire()->mCaptainKey;
	Sporepedia::ShopperRequest request(this);
	request.shopperID = id("AdventurersShopper");
	request.Show(request);
}

const char* ChangeCaptain::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "This cheat does something.";
	}
	else {
		return "ChangeCaptain: Elaborate description of what this cheat does.";
	}
}

void ChangeCaptain::OnShopperAccept(const ResourceKey& selection)
{
	Simulator::GetPlayerEmpire()->mCaptainKey = selection;
}
