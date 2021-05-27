#pragma once

#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cSpaceToolData.h>
#include <Spore\Simulator\cDefaultProjectileWeapon.h>
#include <Spore\Simulator\cToggleToolStrategy.h>
using namespace Simulator;
class EraseSpecies
	:public Simulator::cToggleToolStrategy
	, public Sporepedia::IShopperListener
{
public:
	EraseSpecies();
	~EraseSpecies();
	void SelectedUpdate(cSpaceToolData* pTool,
		const Vector3& position) override;
	virtual bool OnSelect(cSpaceToolData* pTool) override;
	virtual bool OnDeselect(cSpaceToolData* pTool) override;
	void OnShopperAccept(const ResourceKey& selection) override;
};
