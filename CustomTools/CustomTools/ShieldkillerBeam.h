#pragma once

#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cDefaultBeamTool.h>
using namespace Simulator;

#define ShieldkillerBeamPtr intrusive_ptr<ShieldkillerBeam>

class ShieldkillerBeam 
	: public Object
	, public DefaultRefCounted
	, public Simulator::cDefaultBeamTool
{
public:
	static const uint32_t TYPE = id("ShieldkillerBeam");
	static const uint32_t STRATEGY_ID = id("ShieldkillerBeam");
	ShieldkillerBeam();
	~ShieldkillerBeam();

	virtual bool OnHit(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int) override;

	int AddRef() override;
	int Release() override;
	void* Cast(uint32_t type) const override;
	IVisualEffectPtr shieldEffect;

private:
	int playerDamage;


};
