#pragma once

#include "../Actor/ActorState/ActorStateBase.h"

//�ʏ�G�l�~�[�_���[�W�X�e�C�g�N���X
class NormalEnemyDamage :public ActorStateBase
{
public:
	NormalEnemyDamage(IWorld* world, ActorParameters& parameter);
	virtual void Stateinitialize() override;
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation, AnimatedMesh & lmesh) override;

private:
};
