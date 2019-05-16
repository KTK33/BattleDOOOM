#include "ActorStateBase.h"

void ActorStateBase::Stateinitialize()
{
}

void ActorStateBase::StateUpdate(Vector3& lposition, Matrix& lrotation, AnimatedMesh & lmesh)
{
}

bool ActorStateBase::Get_NextStateFlag() const
{
	return mNextStateFlag;
}

ActorStateID ActorStateBase::Get_NextStateID() const
{
	return mNextStateID;
}
