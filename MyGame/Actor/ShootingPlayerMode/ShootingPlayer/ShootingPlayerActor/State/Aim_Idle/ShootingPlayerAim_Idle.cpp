#include "ShootingPlayerAim_Idle.h"
#include "../Input/InputInc.h"
#include "../Actor/ShootingPlayerMode/ShootingPlayer/ShootingPlayerActor/State/stateInc.h"

ShootingPlayerAim_Idle::ShootingPlayerAim_Idle(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void ShootingPlayerAim_Idle::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::ShootingPlayerAimToIdle;
	parameters_->Set_Motion(ShootingPlayerMotionNum::MotionPlayerAimToIdle);
}

void ShootingPlayerAim_Idle::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	//���͏��
	Input();

	//���[�V�����̎��Ԃ��I�������ړ���Ԃ�
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 5)
	{
		mNextStateID = ActorStateID::ShootingPlayerIdle;
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

void ShootingPlayerAim_Idle::Input()
{
		//�����[�h
	if (ShootingPlayerParam::getInstance().Get_RemainGun() < 7)
	{
		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM3) ||
			Keyboard::GetInstance().KeyTriggerDown(KEYCODE::R))
		{
			mNextStateID = ActorStateID::ShootingPlayerReload;
			mNextStateFlag = true;
			return;
		}
	}

	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM5) || 
		Keyboard::GetInstance().KeyTriggerDown(KEYCODE::LSHIFT))
	{
		ShootingPlayerParam::getInstance().Set_AimCheck(true);

		mNextStateID = ActorStateID::ShootingPlayerIdleAiming;
		mNextStateFlag = true;
		return;
	}

}
