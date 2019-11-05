#pragma once

#include "../Actor/ActorState/ActorStateBase.h"
#include "../Effekseer/EffectObj/EffectObj.h"

//�ʏ�G�l�~�[���K�X�e�C�g�N���X
class NormalEnemyRoar :public ActorStateBase
{
public:
	NormalEnemyRoar(IWorld* world, ActorParameters& parameter);
	virtual void Stateinitialize() override;
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation, AnimatedMesh & lmesh) override;

private:
	EffectObj meff;
};
