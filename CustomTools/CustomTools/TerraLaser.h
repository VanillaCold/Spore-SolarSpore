#pragma once

#include <Spore\BasicIncludes.h>
#include <Spore/Simulator/cDefaultBeamTool.h>

#define TerraLaserPtr intrusive_ptr<TerraLaser>
using namespace Simulator;

class TerraLaser 
	: public Simulator::cDefaultBeamTool
{
public:
	static const uint32_t TYPE = id("TerraLaser");
	static const uint32_t STRATEGY_ID = id("TerraLaser");
	
	TerraLaser();
	~TerraLaser();

	static uint32_t sTerraActive;

	virtual void OnMouseDown(cSpaceToolData* pTool, const Vector3& playerPosition) override;
	virtual bool OnHit(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int) override;
	virtual bool WhileFiring(cSpaceToolData* pTool, const Vector3& aimPoint, int) override;
	virtual bool OnMouseUp(cSpaceToolData* pTool) override;
	void* Cast(uint32_t type) const override;
};
