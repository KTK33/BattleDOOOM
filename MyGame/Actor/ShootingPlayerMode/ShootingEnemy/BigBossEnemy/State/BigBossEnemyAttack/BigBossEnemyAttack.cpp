#include "BigBossEnemyAttack.h"
#include "../World/IWorld.h"
#include "../Actor/Actor.h"
#include "../Actor/ActorGroup.h"
#include "BigBossAttackCollision/BigBossAttackCollision.h"
#include "../Actor/ShootingPlayerMode/ShootingEnemy/BigBossEnemy/BigBossEnemyMotionNum.h"

BigBossEnemyAttack::BigBossEnemyAttack(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void BigBossEnemyAttack::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::BigBossEnemyIdle;

	mattackType = 0;
	Attack();
}

void BigBossEnemyAttack::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	AttackBehavior(lposition,lrotation);

	//HP‚ª‚O‚É‚È‚Á‚½‚ç€–S
	if (parameters_->Get_HP() <= 0)
	{
		mNextStateID = ActorStateID::BigBossEnemyDead;
		mNextStateFlag = true;
		return;
	}

	//ƒ‚[ƒVƒ‡ƒ“‚ÌŠÔ‚ªI‚í‚Á‚½‚ç
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 5)
	{
		parameters_->Set_Attack(false);
		mNextStateID = ActorStateID::BigBossEnemyIdle;
		mNextStateFlag = true;
		return;
	}
}

void BigBossEnemyAttack::Attack()
{
	mattackType = mAC.AttackType(parameters_->Get_HP());
	switch (mattackType){
		case 1:
			parameters_->Set_Motion(BigBossEnemyMotion::MotionBigBossTyokusen);
			break;
		case 2:
			parameters_->Set_Motion(BigBossEnemyMotion::MotionBigBossHanniSemai);
			break;
		case 3:
			parameters_->Set_Motion(BigBossEnemyMotion::MotionBigBosstame);
			break;
		case 4:
			parameters_->Set_Motion(BigBossEnemyMotion::MotionBigBossHanni);
			break;
	default: break;
	}
}

void BigBossEnemyAttack::AttackBehavior(Vector3 lposition, Matrix lrotation)
{
	switch (mattackType)
	{
	case 1:
		if (parameters_->Get_Statetimer() == 30.0f)AttackCollision(lposition, lrotation, 20, 1, Vector3(0.0f, 13.0f, 0.0f), 1.5f, 3.0f);
		break;
	case 2:
		if (parameters_->Get_Statetimer() == 40.0f)AttackCollision(lposition, lrotation, 150, 1, Vector3(0.0f, 13.0f, 0.0f), 1.5f, 5.5f);
		break;
	case 3:
		if (parameters_->Get_Statetimer() == 45.0f)AttackCollision(lposition, lrotation, 25, 1, Vector3(0.0f, 13.0f, 0.0f), 1.5f, 3.0f);
		break;
	case 4:
		if (parameters_->Get_Statetimer() == 50.0f)AttackCollision(lposition, lrotation, 90, 1, Vector3(0.0f, 13.0f, 0.0f), 1.5f, 10.0f);
		break;
	default: break;
	}
}

void BigBossEnemyAttack::AttackCollision(Vector3 lposition, Matrix lrotation, int deadTime, int attackParam, Vector3 spot, float len, float rad)
{
	//UŒ‚“–‚½‚è”»’è‚Ì¶¬
	auto AttackPunch = std::make_shared<BigBossAttackCollision>(world_, Vector3{ lposition + lrotation.Forward() * 20 },lrotation,
		std::make_shared<BoundingCapsule>(spot, Matrix::Identity, len, rad));
	world_->add_actor(ActorGroup::EnemyBullet, AttackPunch);
	AttackPunch->SetParam(false, deadTime, attackParam,mattackType);
}
