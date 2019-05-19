#pragma once

#include "../Actor/ActorState/ActorStateBase.h"

class ShootingPlayerGunPunch :public ActorStateBase
{
public:
	ShootingPlayerGunPunch(IWorld* world, ActorParameters& parameter);
	virtual void Stateinitialize() override;
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation, AnimatedMesh & lmesh) override;

private:
	void AttackCollision(Vector3 lposition,Matrix lrotation);
};
