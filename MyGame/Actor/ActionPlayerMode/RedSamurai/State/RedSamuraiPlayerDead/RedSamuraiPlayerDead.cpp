#include "RedSamuraiPlayerDead.h"
#include "../Actor/ActionPlayerMode/RedSamurai/RedSamuraiMotionNum.h"
#include "../../RedSamuraiParam/RedSamuraiParam.h"
#include "../Sound/Sound.h"

RedSamuraiPlayerDead::RedSamuraiPlayerDead(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void RedSamuraiPlayerDead::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::RedSamuraiIdle;

	parameters_->Set_Motion(RedSamuraiMotionNum::MotionRedSamuraiSwardPut1);
	Sound::GetInstance().PlaySE(SE_ID::RED_WIN);
}

void RedSamuraiPlayerDead::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	//ƒ‚[ƒVƒ‡ƒ“‚ÌŽžŠÔ‚ªI‚í‚Á‚½‚çˆÚ“®ó‘Ô‚Ö
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 5)
	{
		mNextStateID = ActorStateID::RedSamuraiPlayerDeadAfter;
		RedSamuraiParam::getInstance().SetSwardPosNum(5);
		RedSamuraiParam::getInstance().SetSwardModelNum(14);
		mNextStateFlag = true;
		return;
	}
}
