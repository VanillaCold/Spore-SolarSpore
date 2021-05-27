#pragma once

#include <Spore\BasicIncludes.h>
#include <Spore\Simulator\cSpaceToolData.h>
#include <Spore\Simulator\cDefaultProjectileWeapon.h>
#include <Spore\Simulator\cDefaultBeamTool.h>
using namespace Simulator;
class SpawnVehicle
	:public Simulator::cDefaultBeamTool
{
	IEffectPtr beameffect;
	IEffectPtr hiteffect;
	cGameDataUFOPtr vehicle;
	Vector3& playpos = Vector3(0,0,0);
public:
	SpawnVehicle();
	~SpawnVehicle();
	
	virtual bool WhileFiring(cSpaceToolData* pTool,const Vector3& aimPoint,int);
	void OnMouseDown(cSpaceToolData* pTool, const Vector3& playerPosition);
	/*virtual bool func4Ch(cSpaceToolData* pTool,const Vector3&);
	virtual bool func48h(cSpaceToolData* pTool, const Vector3&);
	virtual bool OnHit(cSpaceToolData* pTool, const Vector3& position, cSpaceToolData::SpaceToolHit hitType);*/
	virtual bool OnMouseUp(cSpaceToolData* pTool) override;
};