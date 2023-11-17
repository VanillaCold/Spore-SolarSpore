#pragma once

#include <Spore\BasicIncludes.h>

#define cSSArchetypeWeaponManagerPtr intrusive_ptr<cSSArchetypeWeaponManager>

class cSSArchetypeWeaponManager 
	: public Object
	, public DefaultRefCounted
	, public App::IUpdatable
{
public:
	static const uint32_t TYPE = id("cSSArchetypeWeaponManager");
	
	cSSArchetypeWeaponManager();
	~cSSArchetypeWeaponManager();

	int AddRef() override;
	int Release() override;
	void* Cast(uint32_t type) const override;

	void Update();
	
	static cSSArchetypeWeaponManager* Get();
	
private :static cSSArchetypeWeaponManager* sInstance;
};
