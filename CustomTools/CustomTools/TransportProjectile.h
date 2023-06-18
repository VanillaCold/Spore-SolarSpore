#pragma once

#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cDefaultProjectileWeapon.h>

#define TransportProjectilePtr intrusive_ptr<TransportProjectile>
using namespace Simulator;
class TransportProjectile 
	: public Object
	, public DefaultRefCounted
	, public cDefaultProjectileWeapon
{
public:
	static const uint32_t TYPE = id("TransportProjectile");
	static const uint32_t STRATEGY_ID = id("TransportProjectile");
	
	TransportProjectile();
	~TransportProjectile();

	virtual bool OnHit(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int) override;
	virtual bool WhileFiring(cSpaceToolData* pTool, const Vector3& aimPoint, int) override;

	int AddRef() override;
	int Release() override;
	void* Cast(uint32_t type) const override;

private:
	queue<float> deactiveShipSpeeds;
	queue<float> deactiveShipSizes;
};
