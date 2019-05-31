#include "RedSamuraiPlayerDeadAftor.h"
#include "../Actor/ActionPlayerMode/RedSamurai/RedSamuraiMotionNum.h"

RedSamuraiPlayerDeadAftor::RedSamuraiPlayerDeadAftor(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void RedSamuraiPlayerDeadAftor::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::RedSamuraiIdel;

	parameters_->Set_Motion(RedSamuraiMotionNum::MotionRedSamuraiSwardPut2);
}

void RedSamuraiPlayerDeadAftor::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	//ƒ‚[ƒVƒ‡ƒ“‚ÌŽžŠÔ‚ªI‚í‚Á‚½‚çˆÚ“®ó‘Ô‚Ö
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 5)
	{
		parameters_->Set_Motion(RedSamuraiMotionNum::MotionRedSamuraiNoSwardIdle);
	}
}
