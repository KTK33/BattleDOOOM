#pragma once

#include "../Actor/ActorState/ActorStateBase.h"
#include "AttackChoice.h"

class BigBossEnemyAttack :public ActorStateBase
{
public:
	BigBossEnemyAttack(IWorld* world, ActorParameters& parameter);
	virtual void Stateinitialize() override;
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation, AnimatedMesh & lmesh) override;

private:
	void Attack();

	//Ç«ÇÃçUåÇÇÃîªíË
	void AttackBehavior(Vector3 lposition, Matrix lrotation);

	void AttackCollision(Vector3 lposition, Matrix lrotation, int deadTime, int attackParam, Vector3 spot, float len, float rad);

private:
	AttackChoice mAC;

	int mattackType;
};
