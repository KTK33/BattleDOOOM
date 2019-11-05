#pragma once

#include "ActorStateBase.h"
#include "ActorStatePtr.h"

//�A�N�^�[��ԊǗ��N���X
class ActorStateManager
{
public:
	ActorStateManager() = default;

	void add(const ActorStatePtr& state);

	void initialize();

	void update(Vector3& lposition, Matrix& lrotation, AnimatedMesh & lmesh);

	void NextState(ActorStateID& lstate);

	bool Get_NextStateFlag() const;

	ActorStateID Get_NextStateID() const;

	ActorStateManager(const ActorStateManager& other) = delete;
	ActorStateManager& operator=(const ActorStateManager& other) = delete;

private:
	ActorStatePtr state_;

};
