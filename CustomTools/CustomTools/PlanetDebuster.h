#pragma once

#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cSpaceToolData.h>
#include <Spore\Simulator\cDefaultProjectileWeapon.h>
#include <Spore\Simulator\cToggleToolStrategy.h>
#include <Spore\Simulator\cPlaceColonyToolStrategy.h>

///
/// In your dllmain Initialize method, add the system like this:
/// ModAPI::AddSimulatorStrategy(new MySystem(), MySystem::NOUN_ID);
///

using namespace Simulator;
class PlanetDebuster
	:public Simulator::cPlaceColonyToolStrategy
{
	IEffectPtr effect;
public:
	PlanetDebuster();
	~PlanetDebuster();
	virtual bool OnSelect(cSpaceToolData* pTool) override;
	virtual bool Update(cSpaceToolData* pTool, bool showErrors, const char16_t** ppFailText = nullptr) override;
	bool OnDeselect(cSpaceToolData* pTool);
	virtual bool WhileAiming(cSpaceToolData* pTool,
		const Vector3& aimPoint,
		bool showErrors) override;
	void SelectedUpdate(cSpaceToolData* pTool,
		const Vector3& position) override;
	virtual bool OnHit(cSpaceToolData* pTool,
		const Vector3& position,
		cSpaceToolData::SpaceToolHit hitType, int) override;

};