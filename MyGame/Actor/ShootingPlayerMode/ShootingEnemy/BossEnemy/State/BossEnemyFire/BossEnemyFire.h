#pragma once

#include "../Actor/ActorState/ActorStateBase.h"

//���{�X�̉��U���X�e�C�g
class BossEnemyFire :public ActorStateBase
{
public:
	BossEnemyFire(IWorld* world, ActorParameters& parameter);
	virtual void Stateinitialize() override;
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation, AnimatedMesh & lmesh) override;

private:
	void FireCollision(Vector3 lposition,Matrix lrotation);
};
