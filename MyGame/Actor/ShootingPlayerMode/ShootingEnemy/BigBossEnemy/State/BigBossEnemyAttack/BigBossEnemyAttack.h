#pragma once

#include "../Actor/ActorState/ActorStateBase.h"
#include "AttackChoice.h"
#include "../Effekseer/EffectObj/EffectObj.h"

#include "../Actor/EnemyCommon/PlayerLook/PlayerLook.h"

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

	void AttackCollision(Vector3 lposition, Matrix lrotation, Vector3 attackpos, int deadTime, int attackParam, Vector3 spot, float len, float rad);

	void EffectCreate(EFFECT_ID id, float deadTime);

private:
	AttackChoice mAC;

	int mattackType;

	EffectObj meff;
	float meffspeed;

	Vector3 mPlayerPos;
	float mAttackHeight;
	Vector3 mAttackPos;
};
