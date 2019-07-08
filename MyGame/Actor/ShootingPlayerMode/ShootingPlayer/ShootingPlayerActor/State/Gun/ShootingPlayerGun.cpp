#include "ShootingPlayerGun.h"
#include "../Actor/ShootingPlayerMode/ShootingPlayerBullet/ShootingPlayerBullet.h"
#include "../Actor/ShootingPlayerMode/ShootingPlayer/ShootingPlayerActor/State/stateInc.h"

ShootingPlayerGun::ShootingPlayerGun(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void ShootingPlayerGun::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::ShootingPlayerGun;
	parameters_->Set_Motion(ShootingPlayerMotionNum::MotionPlayerStopGun);
}

void ShootingPlayerGun::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	if (parameters_->Get_Statetimer() == 2.0f)
	{
		//弾の生成
		Gun(lposition, lrotation);

		ShootingPlayerParam::getInstance().Red_RemainGun(1);
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

void ShootingPlayerGun::Gun(Vector3 lposition, Matrix lrotation)
{
	//world_->add_actor(ActorGroup::PlayerBullet, new_actor<ShootingPlayerBullet>
	//	(world_, Vector3{ lposition.x,lposition.y + 16.0f,lposition.z } +lrotation.Forward() * 4 + lrotation.Right() * 3, 
	//		ShootingPlayerParam::getInstance().Get_AimPos(), ShootingPlayerParam::getInstance().Get_AttackParam()));]

	world_->add_actor(ActorGroup::PlayerBullet, new_actor<ShootingPlayerBullet>
		(world_, GetCameraPosition(),
			ShootingPlayerParam::getInstance().Get_AimPos(), ShootingPlayerParam::getInstance().Get_AttackParam()));

}
