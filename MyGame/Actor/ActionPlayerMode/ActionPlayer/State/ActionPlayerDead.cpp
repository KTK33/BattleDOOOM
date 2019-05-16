#include "ActionPlayerDead.h"
#include "../ActionPlayerMotionNum.h"

ActionPlayerDead::ActionPlayerDead(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void ActionPlayerDead::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::ActionPlayerDead;
	parameters_->Set_Motion(ActionPlayerMotion::MotionPlayerIdel);
}

void ActionPlayerDead::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	//ƒ‚[ƒVƒ‡ƒ“‚ÌŠÔ‚ªI‚í‚Á‚½‚ç€–S
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 5)
	{
		parameters_->Set_IsDead(true);
		return;
	}
}
