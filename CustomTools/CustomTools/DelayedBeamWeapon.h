#pragma once

#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cDefaultBeamTool.h>

#define DelayedBeamWeaponPtr intrusive_ptr<DelayedBeamWeapon>

class DelayedBeamWeapon 
	: public Simulator::cDefaultBeamTool
{
	Simulator::cGonzagoTimer* mFireTimer;

	bool toReset;
public:
	static const uint32_t STRATEGY_ID = id("DelayedBeamWeapon");
	static const uint32_t TYPE = id("DelayedBeamWeapon");
	
	DelayedBeamWeapon();
	~DelayedBeamWeapon();

	virtual void OnMouseDown(Simulator::cSpaceToolData* pTool, const Vector3& playerPosition) override;

	virtual bool Update(Simulator::cSpaceToolData* pTool, bool showErrors, const char16_t** ppFailText = nullptr) override;
	virtual bool WhileFiring(Simulator::cSpaceToolData* pTool, const Vector3& aimPoint, int) override;
	virtual bool OnMouseUp(Simulator::cSpaceToolData* pTool) override;
};
