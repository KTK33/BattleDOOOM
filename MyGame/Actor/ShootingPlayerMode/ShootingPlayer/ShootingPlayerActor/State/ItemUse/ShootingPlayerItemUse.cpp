#include "ShootingPlayerItemUse.h"
#include "../Actor/ShootingPlayerMode/ShootingPlayer/ShootingPlayerActor/State/stateInc.h"
#include "../Sound/Sound.h"

ShootingPlayerItemUse::ShootingPlayerItemUse(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void ShootingPlayerItemUse::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::ActionPlayerIdle;
	parameters_->Set_Motion(ShootingPlayerMotionNum::MotionPlayerItemUse);

	ShootingPlayerParam::getInstance().Set_AimCheck(false);
}

void ShootingPlayerItemUse::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	if (parameters_->Get_Statetimer() == 28.0f)
	{
		int itemType = ShootingPlayerParam::getInstance().Get_ItemType();
		if (itemType == 1){
			Sound::GetInstance().PlaySE(SE_ID::RECOVERITEM_USE);
		}
		else if (itemType == 2){
			Sound::GetInstance().PlaySE(SE_ID::ATTACKITEM_USE);
		}
	}

	//ƒ‚[ƒVƒ‡ƒ“‚ÌŽžŠÔ‚ªI‚í‚Á‚½‚çˆÚ“®ó‘Ô‚Ö
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 5)
	{
		mNextStateID = ActorStateID::ShootingPlayerIdle;
		mNextStateFlag = true;
		ShootingPlayerParam::getInstance().Set_ItemUse(false,0);
		return;
	}

	//HP‚ª‚O‚É‚È‚Á‚½‚çŽ€–S
	if (parameters_->Get_HP() <= 0)
	{
		mNextStateID = ActorStateID::ShootingPlayerDead;
		mNextStateFlag = true;
		ShootingPlayerParam::getInstance().Set_ItemUse(false,0);
		return;
	}
}
