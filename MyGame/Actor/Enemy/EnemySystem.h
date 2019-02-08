#pragma once
#include "../Actor.h"
#include "../../Math/Matrix.h"

class EnemySystem
{
public:
	float PlayerDirection(Actor* player, Vector3& position, Matrix& matrix);

private:
	float TargetAngle{ 2.5f };
};
