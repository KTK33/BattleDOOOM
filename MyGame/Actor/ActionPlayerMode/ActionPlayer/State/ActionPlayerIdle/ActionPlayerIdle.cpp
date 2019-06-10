#include "ActionPlayerIdle.h"
#include "../Input/InputInfoInc.h"
#include "../Scene/GameData/GameDataManager.h"

ActionPlayerIdle::ActionPlayerIdle(IWorld * world, ActorParameters & parameter)
{
	world_ = world;
	parameters_ = &parameter;
}

void ActionPlayerIdle::Stateinitialize()
{
	mNextStateFlag = false;
	mNextStateID = ActorStateID::ActionPlayerIdle;
}

void ActionPlayerIdle::StateUpdate(Vector3 & lposition, Matrix & lrotation, AnimatedMesh & lmesh)
{
	//“ü—Íî•ñ
	Input();

	//HP‚ª‚O‚É‚È‚Á‚½‚çŽ€–S
	if (parameters_->Get_HP() <= 0)
	{
		mNextStateID = ActorStateID::ActionPlayerDead;
		mNextStateFlag = true;
		return;
	}
}

void ActionPlayerIdle::Input()
{
	if (GameDataManager::getInstance().GetDeadBossEnemy()) return;

	//UŒ‚
	if(ButtonB::GetInstance().TriggerDown())
	{
		mNextStateID = ActorStateID::ActionPlayerAttack;
		mNextStateFlag = true;
		return;
	}

	//ƒXƒeƒbƒv
	if(ButtonA::GetInstance().TriggerDown() && LeftStick::GetInstance().KnockCheck())
	{
		mNextStateID = ActorStateID::ActionPlayerAvoidance;
		mNextStateFlag = true;
		return;
	}
}

