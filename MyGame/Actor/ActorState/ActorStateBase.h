#pragma once

#include "../Math/Vector3.h"

#include "ActorStateID.h"
#include "../ActorParameters.h"
#include "../Animation/AnimationMesh.h"


class IWorld;
class ActorParameters;

class ActorStateBase
{
public:
	ActorStateBase() = default;
	virtual void Stateinitialize();
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation,AnimatedMesh & lmesh);

	bool Get_NextStateFlag() const;

	ActorStateID Get_NextStateID() const;

	ActorStateBase(const ActorStateBase& other) = delete;
	ActorStateBase& operator=(const ActorStateBase& other) = delete;

protected:
	IWorld* world_{ nullptr };
	ActorParameters* parameters_{ nullptr };

	bool mNextStateFlag;
	ActorStateID mNextStateID;
};