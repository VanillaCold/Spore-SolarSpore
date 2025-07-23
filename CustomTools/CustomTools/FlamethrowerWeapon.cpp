#include "stdafx.h"
#include "FlamethrowerWeapon.h"
#include <Spore/Simulator/cGameTerrainCursor.h>

FlamethrowerWeapon::FlamethrowerWeapon()
{
	mpEffectsForCombatants = {};
}


FlamethrowerWeapon::~FlamethrowerWeapon()
{
}

bool FlamethrowerWeapon::WhileFiring(Simulator::cSpaceToolData* pTool, const Vector3& aimPoint, int unk)
{
	Vector3 targetPos = aimPoint;

	Vector3 direction = (targetPos - pTool->mpToolOwner->mPosition).Normalized();
	Vector3 pos = pTool->mpToolOwner->mPosition + (direction * pTool->mDamageRadius * 2);

	bool bChaosMode;
	App::Property::GetBool(pTool->mpPropList.get(), id("flamethrower-attackAllies"), bChaosMode);

	auto combatant = object_cast<Simulator::cCombatant>(pTool->mpToolOwner);

	// Deal damage to combatants caught in the blast.

	eastl::vector <cSpatialObjectPtr> combatantsCaught;
	GameViewManager.IntersectSphere(pos, pTool->mDamageRadius, combatantsCaught);

	for (cSpatialObjectPtr obj : combatantsCaught)
	{
		if (obj.get() == pTool->mpToolOwner.get())
		{
			continue;
		}
		auto targetCombatant = object_cast<Simulator::cCombatant>(obj);
		auto targetGameData = object_cast<Simulator::cGameData>(obj);
		
		if (targetCombatant && targetGameData)
		{
			if (RelationshipManager.IsAllied(targetGameData->mPoliticalID, combatant->GetPoliticalID()) && !bChaosMode)
			{
				continue;
			}

			auto distance = (pos - obj->GetPosition()).Length();

			float distanceRatio = 1 - (distance / pTool->mDamageRadius);
			float damageDealt = (((pTool->mMaxDamage - pTool->mMinDamage) * distanceRatio) + pTool->mMinDamage) * pTool->mAutoFireRate;

			targetCombatant->TakeDamage(damageDealt, combatant->GetPoliticalID(), 0, pos, combatant);
		}

	}

	// Deal with the visual effect.

	if (mpEffectsForCombatants.find(combatant) == mpEffectsForCombatants.end())
	{
		IVisualEffectPtr effect;
		if (EffectsManager.CreateVisualEffect(pTool->mBeamEffectID, 0, effect))
		{
			Transform transform = effect->GetSourceTransform();
			transform.SetOffset(targetPos);

			transform.SetScale(2);

			effect->SetSourceTransform(transform);
			effect->Start();

			mpEffectsForCombatants.emplace(combatant, effect);
		}
	}
	else
	{
		auto effect = mpEffectsForCombatants[combatant];
		if (effect)
		{
			effect->SetSourceTransform(effect->GetSourceTransform().SetOffset(pos));
		}
		else
		{
			SporeDebugPrint("wah");
			mpEffectsForCombatants.erase(combatant);
		}
	}

	return Simulator::cToolStrategy::WhileFiring(pTool, targetPos, unk);
}

bool FlamethrowerWeapon::OnMouseUp(Simulator::cSpaceToolData* pTool)
{
	auto combatant = object_cast<Simulator::cCombatant>(pTool->mpToolOwner);


	if (mpEffectsForCombatants.find(combatant) != mpEffectsForCombatants.end())
	{
		auto effect = mpEffectsForCombatants[combatant];
		if (effect)
		{
			effect->Stop(0);
		}
		mpEffectsForCombatants.erase(combatant);
	}

	return Simulator::cToolStrategy::OnMouseUp(pTool);
}

Vector3 FlamethrowerWeapon::GetAimPoint()
{

	Vector3 cameraPosition, mouseDir;
	App::GetViewer()->GetCameraToMouse(cameraPosition, mouseDir);
	
	auto obj = GameViewManager.GetHoveredObject();

	if (obj)
	{
		return object_cast<Simulator::cSpatialObject>(obj)->GetPosition();
	}

	// no need for an "else"

	auto pPlayer = Simulator::GetPlayerUFO();

	// The normal vector is just the player's position, as this is the "up" vector relative to the planet.
	auto test = Math::PlaneEquation(pPlayer->GetPosition().Normalized(), pPlayer->GetPosition());
	
	Vector3 positionHit{};
	PlaneEquation::Intersection gridPosition = test.IntersectRay(cameraPosition, mouseDir, positionHit);
	Vector3 playerPos = pPlayer->GetPosition();

	SporeDebugPrint("point at %f, %f, %f", positionHit.x, positionHit.y, positionHit.z);
	SporeDebugPrint("player pos at %f, %f, %f ", playerPos.x, playerPos.y, playerPos.z);
	
	auto cursor = Simulator::cGameTerrainCursor::GetTerrainCursor();
	if (cursor && cursor->GetPosition() != Vector3(0,0,0)) 
	{

		// intellisense can scream at me all it wants, i'm not making these const references-
		Vector3 cursorPos = cursor->GetPosition();

		SporeDebugPrint("cursor at %f, %f, %f", cursorPos.x, cursorPos.y, cursorPos.z);

		float gridDistance = (positionHit - playerPos).Length();
		float cursorDistance = (cursorPos - playerPos).Length();

		// If the grid is further than the ground, then assume the player wants to hit the ground.
		if (cursorDistance <= 100)
		{
			// and set the position accordingly.
			positionHit = cursorPos;
		}
	}

	return positionHit;

}

// You can extend this function to return any other types your class implements.
void* FlamethrowerWeapon::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(Simulator::cToolStrategy);
	CLASS_CAST(FlamethrowerWeapon);
	return nullptr;
}
