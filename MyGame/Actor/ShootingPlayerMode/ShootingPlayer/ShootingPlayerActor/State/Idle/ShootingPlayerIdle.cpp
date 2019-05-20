#include "ShootingPlayerIdle.h"
#include "../Input/InputInc.h"
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
	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM5) ||
		Keyboard::GetInstance().KeyTriggerDown(KEYCODE::LSHIFT))
	{
		mNextStateID = ActorStateID::ShootingPlayerIdleToAim;
		mNextStateFlag = true;
		return;
	}

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

	//�e�U��
	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM4) || 
		Keyboard::GetInstance().KeyTriggerDown(KEYCODE::Q))
	{
		mNextStateID = ActorStateID::ShootingPlayerGunPunch;
		mNextStateFlag = true;
		return;
	}

	//�W�����v
	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM1) ||
		Keyboard::GetInstance().KeyTriggerDown(KEYCODE::LCTRL))
	{
		mNextStateID = ActorStateID::ShootingPlayerJump;
		mNextStateFlag = true;
		return;
	}

	//����
	if (GetJoypadPOVState(DX_INPUT_PAD1, 0) == 18000 || 
		Keyboard::GetInstance().KeyTriggerDown(KEYCODE::Y))
	{
		mNextStateID = ActorStateID::ShootingPlayerThohatu;
		mNextStateFlag = true;
		return;
	}
}
