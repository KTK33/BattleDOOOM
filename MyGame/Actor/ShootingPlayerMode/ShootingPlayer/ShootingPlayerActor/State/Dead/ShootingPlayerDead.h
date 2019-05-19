#pragma once

#include "../Actor/ActorState/ActorStateBase.h"

class ShootingPlayerDead :public ActorStateBase
{
public:
	ShootingPlayerDead(IWorld* world, ActorParameters& parameter);
	virtual void Stateinitialize() override;
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation, AnimatedMesh & lmesh) override;

private:
	void Input();
};
