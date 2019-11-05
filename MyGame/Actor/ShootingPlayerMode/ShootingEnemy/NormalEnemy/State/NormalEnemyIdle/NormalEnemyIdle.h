#pragma once

#include "../Actor/ActorState/ActorStateBase.h"

//通常エネミーアイドルステイトクラス
class NormalEnemyIdle :public ActorStateBase
{
public:
	NormalEnemyIdle(IWorld* world, ActorParameters& parameter);
	virtual void Stateinitialize() override;
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation, AnimatedMesh & lmesh) override;

private:
};
