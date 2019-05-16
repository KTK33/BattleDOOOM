#pragma once

#include "../Actor/ActorState/ActorStateBase.h"

class RedSamuraiAttack :public ActorStateBase
{
public:
	RedSamuraiAttack(IWorld* world, ActorParameters& parameter);
	virtual void Stateinitialize() override;
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation, AnimatedMesh & lmesh) override;

private:
	//�ǂ̍U���̔���
	void AttackBehavior(Vector3 lposition, Matrix lrotation);
	//�U���̓����蔻�萶��
	void AttackCollision(Vector3 lposition,Matrix lrotation,int deadTime, int attackParam, Vector3 spot, float len, float rad);
private:
	bool mAttackAlready;

	bool mAttckStart;
};
