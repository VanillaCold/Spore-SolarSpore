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
	auto combatant = object_cast<Simulator::cCombatant>(pTool->mpToolOwner);
	if (mpEffectsForCombatants.find(combatant) == mpEffectsForCombatants.end())
	{
		IVisualEffectPtr effect;
		if (EffectsManager.CreateVisualEffect(pTool->mBeamEffectID, 0, effect))
		{
			Transform transform = effect->GetSourceTransform();
			transform.SetOffset(aimPoint);

			transform.SetScale(2);

			effect->SetSourceTransform(transform);
			effect->Start();

			mpEffectsForCombatants.emplace(combatant, effect);
		}
	}
	else
	{
		auto effect = mpEffectsForCombatants[combatant];

		auto direction = (aimPoint - pTool->mpToolOwner->mPosition).Normalized();
		auto pos = pTool->mpToolOwner->mPosition + (direction * pTool->mDamageRadius * 2);
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

	return Simulator::cToolStrategy::WhileFiring(pTool, aimPoint, unk);
}

Vector3 FlamethrowerWeapon::GetAimPoint()
{

	Vector3 cameraPosition, mouseDir;
	App::GetViewer()->GetCameraToMouse(cameraPosition, mouseDir);
	auto viewDir = CameraManager.GetViewer()->GetViewTransform().GetRotation().Row(1);

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
	
	auto cursor = Simulator::cGameTerrainCursor::GetTerrainCursor();
	if (cursor) 
	{
		// intellisense can scream at me all it wants, i'm not making these const references-
		Vector3 cursorPos = cursor->GetPosition();
		Vector3 playerPos = pPlayer->GetPosition();

		float gridDistance = (positionHit - playerPos).Length();
		float cursorDistance = (cursorPos - playerPos).Length();

		// If the grid is further than the ground, then assume the player wants to hit the ground.
		if (gridDistance >= cursorDistance)
		{
			// and set the position accordingly.
			positionHit = cursorPos;
		}
	}

}

// You can extend this function to return any other types your class implements.
void* FlamethrowerWeapon::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(Simulator::cToolStrategy);
	CLASS_CAST(FlamethrowerWeapon);
	return nullptr;
}
