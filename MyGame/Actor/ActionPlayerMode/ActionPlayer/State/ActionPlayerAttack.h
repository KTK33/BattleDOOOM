#pragma once

#include "../Actor/ActorState/ActorStateBase.h"

class ActionPlayerAttack :public ActorStateBase
{
public:
	ActionPlayerAttack(IWorld* world, ActorParameters& parameter);
	virtual void Stateinitialize() override;
	virtual void StateUpdate(Vector3& lposition, Matrix& lrotation, AnimatedMesh & lmesh) override;

private:
	//UŒ‚
	void Attack();
	//UŒ‚‚Ìí—Ş‚Å“–‚½‚è”»’è‚ğ•ÏX
	void AttackOption(Vector3 lposition, Matrix lrotation);
	//UŒ‚‚Ì“–‚½‚è”»’è¶¬
	void AttackCollision(Vector3 lposition, Matrix lrotation, int deadTime, int attackParam, Vector3 spot, float len, float rad);
	//“ü—Íî•ñ
	void Input();
private:
	int mAttackCount;
};
