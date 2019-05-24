#pragma once

#include "../Actor/ActorState/ActorStateBase.h"

class ShootingPlayerReload :public ActorStateBase
{
public:
	ShootingPlayerReload(IWorld* world, ActorParameters& parameter);
	virtual void Stateinitialize() override;
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation, AnimatedMesh & lmesh) override;

private:
	void Input();
	void GunCount();
};
