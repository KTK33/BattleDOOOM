#pragma once

#include "../Actor/ActorState/ActorStateBase.h"

//��{�X�̎��S���N���X
class BigBossEnemyDead :public ActorStateBase
{
public:
	BigBossEnemyDead(IWorld* world, ActorParameters& parameter);
	virtual void Stateinitialize() override;
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation, AnimatedMesh & lmesh) override;

private:
};
