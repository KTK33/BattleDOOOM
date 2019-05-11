#include "ActorSystem.h"

float ActorSystem::PlayerDirection (Actor* player, Vector3& position, Matrix& matrix)
{
	const auto to_target = player->Getpose().Translation() - position;
	const auto angle = Vector3::Angle(matrix.Forward(), to_target);
	const auto forward_cross_target = Vector3::Cross(matrix.Forward(), to_target);
	return (forward_cross_target.y >= 0.0f) ? angle : -angle;
}

void ActorSystem::TransparenceInit()
{
	SkeletalMesh::Transparence(1.0f);
}

void ActorSystem::ActorTransparence()
{
	SkeletalMesh::Transparence(Alpha);

	if (AlphaCheck)
	{
		Alpha = min(Alpha - 0.1f, 0.0f);
		if (Alpha == 0.0f) AlphaCheck = false;
	}
	else
	{
		Alpha = min(Alpha + 0.1f, 1.0f);
		if (Alpha == 1.0f) AlphaCheck = true;
	}
}

