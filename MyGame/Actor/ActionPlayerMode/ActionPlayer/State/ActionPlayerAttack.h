#pragma once

#include "../Actor/ActorState/ActorStateBase.h"

class ActionPlayerAttack :public ActorStateBase
{
public:
	ActionPlayerAttack(IWorld* world, ActorParameters& parameter);
	virtual void Stateinitialize() override;
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation, AnimatedMesh & lmesh) override;

private:
	//�U��
	void Attack();
	//�U���̎�ނœ����蔻���ύX
	void AttackOption(Vector3 lposition, Matrix lrotation);
	//�U���̓����蔻�萶��
	void AttackCollision(Vector3 lposition, Matrix lrotation, int deadTime, int attackParam, Vector3 spot, float len, float rad);
	//���͏��
	void Input();
private:
	int mAttackCount;
};
