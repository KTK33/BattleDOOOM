#include "RedSamuraiDead.h"
#include "../Actor/ActionPlayerMode/RedSamurai/RedSamuraiMotionNum.h"
#include "../Sound/Sound.h"

RedSamuraiDead::RedSamuraiDead(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void RedSamuraiDead::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::RedSamuraiDead;

	parameters_->Set_Motion(RedSamuraiMotionNum::MotionRedSamuraiDead);

	Sound::GetInstance().PlaySE(SE_ID::RED_LOSE);
}

void RedSamuraiDead::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	//ƒ‚[ƒVƒ‡ƒ“‚ÌŠÔ‚ªI‚í‚Á‚½‚çˆÚ“®ó‘Ô‚Ö
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 5)
	{
		parameters_->Set_IsDead(true);
		return;
	}
}
