#pragma once

#include "../Actor/ActorState/ActorStateBase.h"
#include "../Effekseer/EffectObj/EffectObj.h"

//通常エネミー咆哮ステイトクラス
class NormalEnemyRoar :public ActorStateBase
{
public:
	NormalEnemyRoar(IWorld* world, ActorParameters& parameter);
	virtual void Stateinitialize() override;
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation, AnimatedMesh & lmesh) override;

private:
	EffectObj meff;
};
