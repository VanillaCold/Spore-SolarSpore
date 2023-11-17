#include "stdafx.h"
#include "cSSArchetypeWeaponManager.h"

cSSArchetypeWeaponManager::cSSArchetypeWeaponManager()
{
	sInstance = this;
}


cSSArchetypeWeaponManager::~cSSArchetypeWeaponManager()
{
}

// For internal use, do not modify.
int cSSArchetypeWeaponManager::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int cSSArchetypeWeaponManager::Release()
{
	return DefaultRefCounted::Release();
}

// You can extend this function to return any other types your class implements.
void* cSSArchetypeWeaponManager::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(cSSArchetypeWeaponManager);
	return nullptr;
}

void cSSArchetypeWeaponManager::Update()
{
}

cSSArchetypeWeaponManager* cSSArchetypeWeaponManager::Get()
{
	return sInstance;
}

cSSArchetypeWeaponManager* cSSArchetypeWeaponManager::sInstance;