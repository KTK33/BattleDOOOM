#pragma once

#include "../Actor/ActorState/ActorStateBase.h"

//���{�X�̃A�C�h���X�e�C�g
class BossEnemyIdle :public ActorStateBase
{
public:
	BossEnemyIdle(IWorld* world, ActorParameters& parameter);
	virtual void Stateinitialize() override;
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation, AnimatedMesh & lmesh) override;

private:
};
