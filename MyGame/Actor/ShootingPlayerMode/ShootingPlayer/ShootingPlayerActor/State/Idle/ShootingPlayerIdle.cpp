#include "ShootingPlayerIdle.h"
#include "../Input/InputInc.h"
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

void ShootingPlayerIdle::Input()
{
	//アイドル→エイム前状態まで
	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM5) ||
		Keyboard::GetInstance().KeyTriggerDown(KEYCODE::LSHIFT))
	{
		mNextStateID = ActorStateID::ShootingPlayerIdleToAim;
		mNextStateFlag = true;
		return;
	}

	//リロード
	if (ShootingPlayerParam::getInstance().Get_RemainGun() < 7)
	{
		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM3) ||
			Keyboard::GetInstance().KeyTriggerDown(KEYCODE::R))
		{
			mNextStateID = ActorStateID::ShootingPlayerReload;
			mNextStateFlag = true;
			return;
		}
	}

	//銃攻撃
	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM4) || 
		Keyboard::GetInstance().KeyTriggerDown(KEYCODE::Q))
	{
		mNextStateID = ActorStateID::ShootingPlayerGunPunch;
		mNextStateFlag = true;
		return;
	}

	//ジャンプ
	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM1) ||
		Keyboard::GetInstance().KeyTriggerDown(KEYCODE::LCTRL))
	{
		mNextStateID = ActorStateID::ShootingPlayerJump;
		mNextStateFlag = true;
		return;
	}

	//挑発
	if (GetJoypadPOVState(DX_INPUT_PAD1, 0) == 18000 || 
		Keyboard::GetInstance().KeyTriggerDown(KEYCODE::Y))
	{
		mNextStateID = ActorStateID::ShootingPlayerThohatu;
		mNextStateFlag = true;
		return;
	}
}
