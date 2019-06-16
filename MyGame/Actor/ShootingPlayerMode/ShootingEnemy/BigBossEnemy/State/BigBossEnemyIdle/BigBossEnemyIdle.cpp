#include "BigBossEnemyIdle.h"
#include "../Actor/ShootingPlayerMode/ShootingEnemy/BigBossEnemy/BigBossEnemyMotionNum.h"

BigBossEnemyIdle::BigBossEnemyIdle(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void BigBossEnemyIdle::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::BossEnemyIdle;
	parameters_->Set_Motion(BigBossEnemyMotion::MotionBigBossIdle);
}

void BigBossEnemyIdle::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	//�U���X�e�C�g��
	if (parameters_->Get_Attack() == true)
	{
		mNextStateID = ActorStateID::BigBossEnemyAttack;
		mNextStateFlag = true;
		return;
	}

	//HP���O�ɂȂ����玀�S
	if (parameters_->Get_HP() <= 0)
	{
		mNextStateID = ActorStateID::BigBossEnemyDead;
		mNextStateFlag = true;
		return;
	}
}
