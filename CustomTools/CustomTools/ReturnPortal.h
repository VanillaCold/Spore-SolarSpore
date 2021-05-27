#pragma once

#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cSpaceToolData.h>
#include <Spore\Simulator\cDefaultProjectileWeapon.h>
#include <Spore\Simulator\cPlaceColonyToolStrategy.h>
using namespace Simulator;
class ReturnPortal
	:public Simulator::cPlaceColonyToolStrategy
	//, public Sporepedia::IShopperListener
{
public:
	ReturnPortal();
	~ReturnPortal();
	virtual bool OnSelect(cSpaceToolData* pTool) override;
	virtual bool Update(cSpaceToolData* pTool, bool showErrors, const char16_t** ppFailText = nullptr) override;
	virtual bool WhileAiming(cSpaceToolData* pTool,
		const Vector3& aimPoint,
		bool showErrors) override;
	void SelectedUpdate(cSpaceToolData* pTool,
		const Vector3& position) override;
	virtual bool OnHit(cSpaceToolData* pTool,
		const Vector3& position,
		cSpaceToolData::SpaceToolHit hitType, int) override;
	//void OnShopperAccept(const ResourceKey& selection) override;
};