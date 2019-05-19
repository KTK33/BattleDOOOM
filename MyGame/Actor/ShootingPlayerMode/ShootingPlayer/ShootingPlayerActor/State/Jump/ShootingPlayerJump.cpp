#include "ShootingPlayerJump.h"
#include "../Actor/ShootingPlayerMode/ShootingPlayer/ShootingPlayerActor/State/stateInc.h"

ShootingPlayerJump::ShootingPlayerJump(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void ShootingPlayerJump::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::ActionPlayerJump;
	parameters_->Set_Motion(ShootingPlayerMotionNum::MotionPlayerJump);
}

void ShootingPlayerJump::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	//���[�V�����̎��Ԃ��I�������ړ���Ԃ�
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 5)
	{
		mNextStateID = ActorStateID::ShootingPlayerIdle;
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