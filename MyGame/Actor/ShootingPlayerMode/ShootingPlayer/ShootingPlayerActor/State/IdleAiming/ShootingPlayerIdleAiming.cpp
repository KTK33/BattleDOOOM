#include "ShootingPlayerIdleAiming.h"
#include "../Input/InputInc.h"
#include "../Actor/ShootingPlayerMode/ShootingPlayer/ShootingPlayerActor/State/stateInc.h"

ShootingPlayerIdleAiming::ShootingPlayerIdleAiming(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void ShootingPlayerIdleAiming::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::ShootingPlayerIdleAiming;
	parameters_->Set_Motion(ShootingPlayerMotionNum::MotionPlayerIdleAiming);

}

void ShootingPlayerIdleAiming::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	//入力情報
	Input();

	//ダメージを受けたらダメージ状態へ
	if (ShootingPlayerParam::getInstance().Get_invincibly())
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

void ShootingPlayerIdleAiming::Input()
{
	//エイム中→アイドル状態前まで
	if (GamePad::GetInstance().ButtonTriggerUp(PADBUTTON::NUM5) ||
		Keyboard::GetInstance().KeyTriggerUp(KEYCODE::LSHIFT)) {

		ShootingPlayerParam::getInstance().Set_AimCheck(false);
		mNextStateID = ActorStateID::ShootingPlayerAimToIdle;
		mNextStateFlag = true;
		return;
	}

	//銃を撃つステイトへ
	if(ShootingPlayerParam::getInstance().Get_RemainGun() > 0 &&
		parameters_->Get_Motion() != ShootingPlayerMotionNum::MotionPlayerBackGun)
	{
		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM6) || 
			Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE))
		{
			mNextStateID = ActorStateID::ShootingPlayerGun;
			mNextStateFlag = true;
			return;
		}
	}

	//リロード
	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM3) ||
		Keyboard::GetInstance().KeyTriggerDown(KEYCODE::R))
	{
		mNextStateID = ActorStateID::ShootingPlayerReload;
		mNextStateFlag = true;
		return;
	}
}
