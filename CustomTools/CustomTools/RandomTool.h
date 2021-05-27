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
class RandomTool
	:public Simulator::cToggleToolStrategy
{
public:
	RandomTool();
	~RandomTool();
	void SelectedUpdate(cSpaceToolData* pTool,
		const Vector3& position) override;
	virtual bool OnSelect(cSpaceToolData* pTool) override;
	virtual bool OnDeselect(cSpaceToolData* pTool) override;

};