#include "ActionPlayerAvoidance.h"
#include "../Actor/ActionPlayerMode/ActionPlayer/ActionPlayerMotionNum.h"
#include "../Input/InputInfoInc.h"
#include "../Sound/Sound.h"

ActionPlayerAvoidance::ActionPlayerAvoidance(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void ActionPlayerAvoidance::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::ActionPlayerAvoidance;

	parameters_->Set_Motion(ActionPlayerMotion::MotionPlayerAvoidance);

	Sound::GetInstance().PlaySE(SE_ID::ACTION_STEP);
}

void ActionPlayerAvoidance::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	//���͏��
	Input();
	//���[�V�����̎��Ԃ��I�������ړ���Ԃ�
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 5)
	{
		mNextStateID = ActorStateID::ActionPlayerIdel;
		mNextStateFlag = true;
		return;
	}
	//HP���O�ɂȂ����玀�S
	if (parameters_->Get_HP() <= 0)
	{
		mNextStateID = ActorStateID::ActionPlayerDead;
		mNextStateFlag = true;
		return;
	}
}

void ActionPlayerAvoidance::Input()
{
	//�X�e�b�v�h���U��
	if(ButtonB::GetInstance().TriggerDown())
	{
		mNextStateID = ActorStateID::ActionPlayerAvoidanceAttack;
		mNextStateFlag = true;
		return;
	}
	//�X�e�b�v
	if(ButtonA::GetInstance().TriggerDown())
	{
		mNextStateID = ActorStateID::ActionPlayerAvoidance;
		mNextStateFlag = true;
		return;
	}
}
