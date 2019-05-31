#pragma once

#include "../Actor/ActorState/ActorStateBase.h"

class RedSamuraiPlayerDeadAftor :public ActorStateBase
{
public:
	RedSamuraiPlayerDeadAftor(IWorld* world, ActorParameters& parameter);
	virtual void Stateinitialize() override;
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation, AnimatedMesh & lmesh) override;
private:
};
