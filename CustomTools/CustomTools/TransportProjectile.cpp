#include "stdafx.h"
#include "TransportProjectile.h"

TransportProjectile::TransportProjectile()
{
	deactiveShipSpeeds = {};
	deactiveShipSizes = {};
}


TransportProjectile::~TransportProjectile()
{
}

bool TransportProjectile::OnHit(cSpaceToolData* pTool, const Vector3& position, SpaceToolHit hitType, int unk)
{
	Simulator::cGameDataUFO* ufoObj = object_cast<Simulator::cGameDataUFO>(pTool->mpToolOwner);

	ufoObj->Teleport(position, Math::Quaternion()); 
	ufoObj->SetScale(deactiveShipSizes.front());
	deactiveShipSizes.pop();
	ufoObj->mStandardSpeed = deactiveShipSpeeds.front();
	deactiveShipSpeeds.pop();

	ufoObj->mNextPosition = position;
	ufoObj->mPosition = position;
	ufoObj->mbAtDestination = true;
	ufoObj->mbEnabled = true;
	ufoObj->Teleport(position, Math::Quaternion());
	ufoObj->MoveTo(position, 0);
	ufoObj->mbDesiredVisible = true;

	((cCombatant*)ufoObj)->mbInvincible = false;

	return cDefaultProjectileWeapon::OnHit(pTool,position,hitType,unk);
}

bool TransportProjectile::WhileFiring(cSpaceToolData* pTool, const Vector3& aimPoint, int unk)
{
	bool result = cDefaultProjectileWeapon::WhileFiring(pTool,aimPoint,unk);
	if (result != false)
	{
		Simulator::cGameDataUFO* ufoObj = object_cast<Simulator::cGameDataUFO>(pTool->mpToolOwner);
		deactiveShipSpeeds.emplace_back(ufoObj->mStandardSpeed);
		deactiveShipSizes.emplace_back(ufoObj->GetScale());
		ufoObj->mStandardSpeed = 0;
		ufoObj->mbEnabled = false;
		((cCombatant*)ufoObj)->mbInvincible = true;
		ufoObj->SetScale(0);

		ufoObj->mbAtDestination = true;
		ufoObj->mPosition = Vector3(-1000, 0, 0);
		ufoObj->Teleport(Vector3(-1000, 0, 0), Math::Quaternion());
		ufoObj->mNextPosition = Vector3(-1000, 0, 0);
		ufoObj->MoveTo(Vector3(-1000, 0, 0),0);
//Teleport(Vector3(-1000, 0, 0), Math::Quaternion());
		return result;
	}
	return false;
}

// For internal use, do not modify.
int TransportProjectile::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int TransportProjectile::Release()
{
	return DefaultRefCounted::Release();
}

// You can extend this function to return any other types your class implements.
void* TransportProjectile::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(TransportProjectile);
	return nullptr;
}
