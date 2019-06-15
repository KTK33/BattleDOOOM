#include "BigBossEnemyAttack.h"
#include "../World/IWorld.h"
#include "../Actor/Actor.h"
#include "../Actor/ActorGroup.h"
#include "BigBossAttackCollision/BigBossAttackCollision.h"
#include "../Actor/ShootingPlayerMode/ShootingEnemy/BigBossEnemy/BigBossEnemyMotionNum.h"
#include "../../BigBossEnemyParam/BigBossEnemyParam.h"

BigBossEnemyAttack::BigBossEnemyAttack(IWorld * world, ActorParameters & parameter):
	meff((int)EFFECT_ID::LASER_TYOKUSEN)
{
	world_ = world;
	parameters_ = &parameter;
}

void BigBossEnemyAttack::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::BigBossEnemyIdle;

	meff.stop();
	meff.set_endTime(0.0f);
	meffspeed = 1.0f;
	mAttackHeight = 0.0f;
	mAttackPos = Vector3::Zero;

	mattackType = 0;
	Attack();
}

void BigBossEnemyAttack::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	AttackBehavior(lposition,lrotation);

	auto player = world_->find_actor(ActorGroup::Player, "Player").get();

	if (!BigBossEnemyParam::getInstance().Get_RotaCheck()){
		mPlayerPos = player->Getposition();
	}

	//エフェクトの設定
	meff.set_position(Vector3(lposition.x,lposition.y + mAttackHeight,lposition.z) + mAttackPos);
	meff.set_scale(Vector3(7.0f, 7.0f, 7.0f));
	Matrix angle = Matrix::CreateLookAt(lposition, mPlayerPos, Vector3::Up);
	angle *= Matrix::CreateRotationY(180);
	meff.set_rotation(Matrix::Angle(angle));

	meff.update(meffspeed);
	meff.draw();

	//HPが０になったら死亡
	if (parameters_->Get_HP() <= 0)
	{
		mNextStateID = ActorStateID::BigBossEnemyDead;
		mNextStateFlag = true;
		return;
	}

	//モーションの時間が終わったら
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 5)
	{
		meff.stop();
		BigBossEnemyParam::getInstance().Set_RotaCheck(false);
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
	default: break;
	}
}

void BigBossEnemyAttack::AttackBehavior(Vector3 lposition, Matrix lrotation)
{
	switch (mattackType)
	{
	case 1:
		if (parameters_->Get_Statetimer() == 30.0f)
		{
			BigBossEnemyParam::getInstance().Set_RotaCheck(true);
			mAttackHeight = 18.0f;
			mAttackPos = lrotation.Forward() * 20;
			meffspeed = 1.0f;
			AttackCollision(lposition, lrotation, lrotation.Forward() * 120, 40, 2, Vector3(0.0f, 15.0f, 0.0f), 200.0f, 5.0f);
			EffectCreate(EFFECT_ID::LASER_TYOKUSEN, 80.0f);
		}

		break;
	case 2:
		if (parameters_->Get_Statetimer() == 40.0f)
		{
			BigBossEnemyParam::getInstance().Set_RotaCheck(true);
			mAttackHeight = 18.0f;
			mAttackPos = lrotation.Forward() * 15;
			meffspeed = 1.0f;
			AttackCollision(lposition, lrotation, lrotation.Forward() * 80, 30, 3, Vector3(0.0f, 13.0f, 0.0f), 40.0f, 50.0f);
			EffectCreate(EFFECT_ID::LASER_HANI_SEMAI, 120.0f);
		}
		break;
	case 3:
		if (parameters_->Get_Statetimer() == 100.0f)
		{
			mAttackHeight = 15.0f;
			mAttackPos = lrotation.Right() * 10;
			meffspeed = 0.5f;
			EffectCreate(EFFECT_ID::LASER_HANI_TAME, 150.0f);
		}
		if (parameters_->Get_Statetimer() == 160.0f)
		{
			BigBossEnemyParam::getInstance().Set_RotaCheck(true);
			AttackCollision(lposition, lrotation, lrotation.Right() * 5 + lrotation.Forward() * 60, 140, 4, Vector3(0.0f, 13.0f, 0.0f), 120.0f, 6.0f);
		}
		break;
	default: break;
	}
}

void BigBossEnemyAttack::AttackCollision(Vector3 lposition, Matrix lrotation, Vector3 attackpos,int deadTime, int attackParam, Vector3 spot, float len, float rad)
{
	//攻撃当たり判定の生成
	auto AttackPunch = std::make_shared<BigBossAttackCollision>(world_, Vector3{ lposition + attackpos },lrotation,
		std::make_shared<BoundingCapsule>(spot, Matrix::CreateRotationX(90), len, rad));
	world_->add_actor(ActorGroup::EnemyBullet, AttackPunch);
	AttackPunch->SetParam(false, deadTime, attackParam,mattackType);
}

void BigBossEnemyAttack::EffectCreate(EFFECT_ID id, float deadTime)
{
	meff.stop();
	meff.change_effect((int)id);
	meff.set_endTime(deadTime);
	meff.play();
}
