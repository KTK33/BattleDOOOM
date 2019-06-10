#include "ShootingPlayerIdle_Aim.h"
#include "../Actor/ShootingPlayerMode/ShootingPlayer/ShootingPlayerActor/State/stateInc.h"
#include "../Input/InputInfoInc.h"

ShootingPlayerIdle_Aim::ShootingPlayerIdle_Aim(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void ShootingPlayerIdle_Aim::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::ShootingPlayerIdleToAim;

	parameters_->Set_Motion(ShootingPlayerMotionNum::MotionPlayerIdleToAim);
}

void ShootingPlayerIdle_Aim::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	Input();
	//���[�V�����̎��Ԃ��I�������
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 5)
	{
		ShootingPlayerParam::getInstance().Set_AimCheck(true);

		mNextStateID = ActorStateID::ShootingPlayerIdleAiming;
		mNextStateFlag = true;
		return;
	}

	//�A�C�e���g�p
	if (ShootingPlayerParam::getInstance().Get_ItemUse())
	{
		mNextStateID = ActorStateID::ShootingPlayerItemUse;
		mNextStateFlag = true;
		return;
	}

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

void ShootingPlayerIdle_Aim::Input()
{
	//�����[�h
	if (ShootingPlayerParam::getInstance().Get_RemainGun() < 7)
	{
		if(ButtonX::GetInstance().TriggerDown())
		{
			mNextStateID = ActorStateID::ShootingPlayerReload;
			mNextStateFlag = true;
			return;
		}
	}
}
