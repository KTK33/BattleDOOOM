#include "BossEnemyPunch.h"
#include "../Actor/ShootingPlayerMode/ShootingEnemy/BossEnemy/BossEnemyMotionNum.h"
#include "../World/IWorld.h"
#include "../Actor/Actor.h"
#include "../Actor/EnemyAttackCollison/EnemyAttackCollison.h"

BossEnemyPunch::BossEnemyPunch(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void BossEnemyPunch::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::BossEnemyPunch;
	parameters_->Set_Motion(BossEnemyMotion::MotionBossPunch);
}

void BossEnemyPunch::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	if (parameters_->Get_Statetimer() == 30.0f)
	{
		AttackCollision(lposition, lrotation, 15, 3, Vector3(0.0f, 13.0f, 0.0f), 1.5f, 2.5f);
	}
	//ƒ‚[ƒVƒ‡ƒ“‚ÌŠÔ‚ªI‚í‚Á‚½‚ç
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 5)
	{
		mNextStateID = ActorStateID::BossEnemyIdle;
		parameters_->Set_AttackType(0);
		mNextStateFlag = true;
		return;
	}
}

void BossEnemyPunch::AttackCollision(Vector3 lposition, Matrix lrotation, int deadTime, int attackParam, Vector3 spot, float len, float rad)
{
	//UŒ‚“–‚½‚è”»’è‚Ì¶¬
	auto AttackPunch = std::make_shared<EnemyAttackCollison>(world_, Vector3{ lposition + lrotation.Forward() * 10 },
		std::make_shared<BoundingCapsule>(spot, Matrix::Identity, len, rad));
	world_->add_actor(ActorGroup::EnemyBullet, AttackPunch);
	AttackPunch->SetParam(false, deadTime, attackParam);

}
