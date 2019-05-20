#include "ShootingPlayerAim_Idle.h"
#include "../Input/InputInc.h"
#include "../Actor/ShootingPlayerMode/ShootingPlayer/ShootingPlayerActor/State/stateInc.h"

ShootingPlayerAim_Idle::ShootingPlayerAim_Idle(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void ShootingPlayerAim_Idle::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::ShootingPlayerAimToIdle;
	parameters_->Set_Motion(ShootingPlayerMotionNum::MotionPlayerAimToIdle);
}

void ShootingPlayerAim_Idle::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	//入力情報
	Input();

	//モーションの時間が終わったら移動状態へ
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 5)
	{
		mNextStateID = ActorStateID::ShootingPlayerIdle;
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

void ShootingPlayerAim_Idle::Input()
{
	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM5) || 
		Keyboard::GetInstance().KeyTriggerDown(KEYCODE::LSHIFT))
	{
		ShootingPlayerParam::getInstance().Set_AimCheck(true);

		mNextStateID = ActorStateID::ShootingPlayerIdleAiming;
		mNextStateFlag = true;
		return;
	}

}
