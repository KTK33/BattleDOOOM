#include "ShootingPlayerReload.h"
#include "../Actor/ShootingPlayerMode/ShootingPlayer/ShootingPlayerActor/State/stateInc.h"
#include "../Game/Define.h"
#include "../Input/InputInfoInc.h"

ShootingPlayerReload::ShootingPlayerReload(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void ShootingPlayerReload::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::ShootingPlayerReload;

	parameters_->Set_Motion(ShootingPlayerMotionNum::MotionPlayerReload);
}

void ShootingPlayerReload::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	//���͏��
	Input();

	//���[�V�����̎��Ԃ��I�������ړ���Ԃ�
	if (parameters_->Get_Statetimer() > lmesh.motion_end_time() - 5)
	{
		//�e���̌v�Z
		GunCount();

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

void ShootingPlayerReload::Input()
{
	//�G�C�������A�C�h����ԑO�܂�
	if (LeftStick::GetInstance().KnockCheck())
	{
		ShootingPlayerParam::getInstance().Set_AimCheck(false);
		mNextStateID = ActorStateID::ShootingPlayerAimToIdle;
		mNextStateFlag = true;
		return;
	}
}

void ShootingPlayerReload::GunCount()
{
	int setpoint = 0;
	int HaveGun = ShootingPlayerParam::getInstance().Get_HaveGun();
	int SetRemainGun = ShootingPlayerParam::getInstance().Get_RemainGun();

	//�����Ă���e���@���@��x�ɃZ�b�g�ł���e��
	if (HaveGun < SetGunPoint) {
		if (HaveGun + SetRemainGun < SetGunPoint)//�����Ă��鐔�{�c��e���@���@��x�ɃZ�b�g�ł���e��
		{
			setpoint = HaveGun;
		}
		else {
			setpoint = SetGunPoint - SetRemainGun;
		}
	}
	else {
		setpoint = SetGunPoint - SetRemainGun;
	}
	HaveGun -= setpoint;
	SetRemainGun += setpoint;

	ShootingPlayerParam::getInstance().Set_HaveGun(HaveGun);
	ShootingPlayerParam::getInstance().Set_RemainGun(SetRemainGun);
}
