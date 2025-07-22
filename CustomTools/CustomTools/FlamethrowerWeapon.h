#pragma once

#include <Spore\BasicIncludes.h>

#define FlamethrowerWeaponPtr intrusive_ptr<FlamethrowerWeapon>

class FlamethrowerWeapon 
	: public Simulator::cToolStrategy
{
public:
	static const uint32_t TYPE = id("FlamethrowerWeapon");
	
	FlamethrowerWeapon();
	~FlamethrowerWeapon();

	Vector3 GetAimPoint() override;



	void* Cast(uint32_t type) const override;
};
