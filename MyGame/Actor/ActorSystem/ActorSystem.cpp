#include "ActorSystem.h"

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

