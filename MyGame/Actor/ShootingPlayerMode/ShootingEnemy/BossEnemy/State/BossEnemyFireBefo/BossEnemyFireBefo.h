#pragma once

#include "../Actor/ActorState/ActorStateBase.h"

//���{�X�̉Ή��U���O�i�K�X�e�C�g
class BossEnemyFireBefo :public ActorStateBase
{
public:
	BossEnemyFireBefo(IWorld* world, ActorParameters& parameter);
	virtual void Stateinitialize() override;
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation, AnimatedMesh & lmesh) override;

private:
};
