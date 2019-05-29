#pragma once

#include "../Actor/ActorState/ActorStateBase.h"

class RedSamuraiPlayerDead :public ActorStateBase
{
public:
	RedSamuraiPlayerDead(IWorld* world, ActorParameters& parameter);
	virtual void Stateinitialize() override;
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation, AnimatedMesh & lmesh) override;

private:
};
