#pragma once

#include "../Actor/ActorState/ActorStateBase.h"

//���{�X�̔�_���[�W�N���X
class BossEnemyDamage :public ActorStateBase
{
public:
	BossEnemyDamage(IWorld* world, ActorParameters& parameter);
	virtual void Stateinitialize() override;
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation, AnimatedMesh & lmesh) override;

private:
};
