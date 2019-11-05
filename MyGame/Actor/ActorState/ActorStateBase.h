#pragma once

#include "../Math/Vector3.h"

#include "ActorStateID.h"
#include "../ActorParameters.h"
#include "../Animation/AnimationMesh.h"


class IWorld;
class ActorParameters;

//アクター状態クラス基盤
class ActorStateBase
{
public:
	ActorStateBase() = default;

	//仮想関数　状態初期化
	virtual void Stateinitialize();

	//仮想関数状態更新
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation,AnimatedMesh & lmesh);

	//次の状態に移行するフラグを取得
	bool Get_NextStateFlag() const;

	//次の状態を取得
	ActorStateID Get_NextStateID() const;

	ActorStateBase(const ActorStateBase& other) = delete;
	ActorStateBase& operator=(const ActorStateBase& other) = delete;

protected:
	IWorld* world_{ nullptr };
	ActorParameters* parameters_{ nullptr };

	bool mNextStateFlag;
	ActorStateID mNextStateID;
};