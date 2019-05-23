#include "BossEnemyDead.h"
#include "../Actor/ShootingPlayerMode/ShootingEnemy/BossEnemy/BossEnemyMotionNum.h"

BossEnemyDead::BossEnemyDead(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void BossEnemyDead::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::BossEnemyPunch;
	parameters_->Set_Motion(BossEnemyMotion::MotionBossDead);
}

void BossEnemyDead::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	//モーションの時間が終わったら
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 5)
	{
		parameters_->Set_IsDead(true);
		return;
	}
}
