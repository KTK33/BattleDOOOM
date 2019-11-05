#pragma once

#include "../Actor/ActorState/ActorStateBase.h"

//中ボスのパンチ攻撃ステイト
class BossEnemyPunch :public ActorStateBase
{
public:
	BossEnemyPunch(IWorld* world, ActorParameters& parameter);
	virtual void Stateinitialize() override;
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation, AnimatedMesh & lmesh) override;

private:
	void AttackCollision(Vector3 lposition, Matrix lrotation, int deadTime, int attackParam, Vector3 spot, float len, float rad);
};
