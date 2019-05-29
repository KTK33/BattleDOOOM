#include "RedSamuraiIdle.h"
#include "../World/IWorld.h"
#include "../Actor/Actor.h"
#include "../Actor/ActionPlayerMode/RedSamurai/RedSamuraiMotionNum.h"
#include "../../RedSamuraiParam/RedSamuraiParam.h"

RedSamuraiIdle::RedSamuraiIdle(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void RedSamuraiIdle::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::RedSamuraiIdel;
	parameters_->Set_Motion(RedSamuraiMotionNum::MotionRedSamuraiForWard);
}

void RedSamuraiIdle::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	if (RedSamuraiParam::getInstance().GetPlayerState() == ActorStateID::ActionPlayerDead)
	{
		mNextStateID = ActorStateID::RedSamuraiPlayerDead;
		mNextStateFlag = true;
		return;
	}
	if (parameters_->Get_Attack() == true)
	{
		mNextStateID = ActorStateID::RedSamuraiAttack;
		mNextStateFlag = true;
		return;
	}

	//HP���O�ɂȂ����玀�S
	if (parameters_->Get_HP() <= 0)
	{
		mNextStateID = ActorStateID::RedSamuraiDead;
		mNextStateFlag = true;
		return;
	}
}
