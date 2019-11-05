#pragma once

#include "../Actor/ActorState/ActorStateBase.h"

//大ボスの死亡時クラス
class BigBossEnemyDead :public ActorStateBase
{
public:
	BigBossEnemyDead(IWorld* world, ActorParameters& parameter);
	virtual void Stateinitialize() override;
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation, AnimatedMesh & lmesh) override;

private:
};
