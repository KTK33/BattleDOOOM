#pragma once

#include "../Actor/ActorState/ActorStateBase.h"

//中ボスの火炎攻撃前段階ステイト
class BossEnemyFireBefo :public ActorStateBase
{
public:
	BossEnemyFireBefo(IWorld* world, ActorParameters& parameter);
	virtual void Stateinitialize() override;
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation, AnimatedMesh & lmesh) override;

private:
};
