#pragma once

#include "../Actor/ActorState/ActorStateBase.h"

//通常エネミーパンチステイトクラス
class NormalEnemyPunch :public ActorStateBase
{
public:
	NormalEnemyPunch(IWorld* world, ActorParameters& parameter);
	virtual void Stateinitialize() override;
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation, AnimatedMesh & lmesh) override;

private:
	void AttackCollision(Vector3 lposition, Matrix lrotation, int deadTime, int attackParam, Vector3 spot, float len, float rad);
};
