#include "ShootingPlayerReload.h"
#include "../Actor/ShootingPlayerMode/ShootingPlayer/ShootingPlayerActor/State/stateInc.h"
#include "../Game/GameData/ShootingMode/ShootingPlayerData.h"
#include "../Input/InputInfoInc.h"
#include "../Sound/Sound.h"

ShootingPlayerReload::ShootingPlayerReload(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void ShootingPlayerReload::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::ShootingPlayerReload;

	parameters_->Set_Motion(ShootingPlayerMotionNum::MotionPlayerReload);
}

void ShootingPlayerReload::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	if (parameters_->Get_Statetimer() == 30)
	{
		//弾数の計算
		GunCount();
		Sound::GetInstance().PlaySE(SE_ID::RELOAD_SE);
	}

	//モーションの時間が終わったら移動状態へ
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 5)
	{
		mNextStateID = parameters_->Get_PrevStateID();
		mNextStateFlag = true;
		return;
	}

	//ガード
	if (ButtonB::GetInstance().TriggerDown())
	{
		ShootingPlayerParam::getInstance().Set_AimCheck(false);
		mNextStateID = ActorStateID::ShootingPlayerGuard;
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

void ShootingPlayerReload::GunCount()
{
	int setpoint = 0;
	int HaveGun = ShootingPlayerParam::getInstance().Get_HaveGun();
	int SetRemainGun = ShootingPlayerParam::getInstance().Get_RemainGun();

	//持っている弾数　＜　一度にセットできる弾数
	if (HaveGun < SetGunPoint) {
		if (HaveGun + SetRemainGun < SetGunPoint)//持っている数＋残り弾数　＜　一度にセットできる弾数
		{
			setpoint = HaveGun;
		}
		else {
			setpoint = SetGunPoint - SetRemainGun;
		}
	}
	else {
		setpoint = SetGunPoint - SetRemainGun;
	}
	HaveGun -= setpoint;
	SetRemainGun += setpoint;

	ShootingPlayerParam::getInstance().Set_HaveGun(HaveGun);
	ShootingPlayerParam::getInstance().Set_RemainGun(SetRemainGun);
}
