#include "ActorStateManager.h"

void ActorStateManager::add(const ActorStatePtr & state)
{
	state_ = state;
}

void ActorStateManager::initialize()
{
	state_->Stateinitialize();
}

void ActorStateManager::update(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	state_->StateUpdate(lposition, lrotation,lmesh);
}

void ActorStateManager::NextState(ActorStateID & lstate)
{
	//次の状態クラスの初期化処理を現在の状態から移行する前に行うため
	lstate = state_->Get_NextStateID();
}

bool ActorStateManager::Get_NextStateFlag() const
{
	return state_->Get_NextStateFlag();
}

ActorStateID ActorStateManager::Get_NextStateID() const
{
	return state_->Get_NextStateID();
}
