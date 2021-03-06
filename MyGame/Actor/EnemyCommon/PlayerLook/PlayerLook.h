#pragma once
#include "../Actor/Actor.h"
#include "../Math/Vector3.h"

//敵がプレイヤーの方向に向く共通処理
class PlayerLook
{
	float PlayerDirection(Actor* player, Vector3& position, Matrix& matrix);
public:
	float Look(Actor* player, Vector3& position, Matrix& matrix);
};