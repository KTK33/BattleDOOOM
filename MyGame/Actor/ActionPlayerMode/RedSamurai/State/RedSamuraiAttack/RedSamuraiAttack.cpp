#include "RedSamuraiAttack.h"
#include "../World/IWorld.h"
#include "../Actor/Actor.h"
#include "../Actor/ActionPlayerMode/RedSamurai/RedSamuraiMotionNum.h"
#include "../Actor/ActionPlayerMode/RedSamurai/Arrow/ArrowAttack.h"
#include "../Actor/EnemyAttackCollison/EnemyAttackCollison.h"
#include "../Sound/Sound.h"

RedSamuraiAttack::RedSamuraiAttack(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void RedSamuraiAttack::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::RedSamuraiAttack;

	mAttackAlready = false;
	mAttckStart = false;
	mAttckType = 0;
}

void RedSamuraiAttack::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	//一度だけ攻撃の選択をする
	if (!mAttackAlready)
	{
		AttackBehavior(lposition, lrotation);
	}
	mAttackAlready = true;

	//モーションの時間によって当たり判定を生成
	if (mAttckStart)
	{
		if (mAttckType < 7) {
			parameters_->Set_Motion(RedSamuraiMotionNum::MotionRedSamuraiAttack1);
			if (parameters_->Get_Statetimer() == 4.0f)AttackCollision(lposition, lrotation, 5, 1, Vector3(0.0f, 13.0f, 0.0f), 1.5f, 2.5f);
			if (parameters_->Get_Statetimer() == 9.0f)AttackCollision(lposition, lrotation, 5, 2, Vector3(0.0f, 13.0f, 0.0f), 1.5f, 2.5f);
			if (parameters_->Get_Statetimer() == 20.0f)AttackCollision(lposition, lrotation, 5, 2, Vector3(0.0f, 13.0f, 0.0f), 1.5f, 2.5f);
		}
		else {
			parameters_->Set_Motion(RedSamuraiMotionNum::MotionRedSamuraiAttack2);
			if (parameters_->Get_Statetimer() == 30.0f)AttackCollision(lposition, lrotation, 15, 5, Vector3(0.0f, 13.0f, 0.0f), 2.0f, 2.5f);
		}
	}

	//モーションの時間が終わったら移動状態へ
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 5)
	{
		parameters_->Set_Attack(false);
		mNextStateID = ActorStateID::RedSamuraiIdle;
		mNextStateFlag = true;
		return;
	}

	//HPが０になったら死亡
	if (parameters_->Get_HP() <= 0)
	{
		mNextStateID = ActorStateID::RedSamuraiDead;
		mNextStateFlag = true;
		return;
	}
}

void RedSamuraiAttack::AttackBehavior(Vector3 lposition, Matrix lrotation)
{
	//プレイヤーの検索
	auto player_ = world_->find_actor(ActorGroup::Player, "Player").get();
	if (player_ == nullptr) return;

	//プレイヤーとの距離
	const float PlayerDis = Vector3::Distance(lposition, player_->Getposition());

	//距離が30以上なら遠距離攻撃、それ以外は近距離攻撃
	if (PlayerDis >= 15.0f)
	{
		world_->add_actor(ActorGroup::EnemyBullet, std::make_shared<ArrowAttack>(52, world_, Vector3{ lposition.x,lposition.y + 13.0f,lposition.z } +lrotation.Forward() * 4 + lrotation.Right() * 3));
		parameters_->Set_Motion(RedSamuraiMotionNum::MotionRedSamuraiArrowAttack);
		parameters_->Set_Statetimer(0.0f);
	}
	else
	{
		mAttckStart = true;
		//確率で攻撃変化
		mAttckType = Random::rand(0, 10);
		parameters_->Set_Statetimer(0.0f);
	}
}

void RedSamuraiAttack::AttackCollision(Vector3 lposition, Matrix lrotation, int deadTime, int attackParam, Vector3 spot, float len, float rad)
{
	//攻撃当たり判定の生成
	auto AttackPunch = std::make_shared<EnemyAttackCollison>(world_, Vector3{ lposition + lrotation.Forward() * 10 },
		std::make_shared<BoundingCapsule>(spot, Matrix::Identity, len, rad));
	world_->add_actor(ActorGroup::EnemyBullet, AttackPunch);
	AttackPunch->SetParam(false, deadTime, attackParam);

	Sound::GetInstance().PlaySE(SE_ID::RED_SWARD);

}