#pragma once

#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cToggleToolStrategy.h>
#include <Spore\Simulator\cDefaultProjectileWeapon.h>
#include "IStatusEffect.h"
#include "cSSStatusEffectManager.h"
#include "cShieldEffect.h"

#define GiveSelfStatusToolPtr intrusive_ptr<GiveSelfStatusTool>

class GiveSelfStatusTool
	: public Object
	, public DefaultRefCounted
	, public Simulator::cToggleToolStrategy
{
public:
	static const uint32_t TYPE = id("GiveSelfStatusTool");
	static const uint32_t STRATEGY_ID = id("InflictSelf");
	GiveSelfStatusTool();
	~GiveSelfStatusTool();

	virtual bool OnSelect(Simulator::cSpaceToolData* pTool) override;
	virtual bool OnDeselect(Simulator::cSpaceToolData* pTool) override;
	virtual bool Update(Simulator::cSpaceToolData* pTool, bool showErrors, const char16_t** ppFailText = nullptr);

	int AddRef() override;
	int Release() override;
	void* Cast(uint32_t type) const override;
};
