#include "BossEnemyFire.h"
#include "../World/IWorld.h"
#include "../Actor/Actor.h"
#include "../Actor/ShootingPlayerMode/ShootingEnemy/BossEnemy/BossEnemyMotionNum.h"
#include "../Actor/ShootingPlayerMode/ShootingEnemy/EnemyAttackFire/EnemyAttackFire.h"

BossEnemyFire::BossEnemyFire(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void BossEnemyFire::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::BossEnemyPunch;
	parameters_->Set_Motion(BossEnemyMotion::MotionBossPunch2);
}

void BossEnemyFire::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	if (parameters_->Get_Statetimer() == 10.0f)
	{
		FireCollision(lposition, lrotation);
	}
	//ƒ‚[ƒVƒ‡ƒ“‚ÌŽžŠÔ‚ªI‚í‚Á‚½‚ç
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 5)
	{
		mNextStateID = ActorStateID::BossEnemyIdle;
		parameters_->Set_AttackType(0);
		mNextStateFlag = true;
		return;
	}
}

void BossEnemyFire::FireCollision(Vector3 lposition, Matrix lrotation)
{
	auto enemyFire = std::make_shared<EnemyAttackFire>(8, world_, Vector3{ lposition.x,lposition.y + 15.0f,lposition.z } +lrotation.Forward() * 10);
	world_->add_actor(ActorGroup::EnemyBullet, enemyFire);
	enemyFire->GetEnemyForward(lrotation.Forward());

}
