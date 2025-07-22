#include "stdafx.h"
#include "FlamethrowerWeapon.h"
#include <Spore/Simulator/cGameTerrainCursor.h>

FlamethrowerWeapon::FlamethrowerWeapon()
{
}


FlamethrowerWeapon::~FlamethrowerWeapon()
{
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
	// Since the AI can't get to this point, we can also just assume the player's using the tool.

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
