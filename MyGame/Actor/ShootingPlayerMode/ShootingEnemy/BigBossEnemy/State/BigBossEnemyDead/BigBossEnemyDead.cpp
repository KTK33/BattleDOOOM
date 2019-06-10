#include "BigBossEnemyDead.h"
#include "../Actor/ShootingPlayerMode/ShootingEnemy/BigBossEnemy/BigBossEnemyMotionNum.h"

BigBossEnemyDead::BigBossEnemyDead(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void BigBossEnemyDead::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::BigBossEnemyIdle;
	parameters_->Set_Motion(BigBossEnemyMotion::MotionBigBossDead);
}

void BigBossEnemyDead::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	//ƒ‚[ƒVƒ‡ƒ“‚ÌŠÔ‚ªI‚í‚Á‚½‚ç
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 5)
	{
		parameters_->Set_IsDead(true);
		return;
	}
}
