#pragma once

#include "../Actor/ActorState/ActorStateBase.h"

class BossEnemyFireBefo :public ActorStateBase
{
public:
	BossEnemyFireBefo(IWorld* world, ActorParameters& parameter);
	virtual void Stateinitialize() override;
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation, AnimatedMesh & lmesh) override;

private:
};
