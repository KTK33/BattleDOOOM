#include "RedSamuraiPlayerDead.h"
#include "../Actor/ActionPlayerMode/RedSamurai/RedSamuraiMotionNum.h"
#include "../../RedSamuraiParam/RedSamuraiParam.h"

RedSamuraiPlayerDead::RedSamuraiPlayerDead(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void RedSamuraiPlayerDead::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::RedSamuraiIdel;

	parameters_->Set_Motion(RedSamuraiMotionNum::MotionRedSamuraiSwardPut1);
}

void RedSamuraiPlayerDead::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	//ƒ‚[ƒVƒ‡ƒ“‚ÌŽžŠÔ‚ªI‚í‚Á‚½‚çˆÚ“®ó‘Ô‚Ö
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 5)
	{
		mNextStateFlag = true;
		RedSamuraiParam::getInstance().SetRedSamuraiStop(true);
		return;
	}
}
