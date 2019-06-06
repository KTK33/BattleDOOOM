#include "ShootingPlayerIdle.h"
#include "../Input/InputInfoInc.h"
#include "../Actor/ShootingPlayerMode/ShootingPlayer/ShootingPlayerActor/State/stateInc.h"

ShootingPlayerIdle::ShootingPlayerIdle(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void ShootingPlayerIdle::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::ShootingPlayerIdle;
}

void ShootingPlayerIdle::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
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

void ShootingPlayerIdle::Input()
{
	//�A�C�h�����G�C���O��Ԃ܂�
	if(ButtonLB::GetInstance().TriggerDown())
	{
		mNextStateID = ActorStateID::ShootingPlayerIdleToAim;
		mNextStateFlag = true;
		return;
	}

	if (ButtonB::GetInstance().TriggerDown())
	{
		mNextStateID = ActorStateID::ShootingPlayerGuard;
		mNextStateFlag = true;
		return;
	}

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

	//�e�U��
	if(ButtonY::GetInstance().TriggerDown())
	{
		mNextStateID = ActorStateID::ShootingPlayerGunPunch;
		mNextStateFlag = true;
		return;
	}

	//�W�����v
	if(ButtonA::GetInstance().TriggerDown())
	{
		mNextStateID = ActorStateID::ShootingPlayerJump;
		mNextStateFlag = true;
		return;
	}

	//����
	if(DPad::GetInstance().GetDown())
	{
		mNextStateID = ActorStateID::ShootingPlayerThohatu;
		mNextStateFlag = true;
		return;
	}
}
