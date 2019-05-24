#include "ShootingPlayerIdleAiming.h"
#include "../Input/InputInfoInc.h"
#include "../Actor/ShootingPlayerMode/ShootingPlayer/ShootingPlayerActor/State/stateInc.h"

ShootingPlayerIdleAiming::ShootingPlayerIdleAiming(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void ShootingPlayerIdleAiming::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::ShootingPlayerIdleAiming;
	parameters_->Set_Motion(ShootingPlayerMotionNum::MotionPlayerIdleAiming);

}

void ShootingPlayerIdleAiming::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	//���͏��
	Input();

	//�_���[�W���󂯂���_���[�W��Ԃ�
	if (parameters_->Get_invincibly())
	{
		mNextStateID = ActorStateID::ShootingPlayerDamage;
		mNextStateFlag = true;
		return;
	}

	//HP���O�ɂȂ����玀�S
	if (parameters_->Get_HP() <= 0)
	{
		mNextStateID = ActorStateID::ShootingPlayerDead;
		mNextStateFlag = true;
		return;
	}
}

void ShootingPlayerIdleAiming::Input()
{
	////�G�C�������A�C�h����ԑO�܂�
	//if(ButtonLB::GetInstance().TriggerUp())
	//{

	//	ShootingPlayerParam::getInstance().Set_AimCheck(false);
	//	mNextStateID = ActorStateID::ShootingPlayerAimToIdle;
	//	mNextStateFlag = true;
	//	return;
	//}

	//if (ButtonLB::GetInstance().StateUp())
	//{
	//	ShootingPlayerParam::getInstance().Set_AimCheck(false);
	//	mNextStateID = ActorStateID::ShootingPlayerAimToIdle;
	//	mNextStateFlag = true;
	//	return;
	//}

	//�e�����X�e�C�g��
	if(ShootingPlayerParam::getInstance().Get_RemainGun() > 0 &&
		parameters_->Get_Motion() != ShootingPlayerMotionNum::MotionPlayerBackGun)
	{
		if(ButtonRB::GetInstance().TriggerDown())
		{
			mNextStateID = ActorStateID::ShootingPlayerGun;
			mNextStateFlag = true;
			return;
		}
	}

	//�����[�h
	if(ButtonX::GetInstance().TriggerDown())
	{
		mNextStateID = ActorStateID::ShootingPlayerReload;
		mNextStateFlag = true;
		return;
	}

	if (ButtonLB::GetInstance().StateDown()) return;

	ShootingPlayerParam::getInstance().Set_AimCheck(false);
	mNextStateID = ActorStateID::ShootingPlayerAimToIdle;
	mNextStateFlag = true;
	return;

}
