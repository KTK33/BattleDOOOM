#pragma once
#include "../Actor/Actor.h"
#include "../Math/Vector3.h"

//“G‚ªƒvƒŒƒCƒ„[‚Ì•ûŒü‚ÉŒü‚­‹¤’Êˆ—
class PlayerLook
{
	float PlayerDirection(Actor* player, Vector3& position, Matrix& matrix);
public:
	float Look(Actor* player, Vector3& position, Matrix& matrix);
};