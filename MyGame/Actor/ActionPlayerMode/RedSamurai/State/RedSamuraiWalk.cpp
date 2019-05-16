#include "RedSamuraiWalk.h"
#include "../World/IWorld.h"
#include "../Actor/Actor.h"
#include "../Actor/ActionPlayerMode/RedSamurai/RedSamuraiMotionNum.h"

RedSamuraiWaik::RedSamuraiWaik(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void RedSamuraiWaik::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::RedSamuraiWalk;

	parameters_->Set_Motion(RedSamuraiMotionNum::MotionRedSamuraiForWard);

	mAttackTime = 180.0f;
}

void RedSamuraiWaik::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	//プレイヤーの検索
	auto player_ = world_->find_actor(ActorGroup::Player, "Player").get();
	if (player_ == nullptr) return;

	//プレイヤーに向かって移動する
	Movement(lposition);
	//等間隔で攻撃状態へ
	AttackTimeCheck(lposition,lrotation);

	//HPが０になったら死亡
	if (parameters_->Get_HP() <= 0)
	{
		mNextStateID = ActorStateID::RedSamuraiDead;
		mNextStateFlag = true;
		return;
	}
}

void RedSamuraiWaik::Movement(Vector3 lposition)
{
	//プレイヤーの検索
	auto player_ = world_->find_actor(ActorGroup::Player, "Player").get();
	if (player_ == nullptr) return;

	//プレイヤーとの距離
	const float PlayerDis = Vector3::Distance(lposition, player_->Getposition());

	//距離が15以下はそれ以上先に行かない
	if (PlayerDis <= 15.0f) return;

	//プレイヤーへのベクトル
	const Vector3 playervec = Vector3(player_->Getposition().x - lposition.x, player_->Getposition().y - lposition.y, player_->Getposition().z - lposition.z).Normalize();
	parameters_->Set_Position(lposition + playervec * WalkSpeed);
}

void RedSamuraiWaik::AttackTimeCheck(Vector3 lposition, Matrix lrotation)
{
	//頻度時間が０になったら攻撃状態へ
	mAttackTime -= 1.0f;
	if (mAttackTime < 0)
	{
		mNextStateID = ActorStateID::RedSamuraiAttack;
		mNextStateFlag = true;
		return;
	}

}