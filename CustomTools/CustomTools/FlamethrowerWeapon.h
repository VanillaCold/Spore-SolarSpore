#pragma once

#include <Spore\BasicIncludes.h>

#define FlamethrowerWeaponPtr intrusive_ptr<FlamethrowerWeapon>

class FlamethrowerWeapon 
	: public Simulator::cToolStrategy
{
public:
	static const uint32_t TYPE = id("FlamethrowerWeapon");
	static const uint32_t STRATEGY_ID = id("Flamethrower");
	
	FlamethrowerWeapon();
	~FlamethrowerWeapon();


	virtual bool WhileFiring(Simulator::cSpaceToolData* pTool, const Vector3& aimPoint, int unk);
	virtual bool OnMouseUp(Simulator::cSpaceToolData* pTool);
	Vector3 GetAimPoint() override;

	map<Simulator::cCombatant*, IVisualEffectPtr> mpEffectsForCombatants;


	void* Cast(uint32_t type) const override;
};
