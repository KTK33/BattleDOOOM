#include "ShootingPlayerGunPunch.h"
#include "../Actor/PlayerAttackCollision/PlayerAttackCollision.h"
#include "../Actor/ShootingPlayerMode/ShootingPlayer/ShootingPlayerActor/State/stateInc.h"

ShootingPlayerGunPunch::ShootingPlayerGunPunch(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void ShootingPlayerGunPunch::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::ShootingPlayerGunPunch;
	parameters_->Set_Motion(ShootingPlayerMotionNum::MotionPlayerGunPunch);
}

void ShootingPlayerGunPunch::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	//ステイトの時間で攻撃判定を生成
	if (parameters_->Get_Statetimer() == 30.0f)
	{
		AttackCollision(lposition, lrotation);
	}

	//モーションの時間が終わったら移動状態へ
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 5)
	{
		mNextStateID = parameters_->Get_PrevStateID();
		mNextStateFlag = true;
		return;
	}

	//ダメージを受けたらダメージ状態へ
	if (parameters_->Get_invincibly())
	{
		mNextStateID = ActorStateID::ShootingPlayerDamage;
		mNextStateFlag = true;
		return;
	}

	//HPが０になったら死亡
	if (parameters_->Get_HP() <= 0)
	{
		mNextStateID = ActorStateID::ShootingPlayerDead;
		mNextStateFlag = true;
		return;
	}

}

void ShootingPlayerGunPunch::AttackCollision(Vector3 lposition, Matrix lrotation)
{
	auto AttackPunch = std::make_shared<PlayerAttackCollision>(world_, Vector3{ lposition + lrotation.Forward() * 10 },
		std::make_shared<BoundingCapsule>(Vector3{ 0.0f,13.0f,0.0f }, Matrix::Identity, 1.5f, 2.5f));
	world_->add_actor(ActorGroup::PlayerBullet, AttackPunch);
	AttackPunch->SetParam(false, 20, 1);

}