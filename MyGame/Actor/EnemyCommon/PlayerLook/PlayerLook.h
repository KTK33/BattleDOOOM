#pragma once
#include "../Actor/Actor.h"
#include "../Math/Vector3.h"

class PlayerLook
{
	float PlayerDirection(Actor* player, Vector3& position, Matrix& matrix);
public:
	float Look(Actor* player, Vector3& position, Matrix& matrix);
};