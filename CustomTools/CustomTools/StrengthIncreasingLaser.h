#pragma once

#include <Spore\BasicIncludes.h>
#include <Spore/Simulator/cDefaultBeamTool.h>

#define StrengthIncreasingLaserPtr intrusive_ptr<StrengthIncreasingLaser>

class StrengthIncreasingLaser 
	: public Simulator::cDefaultBeamTool
{
public:
	static const uint32_t TYPE = id("StrengthIncreasingLaser");
	static const uint32_t STRATEGY_ID = id("StrengthIncreasingLaser");

	StrengthIncreasingLaser();
	~StrengthIncreasingLaser();

	virtual bool WhileFiring(Simulator::cSpaceToolData* pTool, const Vector3& aimPoint, int) override;
	virtual bool OnMouseUp(Simulator::cSpaceToolData* pTool) override;
	virtual bool WhileAiming(Simulator::cSpaceToolData* pTool, const Vector3& aimPoint, bool showErrors) override;

	int AddRef() override;
	int Release() override;
	void* Cast(uint32_t type) const override;
};
