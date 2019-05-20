#include "NormalEnemyRoar.h"
#include "../Actor/ShootingPlayerMode/ShootingEnemy/NormalEnemy/NormalEnemyMotionNum.h"

NormalEnemyRoar::NormalEnemyRoar(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void NormalEnemyRoar::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::NormalEnemyDamage;
	parameters_->Set_Motion(NormalEnemyMotionNum::MotionNormalEnemyRoar);
}

void NormalEnemyRoar::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	//���[�V�����̎��Ԃ��I�������
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 5)
	{
		mNextStateID = ActorStateID::NormalEnemyIdle;
		parameters_->Set_Invicibly(false);
		mNextStateFlag = true;
		return;
	}
}
