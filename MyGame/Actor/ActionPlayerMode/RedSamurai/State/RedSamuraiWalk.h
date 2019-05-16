#pragma once

#include "../Actor/ActorState/ActorStateBase.h"


class RedSamuraiWaik :public ActorStateBase
{
public:
	RedSamuraiWaik(IWorld* world, ActorParameters& parameter);
	virtual void Stateinitialize() override;
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation, AnimatedMesh & lmesh) override;

private:
	//ˆÚ“®ˆ—
	void Movement(Vector3 lposition);
	//UŒ‚‚Ì•p“xˆ—
	void AttackTimeCheck(Vector3 lposition, Matrix lrotation);
private:
	//ˆÚ“®‘¬“x
	const float WalkSpeed{ 0.25f };
	//UŒ‚‚Ì•p“xŠÔ
	float mAttackTime;
};
