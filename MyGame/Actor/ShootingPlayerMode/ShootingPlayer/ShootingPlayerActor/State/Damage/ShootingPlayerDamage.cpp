#include "ShootingPlayerDamage.h"
#include "../Actor/ShootingPlayerMode/ShootingPlayer/ShootingPlayerActor/State/stateInc.h"

ShootingPlayerDamage::ShootingPlayerDamage(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void ShootingPlayerDamage::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::ActionPlayerDamage;
	parameters_->Set_Motion(ShootingPlayerMotionNum::MotionPlayerDamage);

	parameters_->Set_Invicibly(true);
}

void ShootingPlayerDamage::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	//ƒ‚[ƒVƒ‡ƒ“‚ÌŽžŠÔ‚ªI‚í‚Á‚½‚çˆÚ“®ó‘Ô‚Ö
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 5)
	{
		parameters_->Set_Invicibly(false);
		mNextStateID = ActorStateID::ShootingPlayerIdle;
		mNextStateFlag = true;
		return;
	}

	//HP‚ª‚O‚É‚È‚Á‚½‚çŽ€–S
	if (parameters_->Get_HP() <= 0)
	{
		mNextStateID = ActorStateID::ShootingPlayerDead;
		mNextStateFlag = true;
		return;
	}
}