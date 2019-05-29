#pragma once

#include "../Actor/ActorState/ActorStateBase.h"

class RedSamuraiIdle :public ActorStateBase
{
public:
	RedSamuraiIdle(IWorld* world, ActorParameters& parameter);
	virtual void Stateinitialize() override;
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation, AnimatedMesh & lmesh) override;

private:
};
