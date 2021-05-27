#pragma once

#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cSpaceToolData.h>
#include <Spore\Simulator\cDefaultProjectileWeapon.h>
#include <Spore\Simulator\cToggleToolStrategy.h>

///
/// In your dllmain Initialize method, add the system like this:
/// ModAPI::AddSimulatorStrategy(new MySystem(), MySystem::NOUN_ID);
///

using namespace Simulator;
class RegalShield
	:public Simulator::cToolStrategy
{
public:
	RegalShield();
	~RegalShield();
	virtual bool Update(cSpaceToolData* pTool, bool showErrors, const char16_t** ppFailText = nullptr);
	virtual bool OnSelect(cSpaceToolData* pTool) override;
	virtual bool OnDeselect(cSpaceToolData* pTool) override;

};