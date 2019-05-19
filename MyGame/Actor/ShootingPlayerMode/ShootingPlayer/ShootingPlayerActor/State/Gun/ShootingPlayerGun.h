#pragma once

#include "../Actor/ActorState/ActorStateBase.h"

class ShootingPlayerGun :public ActorStateBase
{
public:
	ShootingPlayerGun(IWorld* world, ActorParameters& parameter);
	virtual void Stateinitialize() override;
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation, AnimatedMesh & lmesh) override;

private:
	void Gun(Vector3 lposition,Matrix lrotation);
};
