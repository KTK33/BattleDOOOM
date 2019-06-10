#include "ShootingPlayerIdle.h"
#include "../Input/InputInfoInc.h"
#include "../Actor/ShootingPlayerMode/ShootingPlayer/ShootingPlayerActor/State/stateInc.h"

ShootingPlayerIdle::ShootingPlayerIdle(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void ShootingPlayerIdle::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::ShootingPlayerIdle;
}

void ShootingPlayerIdle::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	//入力情報
	Input();

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

void ShootingPlayerIdle::Input()
{
	//アイドル→エイム前状態まで
	if(ButtonLB::GetInstance().TriggerDown())
	{
		mNextStateID = ActorStateID::ShootingPlayerIdleToAim;
		mNextStateFlag = true;
		return;
	}

	if (ButtonB::GetInstance().TriggerDown())
	{
		mNextStateID = ActorStateID::ShootingPlayerGuard;
		mNextStateFlag = true;
		return;
	}

	//リロード
	if (ShootingPlayerParam::getInstance().Get_RemainGun() < 7)
	{
		if(ButtonX::GetInstance().TriggerDown())
		{
			mNextStateID = ActorStateID::ShootingPlayerReload;
			mNextStateFlag = true;
			return;
		}
	}

	//銃攻撃
	if(ButtonY::GetInstance().TriggerDown())
	{
		mNextStateID = ActorStateID::ShootingPlayerGunPunch;
		mNextStateFlag = true;
		return;
	}

	//ジャンプ
	if(ButtonA::GetInstance().TriggerDown())
	{
		mNextStateID = ActorStateID::ShootingPlayerJump;
		mNextStateFlag = true;
		return;
	}

	//挑発
	if(DPad::GetInstance().GetDown())
	{
		mNextStateID = ActorStateID::ShootingPlayerThohatu;
		mNextStateFlag = true;
		return;
	}

	//アイテム使用
	if (ShootingPlayerParam::getInstance().Get_ItemUse())
	{
		mNextStateID = ActorStateID::ShootingPlayerItemUse;
		mNextStateFlag = true;
		return;
	}
}
