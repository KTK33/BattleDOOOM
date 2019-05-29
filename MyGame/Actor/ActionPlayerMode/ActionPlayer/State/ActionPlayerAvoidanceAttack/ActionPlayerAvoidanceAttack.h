#pragma once

#include "../Actor/ActorState/ActorStateBase.h"

class ActionPlayerAvoidanceAttack :public ActorStateBase
{
public:
	ActionPlayerAvoidanceAttack(IWorld* world, ActorParameters& parameter);
	virtual void Stateinitialize() override;
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation, AnimatedMesh & lmesh) override;

private:
	void AttackOption(Vector3 lposition, Matrix lrotation);
	//çUåÇÇÃìñÇΩÇËîªíËê∂ê¨
	void AttackCollision(Vector3 lposition, Matrix lrotation, int deadTime, int attackParam, Vector3 spot, float len, float rad);
	void Input();
};
