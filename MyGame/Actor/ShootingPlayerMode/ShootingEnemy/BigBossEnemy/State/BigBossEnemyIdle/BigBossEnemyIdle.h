#pragma once

#include "../Actor/ActorState/ActorStateBase.h"

//��{�X�̃A�C�h���N���X
class BigBossEnemyIdle :public ActorStateBase
{
public:
	BigBossEnemyIdle(IWorld* world, ActorParameters& parameter);
	virtual void Stateinitialize() override;
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation, AnimatedMesh & lmesh) override;

private:
};
