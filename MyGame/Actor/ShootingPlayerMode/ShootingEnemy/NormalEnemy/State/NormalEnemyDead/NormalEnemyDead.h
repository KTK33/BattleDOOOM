#pragma once

#include "../Actor/ActorState/ActorStateBase.h"

//�ʏ�G�l�~�[���S�X�e�C�g�N���X
class NormalEnemyDead :public ActorStateBase
{
public:
	NormalEnemyDead(IWorld* world, ActorParameters& parameter);
	virtual void Stateinitialize() override;
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation, AnimatedMesh & lmesh) override;

private:
};
