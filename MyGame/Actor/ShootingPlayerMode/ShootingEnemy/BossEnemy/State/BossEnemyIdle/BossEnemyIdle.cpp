#include "BossEnemyIdle.h"
#include "../Actor/ShootingPlayerMode/ShootingEnemy/BossEnemy/BossEnemyMotionNum.h"

BossEnemyIdle::BossEnemyIdle(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void BossEnemyIdle::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::BossEnemyIdle;
	parameters_->Set_Motion(BossEnemyMotion::MotionBossIdle);
}

void BossEnemyIdle::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	if (parameters_->GetAttackType() == 1)
	{
		mNextStateID = ActorStateID::BossEnemyPunch;
		mNextStateFlag = true;
		return;
	}

	if (parameters_->GetAttackType() == 2)
	{
		mNextStateID = ActorStateID::BossEnemyFireBefo;
		mNextStateFlag = true;
		return;
	}

	//HP‚ª‚O‚É‚È‚Á‚½‚çŽ€–S
	if (parameters_->Get_HP() <= 0)
	{
		mNextStateID = ActorStateID::BossEnemyDead;
		mNextStateFlag = true;
		return;
	}

	//1‰ñ–Ú‚Ìƒ_ƒ[ƒW‚ðŽó‚¯‚½‚ç™ôšK
	if (parameters_->Get_invincibly())
	{
		mNextStateID = ActorStateID::BossEnemyDamage;
		mNextStateFlag = true;
		return;
	}
}
