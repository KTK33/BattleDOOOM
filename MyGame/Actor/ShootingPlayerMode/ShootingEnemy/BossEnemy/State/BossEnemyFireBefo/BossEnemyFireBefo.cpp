#include "BossEnemyFireBefo.h"
#include "../Actor/ShootingPlayerMode/ShootingEnemy/BossEnemy/BossEnemyMotionNum.h"

BossEnemyFireBefo::BossEnemyFireBefo(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void BossEnemyFireBefo::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::BossEnemyPunch;
	parameters_->Set_Motion(BossEnemyMotion::MotionBossFireBefo);
}

void BossEnemyFireBefo::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	//ƒ‚[ƒVƒ‡ƒ“‚ÌŽžŠÔ‚ªI‚í‚Á‚½‚ç
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 5)
	{
		mNextStateID = ActorStateID::BossEnemyFire;
		mNextStateFlag = true;
		return;
	}
}
