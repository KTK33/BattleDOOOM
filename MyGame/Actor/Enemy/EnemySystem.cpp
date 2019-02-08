#include "EnemySystem.h"

float EnemySystem::PlayerDirection(Actor* player, Vector3& position, Matrix& matrix)
{
	const auto& to_target = player->Getpose().Translation() - position;
	const auto angle = Vector3::Angle(matrix.Forward(), to_target);
	const auto& forward_cross_target = Vector3::Cross(matrix.Forward(), to_target);
	return (forward_cross_target.y >= 0.0f) ? angle : -angle;
}
