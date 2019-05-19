#include "ShootingPlayerIdle_Aim.h"
#include "../Actor/ShootingPlayerMode/ShootingPlayer/ShootingPlayerActor/State/stateInc.h"

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
	//���[�V�����̎��Ԃ��I�������
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 5)
	{
		ShootingPlayerParam::getInstance().Set_AimCheck(true);

		mNextStateID = ActorStateID::ShootingPlayerIdleAiming;
		mNextStateFlag = true;
		return;
	}

	//�_���[�W���󂯂���_���[�W��Ԃ�
	if (ShootingPlayerParam::getInstance().Get_invincibly())
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

}
