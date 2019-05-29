#pragma once

#include "../Actor/ActorState/ActorStateBase.h"

class ActionPlayerAvoidance :public ActorStateBase
{
public:
	ActionPlayerAvoidance(IWorld* world, ActorParameters& parameter);
	virtual void Stateinitialize() override;
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation, AnimatedMesh & lmesh) override;

private:
	//“ü—Íî•ñ
	void Input();
};
