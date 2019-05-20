#include "NormalEnemyIdle.h"
#include "../Actor/ShootingPlayerMode/ShootingEnemy/NormalEnemy/NormalEnemyMotionNum.h"

NormalEnemyIdle::NormalEnemyIdle(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void NormalEnemyIdle::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::NormalEnemyIdle;
	parameters_->Set_Motion(NormalEnemyMotionNum::MotionNormalEnemyMove);

}

void NormalEnemyIdle::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	if (parameters_->Get_Attack() == true)
	{
		mNextStateID = ActorStateID::NormalEnemyPunch;
		mNextStateFlag = true;
		return;
	}

	//HP���O�ɂȂ����玀�S
	if (parameters_->Get_HP() <= 0)
	{
		mNextStateID = ActorStateID::NormalEnemyDead;
		mNextStateFlag = true;
		return;
	}

	//1��ڂ̃_���[�W���󂯂�����K
	if (parameters_->Get_invincibly())
	{
		mNextStateID = ActorStateID::NormalEnemyDamage;
		mNextStateFlag = true;
		return;
	}
}
