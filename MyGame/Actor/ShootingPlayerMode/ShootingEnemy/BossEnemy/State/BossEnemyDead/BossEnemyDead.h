#pragma once

#include "../Actor/ActorState/ActorStateBase.h"

//中ボスの死亡ステイト
class BossEnemyDead :public ActorStateBase
{
public:
	BossEnemyDead(IWorld* world, ActorParameters& parameter);
	virtual void Stateinitialize() override;
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation, AnimatedMesh & lmesh) override;

private:
};
