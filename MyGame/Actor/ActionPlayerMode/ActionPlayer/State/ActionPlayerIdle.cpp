#include "ActionPlayerIdle.h"
#include "../Input/GamePad/GamePad.h"
#include "../Input/Keyboard/Keyboard.h"

ActionPlayerIdle::ActionPlayerIdle(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void ActionPlayerIdle::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::ActionPlayerIdel;
}

void ActionPlayerIdle::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	//���͏��
	Input();

	//HP���O�ɂȂ����玀�S
	if (parameters_->Get_HP() <= 0)
	{
		mNextStateID = ActorStateID::ActionPlayerDead;
		mNextStateFlag = true;
		return;
	}
}

void ActionPlayerIdle::Input()
{
	//�U��
	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM2) || 
		Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)) {
		mNextStateID = ActorStateID::ActionPlayerAttack;
		mNextStateFlag = true;
		return;
	}

	//�X�e�b�v
	if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM1) || 
		Keyboard::GetInstance().KeyTriggerDown(KEYCODE::LSHIFT)) {
		mNextStateID = ActorStateID::ActionPlayerAvoidance;
		mNextStateFlag = true;
		return;
	}
}

