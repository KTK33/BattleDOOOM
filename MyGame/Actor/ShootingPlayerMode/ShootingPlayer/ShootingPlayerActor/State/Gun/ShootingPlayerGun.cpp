#include "ShootingPlayerGun.h"
#include "../Actor/ShootingPlayerMode/ShootingPlayerBullet/ShootingPlayerBullet.h"
#include "../Actor/ShootingPlayerMode/ShootingPlayer/ShootingPlayerActor/State/stateInc.h"

ShootingPlayerGun::ShootingPlayerGun(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void ShootingPlayerGun::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::ShootingPlayerGun;
	parameters_->Set_Motion(ShootingPlayerMotionNum::MotionPlayerStopGun);
}

void ShootingPlayerGun::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	if (parameters_->Get_Statetimer() == 5.0f)
	{
		//�e�̐���
		Gun(lposition, lrotation);

		ShootingPlayerParam::getInstance().Red_RemainGun(1);
	}

	//���[�V�����̎��Ԃ��I�������ړ���Ԃ�
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 5)
	{
		mNextStateID = parameters_->Get_PrevStateID();
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

void ShootingPlayerGun::Gun(Vector3 lposition, Matrix lrotation)
{
	world_->add_actor(ActorGroup::PlayerBullet, new_actor<ShootingPlayerBullet>
		(world_, Vector3{ lposition.x,lposition.y + 13.0f,lposition.z } +lrotation.Forward() * 4 + lrotation.Right() * 3, 
			ShootingPlayerParam::getInstance().Get_AimPos(), ShootingPlayerParam::getInstance().Get_AttackParam()));
}
