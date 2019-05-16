#pragma once

#include "../Actor/ActorState/ActorStateBase.h"


class RedSamuraiWaik :public ActorStateBase
{
public:
	RedSamuraiWaik(IWorld* world, ActorParameters& parameter);
	virtual void Stateinitialize() override;
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation, AnimatedMesh & lmesh) override;

private:
	//�ړ�����
	void Movement(Vector3 lposition);
	//�U���̕p�x����
	void AttackTimeCheck(Vector3 lposition, Matrix lrotation);
private:
	//�ړ����x
	const float WalkSpeed{ 0.25f };
	//�U���̕p�x����
	float mAttackTime;
};
