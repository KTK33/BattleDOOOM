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
	mNextStateID = ActorStateID::RedSamuraiIdle;

	parameters_->Set_Motion(RedSamuraiMotionNum::MotionRedSamuraiSwardPut2);
}

void RedSamuraiPlayerDeadAftor::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	//���[�V�����̎��Ԃ��I�������ړ���Ԃ�
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 5)
	{
		parameters_->Set_Motion(RedSamuraiMotionNum::MotionRedSamuraiNoSwardIdle);
	}
}
